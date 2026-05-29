#include "gamescreen.h"
#include "build.h"
#include "enemy.h"
#include "missile.h"
#include "wavemanager.h"
#include "collisionmanager.h"
#include "gamefactory.h"
#include <cmath>

GameScreen::GameScreen(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(nullptr)
    , m_build(nullptr)
    , m_waveManager(nullptr)
    , m_collisionManager(nullptr)
    , m_factory(nullptr)
    , m_gameTimer(nullptr)
    , m_lives(100)
    , m_score(0)
    , m_isGameActive(false)
    , m_deltaTime(0.033f)
{
    setupScene();
}

GameScreen::~GameScreen()
{
    cleanupGame();
    delete m_scene;
}

void GameScreen::setFactory(GameFactory* factory)
{
    m_factory = factory;
}

void GameScreen::setupScene()
{
    m_scene = new QGraphicsScene(0, 0, 800, 600, this);
    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setBackgroundBrush(Qt::black);
    
    m_gameTimer = new QTimer(this);
    m_gameTimer->setInterval(33);
    connect(m_gameTimer, &QTimer::timeout, this, &GameScreen::onGameLoop);
}

void GameScreen::startGame()
{
    if (!m_factory) return;
    
    cleanupGame();
    
    // Создаём башню через фабрику
    m_build = m_factory->createBuild();
    m_build->setPos(400, 300);
    m_scene->addItem(m_build);
    
    // Создаём менеджеры
    m_waveManager = new WaveManager(this);
    m_waveManager->setTowerPos(m_build->pos());
    
    m_collisionManager = new CollisionManager(this);
    
    // Подключаем сигналы WaveManager
    connect(m_waveManager, &WaveManager::enemyToSpawn, 
            this, &GameScreen::onEnemyToSpawn);
    connect(m_waveManager, &WaveManager::waveComplete, 
            this, &GameScreen::onWaveComplete);
    connect(m_waveManager, &WaveManager::allWavesComplete, 
            this, &GameScreen::onGameWin);
    
    // Подключаем сигналы CollisionManager
    connect(m_collisionManager, &CollisionManager::enemyHit, 
            this, &GameScreen::onMissileHit);
    connect(m_collisionManager, &CollisionManager::buildHit, 
            this, &GameScreen::onBuildHit);
    
    m_isGameActive = true;
    m_lives = 100;
    m_score = 0;
    m_gameTimer->start();
    m_waveManager->nextWave();
}

void GameScreen::stopGame()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    if (m_waveManager) m_waveManager->pause();
}

void GameScreen::resetGame()
{
    stopGame();
    cleanupGame();
}

void GameScreen::onGameLoop()
{
    if (!m_isGameActive) return;
    
    m_build->updateCooldown(m_deltaTime);
    
    if (m_build->canAtack()) {
        Enemy* target = findNearestEnemy();
        if (target) {
            Missile* missile = m_factory->createMissile(target);
            missile->setPos(m_build->pos());
            m_scene->addItem(missile);
            m_missiles.append(missile);
            m_build->resetCooldown();
        }
    }

    for (Enemy* enemy : m_enemies) {
        enemy->move();
    }

    for (Missile* missile : m_missiles) {
        missile->fly();
    }

    m_collisionManager->checkMissileEnemyCollisions(m_missiles, m_enemies);
    m_collisionManager->checkBuildEnemyCollision(m_build, m_enemies);
}

Enemy* GameScreen::findNearestEnemy()
{
    Enemy* closest = nullptr;
    double minDistance = m_build->getRange();
    
    for (Enemy* enemy : m_enemies) {
        if (!enemy->isAlive()) continue;
        
        double dx = enemy->x() - m_build->x();
        double dy = enemy->y() - m_build->y();
        double distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance < minDistance) {
            minDistance = distance;
            closest = enemy;
        }
    }
    
    return closest;
}

void GameScreen::onEnemyToSpawn(QPointF spawnPos, QPointF targetPos)
{
    Enemy* enemy = m_factory->createEnemy(targetPos);
    enemy->setPos(spawnPos);
    m_scene->addItem(enemy);
    m_enemies.append(enemy);
    
    connect(enemy, &Enemy::died, this, &GameScreen::onEnemyDied);
}

void GameScreen::onEnemyDied(Enemy* enemy)
{
    m_enemies.removeOne(enemy);
    m_scene->removeItem(enemy);
    m_score += 10;

    if(m_waveManager) {
        m_waveManager->checkWaveComplete(m_enemies.size());
    }
}

void GameScreen::onMissileHit(Missile* missile, Enemy* enemy)
{
    enemy->takeDamage(missile->getDamage());
    m_missiles.removeOne(missile);
    m_scene->removeItem(missile);
    missile->deleteLater();
}

void GameScreen::onBuildHit(Enemy* enemy)
{
    m_lives--;
    m_enemies.removeOne(enemy);
    m_scene->removeItem(enemy);
    enemy->deleteLater();

    if (m_waveManager) {
        m_waveManager->checkWaveComplete(m_enemies.size());
    }

    if (m_lives <= 0) {
        gameOver();
    }
}

void GameScreen::onWaveComplete(int waveNumber) {}

void GameScreen::onGameWin()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    emit gameWon();
}

void GameScreen::gameOver()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    emit gameLost();
}

void GameScreen::cleanupGame()
{
    m_isGameActive = false;
    
    if (m_waveManager) {
        m_waveManager->deleteLater();
        m_waveManager = nullptr;
    }
    
    if (m_collisionManager) {
        m_collisionManager->deleteLater();
        m_collisionManager = nullptr;
    }
    
    if (m_build) {
        m_scene->removeItem(m_build);
        m_build->deleteLater();
        m_build = nullptr;
    }
    
    for (Enemy* enemy : m_enemies) {
        m_scene->removeItem(enemy);
        enemy->deleteLater();
    }
    m_enemies.clear();
    
    for (Missile* missile : m_missiles) {
        m_scene->removeItem(missile);
        missile->deleteLater();
    }
    m_missiles.clear();
    
    m_lives = 100;
    m_score = 0;
}
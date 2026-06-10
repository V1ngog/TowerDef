#include "gameprocessor.h"
#include "build.h"
#include "enemy.h"
#include "missile.h"
#include "wavemanager.h"
#include "collisionmanager.h"
#include "gamefactory.h"
#include <cmath>
#include <QDebug>

GameProcessor::GameProcessor(QObject *parent)
    : QObject(parent)
    , m_build(nullptr)
    , m_waveManager(nullptr)
    , m_collisionManager(nullptr)
    , m_factory(nullptr)
    , m_score(0)
    , m_coins(0)
    , m_addDamage(0)
    , m_totalDamage(0)
    , m_isGameActive(false)
    , m_deltaTime(TARGET_DELTA)
    , m_timeSinceLastFrame(0)
{
}

GameProcessor::~GameProcessor()
{
    cleanupGame();
    
    if (m_factory) {
        delete m_factory;
        m_factory = nullptr;
    }
}

void GameProcessor::setFactory(GameFactory* factory)
{
    if (m_factory && m_factory != factory) {
        delete m_factory;
    }
    m_factory = factory;
}

void GameProcessor::startGame()
{
    if (!m_factory) {
        return;
    }
    
    cleanupGame();
    
    m_build = m_factory->createBuild();
    m_build->setPos(400, 300);
    emit buildSpawned(m_build, m_build->pos());

    m_waveManager = new WaveManager(this);
    m_waveManager->setTowerPos(m_build->pos());
    m_collisionManager = new CollisionManager(this);
    
    setupConnections();
    
    m_score = 0;
    m_coins = 0;
    m_addDamage = 0;
    m_isGameActive = true;
    
    emit coinsChanged(m_coins, 0);
    emit scoreChanged(m_score, 0);
    emit gameStarted();
    
    m_waveManager->nextWave();
}

void GameProcessor::stopGame()
{
    m_isGameActive = false;
    if (m_waveManager) {
        m_waveManager->pause();
    }
    emit gameStopped();
}

void GameProcessor::resetGame()
{
    stopGame();
    cleanupGame();
    startGame();
}

void GameProcessor::setupConnections()
{
    if (!m_waveManager || !m_collisionManager || !m_build) return;
    
    connect(m_waveManager, &WaveManager::enemyToSpawn, 
            this, &GameProcessor::onEnemyToSpawn);
    connect(m_waveManager, &WaveManager::waveComplete, 
            this, &GameProcessor::onWaveComplete);
    connect(m_waveManager, &WaveManager::allWavesComplete, 
            this, &GameProcessor::onGameWin);
    
    connect(m_collisionManager, &CollisionManager::enemyHit, 
            this, &GameProcessor::onMissileHit);
    connect(m_collisionManager, &CollisionManager::buildHit, 
            this, &GameProcessor::onBuildHit);
    
    connect(m_build, &Build::destroy, this, &GameProcessor::onBuildDestroyed);
}

void GameProcessor::upgradeDamage()
{
    if (!canUpgradeDamage()) return;
    
    m_coins -= UPGRADE_COST;
    m_addDamage += UPGRADE_VALUE;
    updateTotalDamage();
    
    emit coinsChanged(m_coins, -UPGRADE_COST);
}

void GameProcessor::updateTotalDamage()
{
    if (m_build) {
        m_totalDamage = m_build->getDamage() + m_addDamage;
    }
}

void GameProcessor::addCoins(int amount)
{
    m_coins += amount;
    emit coinsChanged(m_coins, amount);
}

void GameProcessor::addScore(int amount)
{
    m_score += amount;
    emit scoreChanged(m_score, amount);
}

void GameProcessor::onGameLoop()
{
    if (!m_isGameActive) return;

    updateCooldown();
    attack();
    moveEnemies();
    moveMissiles();
    checkCollisions();
}

void GameProcessor::updateCooldown()
{
    if (m_build) {
        m_build->updateCooldown(m_deltaTime);
    }
}

void GameProcessor::attack()
{
    if (!m_build || !m_build->canAtack()) return;
    
    Enemy* target = findNearestEnemy();
    if (target) {
        Missile* missile = m_factory->createMissile(target);
        missile->setPos(m_build->pos());
        m_missiles.append(missile);
        
        emit missileSpawned(missile, missile->pos());
        m_build->resetCooldown();
    }
}

void GameProcessor::moveMissiles()
{
    for (Missile* missile : m_missiles) {
        missile->fly();
    }
}

void GameProcessor::moveEnemies()
{
    for (Enemy* enemy : m_enemies) {
        QPointF oldPos = enemy->pos();
        enemy->move();
        
        if (oldPos != enemy->pos()) {
            emit enemyMoved(enemy, enemy->pos());
        }
    }
}

void GameProcessor::checkCollisions()
{
    if (m_collisionManager) {
        m_collisionManager->checkMissileEnemyCollisions(m_missiles, m_enemies);
        m_collisionManager->checkBuildEnemyCollision(m_build, m_enemies);
    }
}

Enemy* GameProcessor::findNearestEnemy()
{
    if (!m_build) return nullptr;
    
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

void GameProcessor::onEnemyToSpawn(QPointF spawnPos, QPointF targetPos)
{
    Enemy* enemy = m_factory->createEnemy(targetPos);
    enemy->setPos(spawnPos);
    m_enemies.append(enemy);
    
    emit enemySpawned(enemy, spawnPos);
    connect(enemy, &Enemy::died, this, &GameProcessor::onEnemyDied);
}

void GameProcessor::onEnemyDied(Enemy* enemy)
{
    QPointF lastPos = enemy->pos();
    m_enemies.removeOne(enemy);
    
    addCoins(COINS_PER_KILL);
    addScore(SCORE_PER_KILL);
    
    emit enemyDied(enemy);
    
    if (m_waveManager) {
        m_waveManager->checkWaveComplete(m_enemies.size());
    }
}

void GameProcessor::onMissileHit(Missile* missile, Enemy* enemy)
{
    if (!missile->isActive()) return;
    
    float damage = missile->getDamage() + m_addDamage;
    enemy->takeDamage(damage);
    missile->deactivate();
    
    m_missiles.removeOne(missile);
    
    emit missileHit(missile);
}

void GameProcessor::onBuildHit(Enemy* enemy)
{
    if (!m_build) return;
    
    float buildDamage = m_build->getDamage();
    
    m_build->takeDamage(enemy->getDamage());
    enemy->takeDamage(buildDamage);
    
    emit buildDamageTaken(m_build->getHp());
}

void GameProcessor::onBuildDestroyed()
{
    m_isGameActive = false;
    emit buildDestroyed();
    emit gameLost();
}

void GameProcessor::onWaveComplete(int waveNumber)
{
    emit waveComplete(waveNumber);
}

void GameProcessor::onGameWin()
{
    m_isGameActive = false;
    emit allWavesComplete();
    emit gameWon();
}

void GameProcessor::cleanupGame()
{
    m_isGameActive = false;
    
    for (Enemy* enemy : m_enemies) {
        enemy->deleteLater();
    }
    m_enemies.clear();
    
    for (Missile* missile : m_missiles) {
        missile->deleteLater();
    }
    m_missiles.clear();
    
    if (m_waveManager) {
        m_waveManager->deleteLater();
        m_waveManager = nullptr;
    }
    
    if (m_collisionManager) {
        m_collisionManager->deleteLater();
        m_collisionManager = nullptr;
    }
    
    if (m_build) {
        m_build->deleteLater();
        m_build = nullptr;
    }
    
    m_score = 0;
    m_coins = 0;
    m_addDamage = 0;
    m_totalDamage = 0;
}
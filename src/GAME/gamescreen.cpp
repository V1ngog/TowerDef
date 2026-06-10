#include "gamescreen.h"
#include "gameprocessor.h"
#include "gamefactory.h"
#include "gamebutton.h"
#include "build.h"
#include "enemy.h"
#include "missile.h"
#include <QElapsedTimer>
#include <QDebug>

GameScreen::GameScreen(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(nullptr)
    , m_processor(nullptr)
    , m_upgradeButton(nullptr)
    , m_coinsText(nullptr)
    , m_scoreText(nullptr)
    , m_waveText(nullptr)
    , m_gameTimer(nullptr)
    , m_frameTimer(nullptr)
    , m_isGameActive(false)
    , m_deltaTime(0.033f)
{
    setupScene();
}

GameScreen::~GameScreen()
{
    cleanupGame();
    delete m_scene;
    delete m_frameTimer;
}

void GameScreen::setFactory(GameFactory* factory)
{
    if (!m_processor) {
        m_processor = new GameProcessor(this);
        
        connect(m_processor, &GameProcessor::buildSpawned, 
                this, &GameScreen::onBuildSpawned);
        connect(m_processor, &GameProcessor::buildDestroyed, 
                this, &GameScreen::onBuildDestroyed);
        connect(m_processor, &GameProcessor::buildDamageTaken, 
                this, &GameScreen::onBuildDamageTaken);
        
        connect(m_processor, &GameProcessor::enemySpawned, 
                this, &GameScreen::onEnemySpawned);
        connect(m_processor, &GameProcessor::enemyDied, 
                this, &GameScreen::onEnemyDied);
        connect(m_processor, &GameProcessor::enemyMoved, 
                this, &GameScreen::onEnemyMoved);
        
        connect(m_processor, &GameProcessor::missileSpawned, 
                this, &GameScreen::onMissileSpawned);
        connect(m_processor, &GameProcessor::missileHit, 
                this, &GameScreen::onMissileHit);
        connect(m_processor, &GameProcessor::missileDestroyed, 
                this, &GameScreen::onMissileDestroyed);
        
        connect(m_processor, &GameProcessor::coinsChanged, 
                this, &GameScreen::onCoinsChanged);
        connect(m_processor, &GameProcessor::scoreChanged, 
                this, &GameScreen::onScoreChanged);
        
        connect(m_processor, &GameProcessor::waveComplete, 
                this, &GameScreen::onWaveComplete);
        connect(m_processor, &GameProcessor::gameWon, 
                this, &GameScreen::onGameWon);
        connect(m_processor, &GameProcessor::gameLost, 
                this, &GameScreen::onGameLost);
    }
    
    m_processor->setFactory(factory);
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
    
    setupUI();
    
    m_gameTimer = new QTimer(this);
    m_gameTimer->setInterval(16);
    connect(m_gameTimer, &QTimer::timeout, this, &GameScreen::onGameLoop);
    
    m_frameTimer = new QElapsedTimer();
}

void GameScreen::setupUI()
{
    m_coinsText = new QGraphicsTextItem();
    m_coinsText->setDefaultTextColor(Qt::yellow);
    m_coinsText->setFont(QFont("Arial", 16, QFont::Bold));
    m_coinsText->setPos(10, 10);
    m_coinsText->setZValue(100);
    m_scene->addItem(m_coinsText);
    
    m_scoreText = new QGraphicsTextItem();
    m_scoreText->setDefaultTextColor(Qt::white);
    m_scoreText->setFont(QFont("Arial", 16, QFont::Bold));
    m_scoreText->setPos(10, 35);
    m_scoreText->setZValue(100);
    m_scene->addItem(m_scoreText);
    
    m_waveText = new QGraphicsTextItem();
    m_waveText->setDefaultTextColor(Qt::cyan);
    m_waveText->setFont(QFont("Arial", 16, QFont::Bold));
    m_waveText->setPos(10, 60);
    m_waveText->setZValue(100);
    m_scene->addItem(m_waveText);
    
    m_upgradeButton = new GameButton("Upgrade (+5)", nullptr);
    m_upgradeButton->setPos(10, 90);
    m_scene->addItem(m_upgradeButton);
    
    connect(m_upgradeButton, &GameButton::clicked, [this]() {
        if (m_processor) {
            m_processor->upgradeDamage();
        }
    });
    
}

void GameScreen::startGame()
{
    if (!m_processor) return;
    
    m_processor->startGame();
    m_isGameActive = true;
    m_frameTimer->start();
    m_gameTimer->start();
}

void GameScreen::stopGame()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    if (m_processor) {
        m_processor->stopGame();
    }
}

void GameScreen::resetGame()
{
    stopGame();
    cleanupGame();
    if (m_processor) {
        m_processor->resetGame();
    }
    
    startGame();
}

void GameScreen::onGameLoop()
{
    if (!m_isGameActive || !m_processor) return;
    
    if (m_frameTimer->isValid()) {
        m_deltaTime = m_frameTimer->elapsed() / 1000.0f;
    }
    m_frameTimer->restart();
    
    if (m_deltaTime > 0.033f) {
        m_deltaTime = 0.033f;
    }
    
    m_processor->updateDeltaTime(m_deltaTime);
    m_processor->onGameLoop();
}

void GameScreen::onBuildSpawned(Build* build, QPointF pos)
{
    m_scene->addItem(build);
    build->setPos(pos);
    
    m_buildHealthBar = new QGraphicsRectItem(0, 0, 60, 8);
    m_buildHealthBar->setBrush(Qt::green);
    m_buildHealthBar->setPos(pos.x() - 30, pos.y() - 35);
    m_scene->addItem(m_buildHealthBar);
}

void GameScreen::onBuildDestroyed()
{
    if (m_buildHealthBar) {
        m_scene->removeItem(m_buildHealthBar);
        delete m_buildHealthBar;
        m_buildHealthBar = nullptr;
    }
}

void GameScreen::onBuildDamageTaken(float currentHp)
{
    if (m_buildHealthBar) {
        float percent = currentHp / 50.0f;
        int width = static_cast<int>(60 * percent);
        if (width < 0) width = 0;
        
        QRectF rect = m_buildHealthBar->rect();
        rect.setWidth(width);
        m_buildHealthBar->setRect(rect);
        
        if (percent > 0.6f) {
            m_buildHealthBar->setBrush(Qt::green);
        } else if (percent > 0.3f) {
            m_buildHealthBar->setBrush(Qt::yellow);
        } else {
            m_buildHealthBar->setBrush(Qt::red);
        }
    }
}

void GameScreen::onEnemySpawned(Enemy* enemy, QPointF pos)
{
    m_scene->addItem(enemy);
    enemy->setPos(pos);
    
    m_enemyVisuals[enemy] = enemy;
}

void GameScreen::onEnemyDied(Enemy* enemy)
{
    if (m_enemyVisuals.contains(enemy)) {
        m_scene->removeItem(enemy);
        m_enemyVisuals.remove(enemy);
        enemy->deleteLater();
    }
}

void GameScreen::onEnemyMoved(Enemy* enemy, QPointF newPos)
{
    if (m_enemyVisuals.contains(enemy)) {
        enemy->setPos(newPos);
    }
}

void GameScreen::onMissileSpawned(Missile* missile, QPointF pos)
{
    m_scene->addItem(missile);
    missile->setPos(pos);
    m_missileVisuals[missile] = missile;
}

void GameScreen::onMissileHit(Missile* missile)
{
    if (m_missileVisuals.contains(missile)) {
        m_scene->removeItem(missile);
        m_missileVisuals.remove(missile);
        missile->deleteLater();
    }
}

void GameScreen::onMissileDestroyed(Missile* missile)
{
    if (m_missileVisuals.contains(missile)) {
        m_scene->removeItem(missile);
        m_missileVisuals.remove(missile);
        missile->deleteLater();
    }
}

void GameScreen::onCoinsChanged(int newCoins, int changeAmount)
{
    Q_UNUSED(changeAmount);
    m_coinsText->setPlainText(QString("Coins: %1").arg(newCoins));
}

void GameScreen::onScoreChanged(int newScore, int changeAmount)
{
    Q_UNUSED(changeAmount);
    m_scoreText->setPlainText(QString("Score: %1").arg(newScore));
}

void GameScreen::onWaveComplete(int waveNumber)
{
    m_waveText->setPlainText(QString("Wave: %1").arg(waveNumber));
}

void GameScreen::onGameWon()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    emit gameWon();
}

void GameScreen::onGameLost()
{
    m_isGameActive = false;
    m_gameTimer->stop();
    emit gameLost();
}

void GameScreen::cleanupGame()
{
    m_isGameActive = false;
    
    for (auto* enemy : m_enemyVisuals.keys()) {
        m_scene->removeItem(enemy);
    }
    m_enemyVisuals.clear();
    
    for (auto* missile : m_missileVisuals.keys()) {
        m_scene->removeItem(missile);
    }
    m_missileVisuals.clear();
    
    if (m_buildHealthBar) {
        m_scene->removeItem(m_buildHealthBar);
        delete m_buildHealthBar;
        m_buildHealthBar = nullptr;
    }
}
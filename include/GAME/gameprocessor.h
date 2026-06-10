#ifndef GAMEPROCESSOR_H
#define GAMEPROCESSOR_H

#include <QObject>
#include <QList>
#include <QPointF>

class Build;
class Enemy;
class Missile;
class WaveManager;
class CollisionManager;
class GameFactory;

class GameProcessor : public QObject
{
    Q_OBJECT

public:
    explicit GameProcessor(QObject *parent = nullptr);
    ~GameProcessor();
    
    void setFactory(GameFactory* factory);
    void startGame();
    void stopGame();
    void resetGame();
    void updateDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

    QList<Enemy*> getEnemies() const { return m_enemies; }
    QList<Missile*> getMissiles() const { return m_missiles; }
    Build* getBuild() const { return m_build; }
    int getScore() const { return m_score; }
    int getCoins() const { return m_coins; }
    float getAddDamage() const { return m_addDamage; }
    
    void upgradeDamage();
    bool canUpgradeDamage() const { return m_coins >= 50; }
    int getUpgradeCost() const { return 50; }
    int getUpgradeValue() const { return 5; }

signals:
    void gameStarted();
    void gameStopped();
    void gameWon();
    void gameLost();

    void buildSpawned(Build* build, QPointF pos);
    void buildDestroyed();
    void buildDamageTaken(float currentHp);
    
    void enemySpawned(Enemy* enemy, QPointF pos);
    void enemyDied(Enemy* enemy);
    void enemyMoved(Enemy* enemy, QPointF newPos);
    
    void missileSpawned(Missile* missile, QPointF pos);
    void missileHit(Missile* missile);
    void missileDestroyed(Missile* missile);
    
    void coinsChanged(int newCoins, int changeAmount);
    void scoreChanged(int newScore, int changeAmount);
    void waveChanged(int waveNumber, int enemiesLeft, int totalEnemies);
    
    void waveStarted(int waveNumber);
    void waveComplete(int waveNumber);
    void allWavesComplete();

public slots:
    void onGameLoop();

private slots:
    void onEnemyToSpawn(QPointF spawnPos, QPointF targetPos);
    void onEnemyDied(Enemy* enemy);
    void onMissileHit(Missile* missile, Enemy* enemy);
    void onBuildHit(Enemy* enemy);
    void onBuildDestroyed();
    void onWaveComplete(int waveNumber);
    void onGameWin();

private:
    void cleanupGame();
    void setupConnections();
    void updateCooldown();
    void attack();
    void moveEnemies();
    void moveMissiles();
    void checkCollisions();
    Enemy* findNearestEnemy();
    void updateTotalDamage();
    void addCoins(int amount);
    void addScore(int amount);
    
    Build* m_build;
    WaveManager* m_waveManager;
    CollisionManager* m_collisionManager;
    GameFactory* m_factory;
    
    QList<Enemy*> m_enemies;
    QList<Missile*> m_missiles;
    
    int m_score;
    int m_coins;
    float m_addDamage;
    float m_totalDamage;
    bool m_isGameActive;
    float m_deltaTime;
    float m_timeSinceLastFrame;
    
    static constexpr int UPGRADE_COST = 50;
    static constexpr int UPGRADE_VALUE = 5;
    static constexpr int COINS_PER_KILL = 10;
    static constexpr int SCORE_PER_KILL = 10;
    static constexpr float TARGET_FPS = 60.0f;
    static constexpr float TARGET_DELTA = 1.0f / TARGET_FPS;
};

#endif
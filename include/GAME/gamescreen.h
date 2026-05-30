#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>

class GameButton;
class Build;
class Enemy;
class Missile;
class WaveManager;
class CollisionManager;
class GameFactory;

class GameScreen : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

    void setFactory(GameFactory* factory);
    void startGame();
    void stopGame();
    void resetGame();   

signals:
    void gameWon();
    void gameLost();

private slots:
    void onGameLoop();
    void onEnemyToSpawn(QPointF spawnPos, QPointF targetPos);
    void onEnemyDied(Enemy* enemy);
    void onMissileHit(Missile* missile, Enemy* enemy);
    void onBuildHit(Enemy* enemy);
    void onWaveComplete(int waveNumber);
    void onGameWin();
    void onMissileRemove(Missile *missile);
    void onUpgradeDamageClicked();

private:
    void setupUI();
    void updateUI();
    void setupScene();
    void cleanupGame();
    void gameOver();
    Enemy* findNearestEnemy();

    QGraphicsScene* m_scene;
    Build* m_build;
    WaveManager* m_waveManager;
    CollisionManager* m_collisionManager;
    GameFactory* m_factory;
    GameButton* m_addDamageButton;
    QGraphicsTextItem* m_coinsText;
    
    QList<Enemy*> m_enemies;
    QList<Missile*> m_missiles;
    
    QTimer* m_gameTimer;
    int m_lives;
    int m_score;
    int m_coins;
    float m_addDamage;
    bool m_isGameActive;
    float m_deltaTime;
};

#endif
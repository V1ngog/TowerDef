#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

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
    void onPageEnter();
    void onPageExit();

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

private:
    void setupScene();
    void cleanupGame();
    void gameOver();
    Enemy* findNearestEnemy();

    QGraphicsScene* m_scene;
    Build* m_build;
    WaveManager* m_waveManager;
    CollisionManager* m_collisionManager;
    GameFactory* m_factory;
    
    QList<Enemy*> m_enemies;
    QList<Missile*> m_missiles;
    
    QTimer* m_gameTimer;
    int m_lives;
    int m_score;
    bool m_isGameActive;
    float m_deltaTime;
};

#endif
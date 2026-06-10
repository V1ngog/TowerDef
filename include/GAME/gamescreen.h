#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QMap>
#include <QElapsedTimer>

class GameButton;
class Build;
class Enemy;
class Missile;
class GameProcessor;
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
    
    void onBuildSpawned(Build* build, QPointF pos);
    void onBuildDestroyed();
    void onBuildDamageTaken(float currentHp);
    
    void onEnemySpawned(Enemy* enemy, QPointF pos);
    void onEnemyDied(Enemy* enemy);
    void onEnemyMoved(Enemy* enemy, QPointF newPos);
    
    void onMissileSpawned(Missile* missile, QPointF pos);
    void onMissileHit(Missile* missile);
    void onMissileDestroyed(Missile* missile);
    
    void onCoinsChanged(int newCoins, int changeAmount);
    void onScoreChanged(int newScore, int changeAmount);
    
    void onWaveComplete(int waveNumber);
    void onGameWon();
    void onGameLost();

private:
    void setupScene();
    void setupUI();
    void cleanupGame();
    
    QMap<Enemy*, QGraphicsPixmapItem*> m_enemyVisuals;
    QMap<Missile*, QGraphicsPixmapItem*> m_missileVisuals;
    QGraphicsRectItem* m_buildHealthBar;
    
    QGraphicsScene* m_scene;
    GameProcessor* m_processor;
    GameButton* m_upgradeButton;
    QGraphicsTextItem* m_coinsText;
    QGraphicsTextItem* m_scoreText;
    QGraphicsTextItem* m_waveText;
    
    QTimer* m_gameTimer;
    QElapsedTimer* m_frameTimer;
    
    bool m_isGameActive;
    float m_deltaTime;
};

#endif
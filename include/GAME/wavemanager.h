#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QPointF>
#include "enemy.h"

class WaveManager : public QObject
{
    Q_OBJECT

public:
    explicit WaveManager(QObject *parent = nullptr);

    void start() { m_spawnTimer->start(m_spawnDelay) ;}
    void pause() { m_spawnTimer->stop(); }
    void reset();
    void nextWave();
    void setTowerPos(const QPointF& pos) { m_towerPos = pos; }

    int getCurrentWave() const { return m_currentWave; }
    int getEnemiesLeft() const { return m_enemiesInWave - m_enemiesSpawned; }

signals:
    void enemyToSpawn(QPointF spawnPos, QPointF targetPos);
    void waveComplete(int waveNumber);
    void allWavesComplete();

private slots:
    void spawnNextEnemy();
    
private:
    QPointF getRandomSpawnPosition();
    
    QTimer* m_spawnTimer;
    QPointF m_towerPos;
    
    int m_currentWave;
    int m_enemiesInWave;
    int m_enemiesSpawned;
    int m_spawnDelay;
};
#endif
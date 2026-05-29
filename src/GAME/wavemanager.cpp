#include <QRandomGenerator>
#include <cmath>
#include "wavemanager.h"

WaveManager::WaveManager(QObject *parent)
    : QObject(parent)
    , m_spawnTimer(new QTimer(this))
    , m_currentWave(0)
    , m_enemiesInWave(0)
    , m_enemiesSpawned(0)
    , m_spawnDelay(1500)
{
    connect(m_spawnTimer, &QTimer::timeout, this, &WaveManager::spawnNextEnemy);
}

void WaveManager::reset()
{
    pause();
    m_currentWave = 0;
    m_enemiesInWave = 0;
    m_enemiesSpawned = 0;
    m_spawnDelay = 1500;
}

void WaveManager::nextWave()
{
    m_currentWave++;
    m_enemiesInWave = 3 + m_currentWave * 2;
    m_enemiesSpawned = 0;
    m_spawnDelay = std::max(500, 2000 - m_currentWave * 100);
    start();
}

void WaveManager::checkWaveComplete(int aliveEnemies)
{
    if (m_enemiesSpawned >= m_enemiesInWave && aliveEnemies == 0) {
        if (m_currentWave >= 10) {
            emit allWavesComplete();
        } else {
            emit waveComplete(m_currentWave);
            nextWave();
        }
    }
}

QPointF WaveManager::getRandomSpawnPosition()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int OFFSET = 50; 

    int side = QRandomGenerator::global()->bounded(4);
    
    switch (side) {
    case 0: // верх
        return QPointF(QRandomGenerator::global()->bounded(WIDTH), -OFFSET);
    case 1: // право
        return QPointF(WIDTH + OFFSET, QRandomGenerator::global()->bounded(HEIGHT));
    case 2: // низ
        return QPointF(QRandomGenerator::global()->bounded(WIDTH), HEIGHT + OFFSET);
    default: // лево
        return QPointF(-OFFSET, QRandomGenerator::global()->bounded(HEIGHT));
    }
}

void WaveManager::spawnNextEnemy()
{
    if(m_enemiesSpawned >= m_enemiesInWave) {
        m_spawnTimer->stop();
        return;
    }
    
    QPointF spawnPos = getRandomSpawnPosition();
    emit enemyToSpawn(spawnPos, m_towerPos);
    m_enemiesSpawned++;
}
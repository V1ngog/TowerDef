#include "weaktower.h"

WeakTower::WeakTower()
{
    m_range = 150;
    m_damage = 150;
    m_hp = 1000.0f;
    m_cooldownTime = 1.0f;
    m_currentCooldown = 0.0f;
    setupVisual();
}

void WeakTower::setupVisual()
{
    QPixmap pixmap(40, 40);
    pixmap.fill(Qt::gray);
    setPixmap(pixmap);
    setTransformOriginPoint(20, 20);
}
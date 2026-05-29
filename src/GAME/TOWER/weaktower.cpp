#include "WeakTower.h"

WeakTower::WeakTower()
{
    m_range = 120;
    m_cooldownTime = 0.8f;
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
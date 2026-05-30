#include "strongtower.h"

StrongTower::StrongTower()
{
    m_range = 150;
    m_damage = 150;
    m_hp = 300.0f;
    m_cooldownTime = 1.0f;
    m_currentCooldown = 0.0f;
    setupVisual();
}

void StrongTower::setupVisual()
{
    QPixmap pixmap(60, 60);
    pixmap.fill(Qt::darkBlue);
    setPixmap(pixmap);
    setTransformOriginPoint(30, 30);
}
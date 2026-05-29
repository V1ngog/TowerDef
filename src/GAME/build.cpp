#include "build.h"

Build::Build(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {}


void Build::updateCooldown(float deltaTime)
{
    if (m_currentCooldown > 0) {
        m_currentCooldown -= deltaTime;
    }
}

bool Build::canAtack() const
{
    return m_currentCooldown <= 0;
}

void Build::resetCooldown()
{
    m_currentCooldown = m_cooldownTime;
}

void Build::takeDamage(float damage)
{
    m_hp -= damage;

    if (m_hp <= 0) {
        emit destroy(); 
    }
}
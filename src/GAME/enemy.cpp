#include "enemy.h"
#include <cmath>

Enemy::Enemy(QPointF targetPos, QGraphicsItem *parent) 
    : QGraphicsPixmapItem(parent)
    , m_target(targetPos) {}

void Enemy::move()
{
    QPointF direction = m_target - pos();

    double length  = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (length  > 0) {
        direction /= length;
        setPos(pos() + direction * m_speed);
    }
}

void Enemy::takeDamage(float damage)
{
    m_hp -= damage;

    if (m_hp <= 0) {
        emit died(this);
    }
}

#include "enemy.h"
#include <cmath>

Enemy::Enemy(QPointF targetPos, float hp, float speed, QGraphicsItem *parent = nullptr) 
    : QGraphicsPixmapItem(parent)
    , m_target(targetPos)
    , m_hp(hp)
    , m_speed(speed)
{
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::red);
    setPixmap(pixmap);
    
    setTransformOriginPoint(15, 15);
}

void Enemy::move()
{
    QPointF direction = m_target - pos();

    double dx = direction.x();
    double dy = direction.y();
    double distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        direction.setX(dx / distance);
        direction.setY(dy / distance);
        
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
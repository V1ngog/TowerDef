#include "missile.h"
#include <cmath>

Missile::Missile(Enemy *target, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , m_target(target) {}

void Missile::fly()
{
    if (!m_target) return;
    
    QPointF direction = m_target->pos() - pos();
    
    double length  = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

    if (length  > 0) {
        direction /= length;
        setPos(pos() + direction * m_speed);
    }
}
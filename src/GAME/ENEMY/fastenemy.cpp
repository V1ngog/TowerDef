#include "fastenemy.h"

FastEnemy::FastEnemy(QPointF targetPos) : Enemy(targetPos) {
        m_hp = 20;
        m_damage = 5.0f;
        m_speed = 10.0f;
        setupVisual();
    }

void FastEnemy::setupVisual() {
        QPixmap pixmap(25, 25);
        pixmap.fill(Qt::red);
        setPixmap(pixmap);
        setTransformOriginPoint(12, 12);
    }
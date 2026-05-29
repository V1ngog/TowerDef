#include "slowenemy.h"

SlowEnemy::SlowEnemy(QPointF targetPos) : Enemy(targetPos) {
        m_hp = 50;
        m_damage = 2.5f;
        m_speed = 10.0f;
        setupVisual();
    }

void SlowEnemy::setupVisual() {
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::darkRed);
        setPixmap(pixmap);
        setTransformOriginPoint(20, 20);
    }
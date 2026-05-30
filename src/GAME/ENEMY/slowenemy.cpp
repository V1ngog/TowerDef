#include "slowenemy.h"

SlowEnemy::SlowEnemy(QPointF targetPos) : Enemy(targetPos) {
        m_hp = 10;
        m_damage = 2.5f;
        m_speed = 5.0f;
        setupVisual();
    }

void SlowEnemy::setupVisual() {
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::darkRed);
        setPixmap(pixmap);
        setTransformOriginPoint(20, 20);
    }
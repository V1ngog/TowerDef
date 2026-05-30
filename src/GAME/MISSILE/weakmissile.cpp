#include "weakmissile.h"

WeakMissile::WeakMissile(Enemy* target) : Missile(target) {
        m_damage = 7;
        m_speed = 15.0f;
        m_active = true;
        setupVisual();
    }

void WeakMissile::setupVisual() {
        QPixmap pixmap(8, 8);
        pixmap.fill(Qt::yellow);
        setPixmap(pixmap);
        setTransformOriginPoint(4, 4);
    }
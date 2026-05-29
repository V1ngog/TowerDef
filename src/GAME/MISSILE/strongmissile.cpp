#include "strongmissile.h"

StrongMissile::StrongMissile(Enemy* target) : Missile(target) {
        m_damage = 2;
        m_speed = 11.0f;
        m_active = true;
        setupVisual();
    }

void StrongMissile::setupVisual() {
        QPixmap pixmap(12, 12);
        pixmap.fill(QColor(255, 165, 0));
        setPixmap(pixmap);
        setTransformOriginPoint(6, 6);
    }
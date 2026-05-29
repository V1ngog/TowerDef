#ifndef MISSILE_H
#define MISSILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include "enemy.h"

class Missile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Missile(Enemy *target, QGraphicsItem *parent = nullptr);
    virtual ~Missile() {}

    virtual void fly();

    void hit();
    float getDamage() { return m_damage; }
    bool isActive() const { return m_active; }
    void deactivate() { m_active = false; }

signals:
    void remove(Missile *missile);

protected:
    Enemy *m_target;
    float m_damage;
    float m_speed;
    bool m_active = true;

    virtual void setupVisual() = 0;
    
};
#endif
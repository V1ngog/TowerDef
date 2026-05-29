#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Enemy(QPointF targetPos, QGraphicsItem *parent = nullptr);
    virtual ~Enemy() {}

    virtual void move();
    virtual void takeDamage(float damage);

    int getHp() const { return m_hp; }
    int getDamage() const { return m_damage; }
    bool isAlive() const { return m_hp > 0; }
    
signals:
    void died(Enemy *enemy);

protected:
    QPointF m_target;
    float m_damage;
    float m_hp;
    float m_speed;

    virtual void setupVisual() = 0;

};
#endif
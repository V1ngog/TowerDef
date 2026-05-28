#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Enemy(QPointF targetPos, float hp, float speed, QGraphicsItem *parent = nullptr);
    virtual ~Enemy() {}

    virtual void move();
    virtual void takeDamage(float damage);

    int getHp() const { return m_hp; }
    
signals:
    void died(Enemy *enemy);

private:
    QPointF m_target;
    float m_hp;
    float m_speed;

};
#endif
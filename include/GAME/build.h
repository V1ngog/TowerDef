#ifndef BUILD_H
#define BUILD_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Build : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Build(QGraphicsItem *parent = nullptr);
    virtual ~Build() {}

    virtual void updateCooldown(float deltaTime);
    virtual bool canAtack() const;
    virtual void resetCooldown();
    virtual void takeDamage(float damage);
    
    float getDamage() const { return m_damage; }
    float getHp() const { return m_hp; }
    int getRange() const { return m_range; }

signals:
    void destroy();

protected:
    int m_range = 0;
    float m_hp = 0;
    float m_damage = 0;
    float m_cooldownTime = 0.0f;
    float m_currentCooldown = 0.0f;

    virtual void setupVisual() = 0;
};

#endif
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
    
    int getRange() const { return m_range; }

protected:
    int m_range = 0;
    float m_cooldownTime = 0.0f;
    float m_currentCooldown = 0.0f;

    virtual void setupVisual() = 0;
};

#endif
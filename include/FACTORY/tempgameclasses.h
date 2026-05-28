#ifndef TEMPGAMECLASSES_H
#define TEMPGAMECLASSES_H

#include "build.h"
#include "enemy.h"
#include "missile.h"
#include <QPixmap>
#include <cmath>

// ========== БАШНИ ==========

class WeakTower : public Build
{
public:
    WeakTower() {
        m_range = 400;
        m_damage = 40;
        m_cooldownTime = 0.1f;
        m_currentCooldown = 0.0f;
        setupVisual();
    }
    
    void updateCooldown(float deltaTime) override {
        if (m_currentCooldown > 0) m_currentCooldown -= deltaTime;
    }
    
    bool canAtack() const override {
        return m_currentCooldown <= 0;
    }
    
    void resetCooldown() override {
        m_currentCooldown = m_cooldownTime;
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::gray);
        setPixmap(pixmap);
        setTransformOriginPoint(20, 20);
    }
};

class StrongTower : public Build
{
public:
    StrongTower() {
        m_range = 400;
        m_damage = 40;
        m_cooldownTime = 0.1f;
        m_currentCooldown = 0.0f;
        setupVisual();
    }
    
    void updateCooldown(float deltaTime) override {
        if (m_currentCooldown > 0) m_currentCooldown -= deltaTime;
    }
    
    bool canAtack() const override {
        return m_currentCooldown <= 0;
    }
    
    void resetCooldown() override {
        m_currentCooldown = m_cooldownTime;
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(60, 60);
        pixmap.fill(Qt::darkBlue);
        setPixmap(pixmap);
        setTransformOriginPoint(30, 30);
    }
};

// ========== ВРАГИ ==========

class FastEnemy : public Enemy
{
public:
    FastEnemy(QPointF targetPos) : Enemy(targetPos) {
        m_hp = 2;
        m_speed = 1.0f;
        setupVisual();
    }
    
    void move() override {
        QPointF direction = m_target - pos();
        double length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            direction /= length;
            setPos(pos() + direction * m_speed);
        }
    }
    
    void takeDamage(float damage) override {
        m_hp -= damage;
        if (m_hp <= 0) {
            emit died(this);
            deleteLater();
        }
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(25, 25);
        pixmap.fill(Qt::red);
        setPixmap(pixmap);
        setTransformOriginPoint(12, 12);
    }
};

class SlowEnemy : public Enemy
{
public:
    SlowEnemy(QPointF targetPos) : Enemy(targetPos) {
        m_hp = 5;
        m_speed = 1.0f;
        setupVisual();
    }
    
    void move() override {
        QPointF direction = m_target - pos();
        double length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            direction /= length;
            setPos(pos() + direction * m_speed);
        }
    }
    
    void takeDamage(float damage) override {
        m_hp -= damage;
        if (m_hp <= 0) {
            emit died(this);
            deleteLater();
        }
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::darkRed);
        setPixmap(pixmap);
        setTransformOriginPoint(20, 20);
    }
};

// ========== РАКЕТЫ ==========

class WeakMissile : public Missile
{
public:
    WeakMissile(Enemy* target) : Missile(target) {
        m_damage = 50;
        m_speed = 15.0f;
        m_active = true;
        setupVisual();
    }
    
    void fly() override {
        if (!m_target || !m_target->isAlive()) {
            deleteLater();
            return;
        }
        
        QPointF direction = m_target->pos() - pos();
        double length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            direction /= length;
            setPos(pos() + direction * m_speed);
        }
        
        if (length < 10) {
            deactivate();
        }
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(8, 8);
        pixmap.fill(Qt::yellow);
        setPixmap(pixmap);
        setTransformOriginPoint(4, 4);
    }
};

class StrongMissile : public Missile
{
public:
    StrongMissile(Enemy* target) : Missile(target) {
        m_damage = 200;
        m_speed = 11.0f;
        m_active = true;
        setupVisual();
    }
    
    void fly() override {
        if (!m_target || !m_target->isAlive()) {
            deleteLater();
            return;
        }
        
        QPointF direction = m_target->pos() - pos();
        double length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
        if (length > 0) {
            direction /= length;
            setPos(pos() + direction * m_speed);
        }
        
        if (length < 10) {
            deactivate();
        }
    }

protected:
    void setupVisual() override {
        QPixmap pixmap(12, 12);
        pixmap.fill(QColor(255, 165, 0));  // оранжевый
        setPixmap(pixmap);
        setTransformOriginPoint(6, 6);
    }
};

#endif
// factories.h
#ifndef FACTORIES_H
#define FACTORIES_H

#include "gamefactory.h"
#include "tempgameclasses.h"

// Лёгкая фабрика (сложность: лёгкая)
class EasyFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new StrongTower();  // крепкая башня
    }
    
    Enemy* createEnemy(QPointF targetPos) override {
        return new SlowEnemy(targetPos);  // медленные враги
    }
    
    Missile* createMissile(Enemy* target) override {
        return new StrongMissile(target);  // сильные ракеты
    }
};

// Тяжёлая фабрика (сложность: тяжёлая)
class HardFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new WeakTower();  // слабая башня
    }
    
    Enemy* createEnemy(QPointF targetPos) override {
        return new FastEnemy(targetPos);  // быстрые враги
    }
    
    Missile* createMissile(Enemy* target) override {
        return new WeakMissile(target);  // слабые ракеты
    }
};

// Средняя фабрика (сложность: средняя)
class MediumFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new StrongTower();  // крепкая башня
    }
    
    Enemy* createEnemy(QPointF targetPos) override {
        return new FastEnemy(targetPos);  // быстрые враги
    }
    
    Missile* createMissile(Enemy* target) override {
        return new WeakMissile(target);  // слабые ракеты
    }
};

#endif
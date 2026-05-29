#ifndef FACTORIES_H
#define FACTORIES_H

#include "gamefactory.h"
#include "slowenemy.h"
#include "fastenemy.h"
#include "strongtower.h"
#include "weaktower.h"
#include "strongmissile.h"
#include "weakmissile.h"

class EasyFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new StrongTower();  
    }

    Enemy* createEnemy(QPointF targetPos) override {
        return new SlowEnemy(targetPos);  
    }

    Missile* createMissile(Enemy* target) override {
        return new StrongMissile(target);  
    }
};

class HardFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new WeakTower();  
    }

    Enemy* createEnemy(QPointF targetPos) override {
        return new FastEnemy(targetPos);  
    }

    Missile* createMissile(Enemy* target) override {
        return new WeakMissile(target);  
    }
};

class MediumFactory : public GameFactory
{
public:
    Build* createBuild() override {
        return new StrongTower();  
    }
    
    Enemy* createEnemy(QPointF targetPos) override {
        return new FastEnemy(targetPos);  
    }
    
    Missile* createMissile(Enemy* target) override {
        return new WeakMissile(target);  
    }
};

#endif
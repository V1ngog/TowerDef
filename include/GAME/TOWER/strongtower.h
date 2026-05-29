#ifndef STRONGTOWER_H
#define STRONGTOWER_H

#include "build.h"

class StrongTower : public Build
{
public:
    StrongTower();

protected:
    void setupVisual() override;
};
#endif
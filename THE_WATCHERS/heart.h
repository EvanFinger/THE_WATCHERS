#ifndef HEART_H
#define HEART_H

#include "Entity.h"

class heart :
    public Entity
{
private:

public:
    heart(float x, float y, sf::Texture& texture_sheet);
    virtual ~heart();

    virtual void update(const float &dt);

    
};

#endif

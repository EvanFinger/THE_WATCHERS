#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables

    //Init Functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y,int max_health, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    virtual void update(const float& dt);
};


#endif

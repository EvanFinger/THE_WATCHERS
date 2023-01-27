#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Entity.h"
#include "heart.h"

class HealthBar :
    public Entity
{
private:
    //init
    int heartInitializationSpacer;
    sf::Texture& heartTextureSheet;
    std::map<int, heart*> hearts;
    void initComponents();
public:
    
    int maxHealth;
    int health;

    HealthBar(unsigned int max_health, float x, float y, sf::Texture& texture_sheet);
    virtual ~HealthBar();

    virtual void update(const float& dt);

    virtual void render(sf::RenderTarget* target);
};

#endif

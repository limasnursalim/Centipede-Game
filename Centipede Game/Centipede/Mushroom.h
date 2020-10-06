//
// Created by Edwin Lau Mack on 5/2/20.
//

#ifndef CENTIPEDE_MUSHROOM_H
#define CENTIPEDE_MUSHROOM_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Mushroom : public sf::Drawable
{
private:
    sf::Sprite mushroom;
    sf::Texture texture;
    Animation mushroom1Animation;


public:
    Mushroom(sf::Texture& texture);
    Mushroom(std::string filepath);
    void draw(sf::RenderTarget& window,sf::RenderStates state)const;
    void Update();
    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);

    sf::Sprite& getSprite();
    Animation getAnimation1()
    {
        return mushroom1Animation;
    }
};


#endif //CENTIPEDE_MUSHROOM_H

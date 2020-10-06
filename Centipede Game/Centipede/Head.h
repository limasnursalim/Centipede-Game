//
// Created by Edwin Lau Mack on 5/2/20.
//

#ifndef CENTIPEDE_HEAD_H
#define CENTIPEDE_HEAD_H

#include <SFML/Graphics.hpp>
#include "Animation.h"


class Head : public sf::Drawable
{

private:
    sf::Sprite centipedeHead;
    Animation WalkingLeft;
    Animation WalkingRight;
    Animation WalkingDown;
    sf::Texture texture;
    sf::Texture texture2;
    bool destroyed;


public:
    Head(std::string filepath1,std::string filepath2);
    sf::Sprite& getHead();
    void move(sf::Vector2f velocity);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void setSize(sf::Vector2f size);
    void draw(sf::RenderTarget& window,sf::RenderStates state)const;

    sf::Vector2f getSize() {return centipedeHead.getScale();}

};


#endif //CENTIPEDE_HEAD_H

//
// Created by Edwin Lau Mack on 5/2/20.
//

#include "Head.h"
Head::Head(std::string filepath1,std::string filepath2) : WalkingDown(0,8, 8, 8), WalkingLeft(0,0,8,8), WalkingRight(32,8,8,8)
{
    texture.loadFromFile(filepath1);
    texture2.loadFromFile(filepath2);
    centipedeHead.setTexture(texture);
    WalkingDown.ApplyToSprite(centipedeHead);
    destroyed = false;
}

sf::Sprite& Head::getHead()
{
    return centipedeHead;
}

void Head::move(sf::Vector2f velocity)
{
    centipedeHead.move(velocity);
}

sf::Vector2f Head::getPosition()
{
    return centipedeHead.getPosition();
}

void Head::setPosition(sf::Vector2f pos)
{
    centipedeHead.setPosition(pos);
}

void Head::setSize(sf::Vector2f size)
{
    centipedeHead.setScale(size);
}


void Head::draw(sf::RenderTarget& window,sf::RenderStates state)const
{
    window.draw(centipedeHead);
}

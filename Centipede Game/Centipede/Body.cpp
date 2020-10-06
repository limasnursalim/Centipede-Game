//
// Created by anggo on 6/8/2020.
//
//
// Created by Edwin Lau Mack on 5/2/20.
//

#include "Body.h"
Body::Body(std::string filepath1) : WalkingDown(0,8, 8, 8), WalkingLeft(0,0,8,8), WalkingRight(32,8,8,8)
{
    texture.loadFromFile(filepath1);
    centipedeHead.setTexture(texture);
    WalkingDown.ApplyToSprite(centipedeHead);
    destroyed = false;
}

sf::Sprite& Body::getHead()
{
    return centipedeHead;
}

void Body::move(sf::Vector2f velocity)
{
    centipedeHead.move(velocity);
}

sf::Vector2f Body::getPosition()
{
    return centipedeHead.getPosition();
}

void Body::setPosition(sf::Vector2f pos)
{
    centipedeHead.setPosition(pos);
}

void Body::setSize(sf::Vector2f size)
{
    centipedeHead.setScale(size);
}


void Body::draw(sf::RenderTarget& window,sf::RenderStates state)const
{
    window.draw(centipedeHead);
}

void Body::Update(float dt, sf::Vector2f dir)
{

    if (dir.x < 0.0f && dir.y == 0.0f)
    {
        centipedeHead.setTexture(texture);
        WalkingLeft.ApplyToSprite(centipedeHead);
        WalkingLeft.animatedUpdate(dt);
    }

    if (dir.x > 0.0f && dir.y == 0.0f)
    {
        centipedeHead.setTexture(texture2);
        WalkingRight.ApplyToSprite(centipedeHead);
        WalkingRight.animatedUpdate(dt);
    }

    if (dir.y > 0.0f && dir.x == 0.0f)
    {
        centipedeHead.setTexture(texture);
        WalkingDown.ApplyToSprite(centipedeHead);
        WalkingDown.animatedUpdate(dt);
    }
}



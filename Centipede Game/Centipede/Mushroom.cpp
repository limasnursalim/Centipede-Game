//
// Created by Edwin Lau Mack on 5/2/20.
//

#include "Mushroom.h"

Mushroom::Mushroom(sf::Texture& texture) : mushroom1Animation(0,0,16,16)
{
    mushroom.setTexture(texture);
    mushroom1Animation.ApplyToSprite(mushroom);
}

Mushroom::Mushroom(std::string filepath): mushroom1Animation(0,0,16,16)
{
    texture.loadFromFile(filepath);
    mushroom.setTexture(texture);
    mushroom1Animation.ApplyToSprite(mushroom);
}


void Mushroom::draw(sf::RenderTarget& window,sf::RenderStates state)const
{
    window.draw(mushroom);

}

void Mushroom::Update()
{
    mushroom1Animation.Update();
    mushroom1Animation.ApplyToSprite(mushroom);
}

void Mushroom::setPosition(sf::Vector2f pos)
{
    mushroom.setPosition(pos);
}

void Mushroom::setSize(sf::Vector2f size)
{
    mushroom.setScale(size);
}

sf::Sprite& Mushroom::getSprite()
{
    return mushroom;
}
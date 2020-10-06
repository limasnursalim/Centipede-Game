//
// Created by anggo on 6/10/2020.
//

#include "Health.h"

Health::Health(std::string filepath)
{
    texture.loadFromFile(filepath);
    healthIcon.setTexture(texture);
}

void Health::draw(sf::RenderTarget& window,sf::RenderStates state) const
{
    window.draw(healthIcon);
}

void Health::setSize(sf::Vector2f size)
{
    healthIcon.setScale(size);
}

void Health::setPosition(sf::Vector2f pos)
{
    healthIcon.setPosition(pos);
}
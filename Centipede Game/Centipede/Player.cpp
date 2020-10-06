//
// Created by Edwin Lau Mack on 5/2/20.
//

#include "Player.h"
#include <iostream>

Player::Player(std::string filepath)
{
    playerTexture.loadFromFile(filepath);
    blaster.setTexture(playerTexture);
}

Player::Player(sf::Texture& texture)
{
    blaster.setTexture(texture);
}

void Player::move(sf::Vector2f velocity)
{
    blaster.move(velocity);
}

void Player::setPos(sf::Vector2f pos)
{
    blaster.setPosition(pos);
}

void Player::setSize(sf::Vector2f size)
{
    blaster.setScale(size);
}

void Player::draw(sf::RenderTarget& window,sf::RenderStates state)const
{
    window.draw(blaster);
}

sf::Sprite Player::getSprite() const
{
    return blaster;
}

sf::Vector2f Player::getPosition()
{
    return blaster.getPosition();
}
//
//std::vector<Bullet>& Player::getBullets()
//{
//    return playerBullets;
//}
int Player::getHP()
{
    return HP;
}

void Player::plusHP()
{
    HP++;
}


void Player::minusHP()
{
    HP--;
}


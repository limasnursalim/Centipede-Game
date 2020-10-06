//
// Created by Edwin Lau Mack on 5/2/20.
//

#ifndef CENTIPEDE_PLAYER_H
#define CENTIPEDE_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player :public sf::Drawable
{
private:
    sf::Sprite blaster;

    sf::Texture playerTexture;

    std::vector<Bullet> playerBullets;

    int HP = 3;

    int maxHP = 3;


public:
    Player(sf::Texture &texture);

    Player(std::string filepath);

    void move(sf::Vector2f velocity);

    void setPos(sf::Vector2f pos);

    void setSize(sf::Vector2f size);

    void draw(sf::RenderTarget& window,sf::RenderStates state)const;

    int getHP();

    void plusHP();

    void minusHP();

    sf::Sprite getSprite() const;

    sf::Vector2f getPosition();

    std::vector<Bullet> &getBullets();
};

#endif //CENTIPEDE_PLAYER_H

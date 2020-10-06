//
// Created by anggo on 5/16/2020.
//

#ifndef CENTIPEDE_CENTIPEDE_H
#define CENTIPEDE_CENTIPEDE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "..\Game\Game.h"
#include "Player.h"
#include "Mushroom.h"
#include "Collision.h"
#include "Head.h"
#include "Body.h"
#include "Flea.h"
#include "Spider.h"
#include "Health.h"
#include <cstdlib>

class Centipede : public Game
{
private:
    sf::Texture bulletTexture;
    std::vector<Bullet> bullets;
    std::vector<Mushroom> level1;
    Mushroom mushroom;
    Player p;
    std::vector<Head> centipede;
    std::vector<std::vector<Head>> centipedes;
    std::vector<Flea> FleasV;
    std::vector<Spider> SpiderV;
    std::vector<std::vector<bool>> LMovement;
    std::vector<std::vector<bool>> RMovement;
    std::vector<bool> leftMovement;
    std::vector<bool> rightMovement;
    std::vector<Health> healthVector;
    sf::Font myFont;
    sf::Text scoreCount;
    bool repeat2 = false;
    bool touchGround = false;
    bool touchWall = false;
    bool repeat = false;
    sf::Clock clock;
    sf::Time frameTime;
    bool retry;
    int PlayerHp;


    bool shoot = false;
    int shootTimer = 25;

    int score=0;

    void initializeGame(sf::RenderWindow& window);
public:
    Centipede();
    virtual void start(sf::RenderWindow& window);
    virtual void exit();
    virtual void addEvents(sf::RenderWindow& window);
    virtual void addEvents(const sf::RenderWindow &window, sf::Event& event);
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};
#endif //CENTIPEDE_CENTIPEDE_H

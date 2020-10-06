//
// Created by anggo on 6/8/2020.
//

#ifndef SFML_SOMETHING_BODY_H
#define SFML_SOMETHING_BODY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Body : public sf::Drawable
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
    Body(std::string filepath1);
    sf::Sprite& getHead();
    void move(sf::Vector2f velocity);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    void setSize(sf::Vector2f size);
    void Update( float dt , sf::Vector2f dir);
    void draw(sf::RenderTarget& window,sf::RenderStates state)const;

    sf::Vector2f getSize() {return centipedeHead.getScale();}

};
#endif //SFML_SOMETHING_BODY_H

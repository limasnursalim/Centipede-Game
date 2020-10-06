//
// Created by Edwin Lau Mack on 5/2/20.
//

#ifndef CENTIPEDE_BULLET_H
#define CENTIPEDE_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable
{
public:

    Bullet(sf::Texture& texture);
    void fire(int speed);
    sf::Sprite& getSprite();
    void draw(sf::RenderTarget& window,sf::RenderStates state)const;
    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);

private:
    sf::Sprite bullet;
    sf::Texture texture;

};


#endif //CENTIPEDE_BULLET_H

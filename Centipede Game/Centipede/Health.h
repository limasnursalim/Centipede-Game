//
// Created by anggo on 6/10/2020.
//

#ifndef TESTER_HEALTH_H
#define TESTER_HEALTH_H

#include <SFML/Graphics.hpp>

class Health : public sf::Drawable
{
private:
    sf::Sprite healthIcon;
    sf::Texture texture;

public:
    Health(std::string filepath);
    void draw(sf::RenderTarget& window,sf::RenderStates state)const;
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f pos);


};


#endif //TESTER_HEALTH_H

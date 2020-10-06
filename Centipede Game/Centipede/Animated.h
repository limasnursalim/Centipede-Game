//
// Created by anggo on 6/8/2020.
//

#ifndef TESTER_ANIMATED_H
#define TESTER_ANIMATED_H

#include <SFML/Graphics.hpp>

class Animated : public sf::Drawable {
public:
    Animated();
    Animated(sf::Texture _texture);
    Animated(std::string spriteName, int left, int top, int rows, int cols);
    void setTextureRect(float left, float top, float width, float height);
    void setScale(sf::Vector2f size);
    void animation();
    void setTime(float time);
    void move(sf::Vector2f velocity);
    void rotate(float angle);
    virtual void draw(sf::RenderTarget &window, sf::RenderStates state) const;
    void goToRow(int row);
    void setCol(int col);
    void advanceRow();
    void setPosition(sf::Vector2f pos);
    bool ANIMATION_COMPLETE = false;

private:
    float _time;
    sf::Texture texture;
    sf::Clock clock;
    sf::IntRect sourceSprite;
    sf::Sprite sprite;
    float left, right;
    float width, height;
    int rows, cols, row = 1;

};


#endif //TESTER_ANIMATED_H

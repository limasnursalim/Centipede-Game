//
// Created by anggo on 6/8/2020.
//

#include "Animated.h"

Animated::Animated()
{}
Animated::Animated(sf::Texture _texture)
{
    texture = _texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sourceSprite);
}
Animated::Animated(std::string spriteName, int left, int top, int rows, int cols)
{
    if(!texture.loadFromFile(spriteName))
        exit(1);
    this->rows = rows;
    this->cols = cols;
    width = texture.getSize().x/(cols*1.0f);
    height = texture.getSize().y/(rows*1.0f);
    setTextureRect(left, top, width, height);
    sprite.setTexture(texture);
    sprite.setTextureRect(sourceSprite);
    this->left = left;

}
void Animated::setTextureRect(float left, float top, float width, float height)
{
    sourceSprite.left = left;
    sourceSprite.top = top;
    sourceSprite.width = width;
    sourceSprite.height = height;
}
void Animated::setTime(float time)
{
    _time = time;
}
void Animated::animation()
{
    ANIMATION_COMPLETE = false;
    if (clock.getElapsedTime().asMilliseconds() > _time)
    {
        if (sourceSprite.left == (cols == 0 ? width : (cols - 1) * sourceSprite.width))
            sourceSprite.left = left;
        else
            sourceSprite.left += sourceSprite.width;
        sprite.setTextureRect(sourceSprite);
        clock.restart();

    }
    ANIMATION_COMPLETE = true;
    row = row > cols ? 1 : row + 1;
}
void Animated::setScale(sf::Vector2f size)
{
    sprite.setScale(size);
}
void Animated::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
    window.draw(sprite);
}
void Animated::move(sf::Vector2f velocity)
{
    sprite.move(velocity);
}
void Animated::rotate(float angle)
{
    sprite.rotate(angle);
}

void Animated::goToRow(int row)
{
    sourceSprite.top = height *(row - 1);
    sprite.setTextureRect(sourceSprite);
}

void Animated::setCol(int col)
{
    sourceSprite.left = sourceSprite.width * (col - 1);
    left = sourceSprite.width *(col - 1);
    sprite.setTextureRect(sourceSprite);
}

void Animated::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Animated::advanceRow()
{
    goToRow(row);
}
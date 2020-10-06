//
// Created by anggo on 6/10/2020.
//
#include "Flea.h"
#include <string>

Flea::Flea(std::string file) : fleaAnimation(0,0,32,16)
{
    texture.loadFromFile(file);
    flea.setTexture(texture);
    fleaAnimation.ApplyToSprite(flea);
}

sf::Sprite& Flea::getSprite() {
    return flea;
}

void Flea::setPosition(sf::Vector2f pos) {
    flea.setPosition(pos);
}

sf::Vector2f Flea::getPosition() {
    return flea.getPosition();
}

void Flea::setSize(sf::Vector2f size) {
    flea.setScale(size);
}

void Flea::draw(sf::RenderTarget& window,sf::RenderStates state)const {
    window.draw(flea);
}

void Flea::attack(sf::Vector2f speed) {
    flea.move(speed);
}

void Flea::Update() {
    fleaAnimation.Update();
    fleaAnimation.ApplyToSprite(flea);
    fleaAnimation.animatedUpdate(1.0f/60.0f);
}
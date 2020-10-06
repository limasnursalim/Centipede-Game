//
// Created by Edwin Lau Mack on 5/2/20.
//

#ifndef CENTIPEDE_ANIMATION_H
#define CENTIPEDE_ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
private:
    static constexpr int nFrames = 4;
    static constexpr int holdTime = 0.1f;

    sf::Texture texture;
    sf::IntRect frames[nFrames];
    int iFrame = 0;
    float time = 0.0f;

public:
    Animation() = default;
    Animation(int x, int y, int width, int height);
    void ApplyToSprite(sf::Sprite& sprite);
    void Advance();
    void animatedAdvance();
    int getiFrame();
    void Update();
    void animatedUpdate(float dt);
    void ApplyToSprite();

};


#endif //CENTIPEDE_ANIMATION_H

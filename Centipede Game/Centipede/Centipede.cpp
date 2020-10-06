//
// Created by anggo on 5/17/2020.
//
#include "Centipede.h"

Centipede::Centipede() :mushroom("Sprites/mushroom.png"),p("Sprites/blaster.png")
{
    image_path = "Sprites/Centipede.png";
    title = "Centipede";
    info_path = "Information/info.txt";
    load_game();
}

void Centipede::start(sf::RenderWindow& window)
{

    initializeGame(window);

}

void Centipede::addEvents(sf::RenderWindow& window)
{
    sf::Vector2f centipedeVelocity(5.0f, 0.2f);

    frameTime = clock.getElapsedTime();

    for(int i=0;i<centipedes.size();i++)
    {
        for(int j=0;j<centipedes[i].size();j++)
        {
            // Centipede going down to y = 30
            if (centipedes[i][j].getPosition().y <= 70.0f) {
                centipedeVelocity = sf::Vector2f(0.0f, 10.0f);
                centipedes[i][j].move(centipedeVelocity);
            }

                // After passing the y = 30 mark
            else {
                // Centipede needs to go to left
                if (LMovement[i][j])
                {
                    centipedeVelocity = sf::Vector2f(-10.0f, 0.0f);
                    centipedes[i][j].move(centipedeVelocity);
                }

                    // Centipede needs to go to the right
                else if (RMovement[i][j]) {
                    centipedeVelocity = sf::Vector2f(10.0f, 0.0f);
                    centipedes[i][j].move(centipedeVelocity);
                }

                // Check centipede collides with the left window barrier
                if (centipedes[i][j].getPosition().x <= 420) {
                    centipedeVelocity = sf::Vector2f(0.0f, 10.0f);
                    centipedes[i][j].move(centipedeVelocity);
                    LMovement[i][j] = false;
                    RMovement[i][j] = true;
                }
                if (centipedes[i][j].getPosition().x >= 1500) {
                    centipedeVelocity = sf::Vector2f(0.0f, 10.0f);
                    centipedes[i][j].move(centipedeVelocity);
                    RMovement[i][j] = false;
                    LMovement[i][j] = true;
                }

                for (int k = 0; k < level1.size(); k++) {
                    if (Collision::PixelPerfectTest(centipedes[i][j].getHead(), level1[k].getSprite())) {
                        if (LMovement[i][j]) {
                            centipedeVelocity = sf::Vector2f(0.0f, 10.0f);
                            centipedes[i][j].move(centipedeVelocity);
                            LMovement[i][j] = false;
                            RMovement[i][j] = true;
                        } else {
                            centipedeVelocity = sf::Vector2f(0.0f, 10.0f);
                            centipedes[i][j].move(centipedeVelocity);
                            RMovement[i][j] = false;
                            LMovement[i][j] = true;
                        }
                    }
                }
            }
        }
    }

    // Movement of the blaster

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        p.move(sf::Vector2f(5.0f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        p.move(sf::Vector2f(-5.0f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        p.move(sf::Vector2f(0.0f, -5.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        p.move(sf::Vector2f(0.0f, 5.0f));
    }

    // Blaster not getting out of window
    if (p.getPosition().x >= window.getSize().x - 50)
    {
        p.move(sf::Vector2f(-1.5f, 0.0f));
    }
    if (p.getPosition().x <= 0)
    {
        p.move(sf::Vector2f(1.5f, 0.0f));
    }
    if (p.getPosition().y >= window.getSize().y - 50)
    {
        p.move(sf::Vector2f(0.0f, -1.5f));
    }

    // Shooting bullets

    if (shootTimer < 25)
    {
        shootTimer++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 25)
    {
        Bullet newBullet(bulletTexture);
        newBullet.setPosition(sf::Vector2f(p.getPosition().x, p.getPosition().y));
        newBullet.setSize(sf::Vector2f(2.5f, 2.5f));
        bullets.push_back(newBullet);
        shootTimer = 0;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[ i ].fire(-10);

        if (bullets[ i ].getSprite().getPosition().y < 0)
        {
            bullets.erase(bullets.begin() + i);
        }
    }

    // Collision bullets with mushrooms
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < level1.size(); j++)
        {
            if (Collision::PixelPerfectTest(bullets[ i ].getSprite(), level1[ j ].getSprite()))
            {
                bullets.erase(bullets.begin() + i);
                level1[ j ].Update();
                if (level1[ j ].getAnimation1().getiFrame() == 4)
                {
                    level1.erase(level1.begin() + j);
                    score+=100;
                    scoreCount.setString(std::to_string(score));
                }
            }
        }
    }

    /******* FLEA ********/

    //The speed of the fleas~
    sf::Vector2f fleasSpeed(0,1.0f);
    if ((static_cast<int>(frameTime.asSeconds())%5) == 0) {
        if(!repeat) {
            Flea *newFlea = new Flea("Sprites/flea.png");
            newFlea->setPosition(sf::Vector2f(rand()% 1080 + 420,-50));
            newFlea->setSize(sf::Vector2f(2.0f,2.0f));
            FleasV.push_back(*newFlea);
            repeat = true;
        }
    }

    //To make sure that the vector don't increase as for milliseconds
    if(static_cast<int>(frameTime.asSeconds())%5 != 0) {
        repeat = false;
    }
    //Summon the Feas to the attack the player

    FleasV[0].attack(fleasSpeed);

    //Delete the Feas when it collides with the player

    if ((Collision::PixelPerfectTest(FleasV[0].getSprite(), p.getSprite())))
    {
        FleasV.erase(FleasV.begin());
        healthVector.erase(healthVector.begin());
    }
    if(FleasV[0].getPosition().y>1080)
    {
        FleasV.erase(FleasV.begin());
    }

    for(int i=0;i<bullets.size();i++)
    {
        if ((Collision::PixelPerfectTest(FleasV[0].getSprite(), bullets[i].getSprite())))
        {
            FleasV.erase(FleasV.begin());
            bullets.erase(bullets.begin()+i);
            score+= 50;
        }
    }



    /******* SPIDER *********/
    //Increase vector every 7 seconds to summon the spider
    if ((static_cast<int>(frameTime.asSeconds())%7) == 0) {
        if(!repeat2) {
            Spider *newSpider = new Spider("Sprites/spider.png");
            newSpider->setPosition(sf::Vector2f(rand()%2000,rand()%2000));
            newSpider->setSize(sf::Vector2f(4.0f,4.0f));
            SpiderV.push_back(*newSpider);
            repeat2 = true;
        }
    }

    //To make sure that the vector don't increase as for milliseconds
    if(static_cast<int>(frameTime.asSeconds())%7 != 0) {
        repeat2 = false;
    }

    //Direction of the spider moving
    if (SpiderV[0].getPosition().y >= 1080)
        touchGround = true;
    if (SpiderV[0].getPosition().y <= 0)
        touchGround = false;

    if (SpiderV[0].getPosition().x >= 1500)
        touchWall = true;
    if (SpiderV[0].getPosition().x <= 420)
        touchWall = false;

    //Spider will move and attack
    if (SpiderV.size() > 0) {
        if (touchGround) {
            SpiderV[0].attack(sf::Vector2f(0, -1.0f));
        } else {
            SpiderV[0].attack(sf::Vector2f(0, 1.0f));
        }
        if (touchWall) {
            SpiderV[0].attack(sf::Vector2f(-1.0f, 0));
        } else {
            SpiderV[0].attack(sf::Vector2f(1.0f, 0));
        }
    }

    if (frameTime.asSeconds()>7) {
        SpiderV.erase(SpiderV.begin());
        frameTime = clock.restart();
    }

    //Delete the Spider when it collides with the player

    if ((Collision::PixelPerfectTest(SpiderV[0].getSprite(), p.getSprite())) && SpiderV.size()>0)
    {
        SpiderV.erase(SpiderV.begin() );
        healthVector.erase(healthVector.begin());
    }

    //Delete the Spider when it collides with the centipede
    for(int i=0;i<bullets.size();i++)
    {
        if ((Collision::PixelPerfectTest(SpiderV[0].getSprite(), bullets[i].getSprite())))
        {
            SpiderV.erase(SpiderV.begin() );
            bullets.erase(bullets.begin()+i);
            score+=50;
        }
    }


    //Collision bullet with body
    for(int i=0;i<centipedes.size();i++)
    {
        for (int j = 0; j < centipedes[i].size(); j++)
        {
            if(Collision::PixelPerfectTest(centipedes[i][j].getHead(),p.getSprite()) && healthVector.size()>0)
            {
                healthVector.erase(healthVector.begin());
            }
            for (int k = 0; k < bullets.size(); k++) {
                if (Collision::PixelPerfectTest(centipedes[i][j].getHead(), bullets[k].getSprite()))
                {
                    // Erase bullet sprite
                    bullets.erase(bullets.begin()+k);

                    if(centipedes[i].size() == 1)
                    {
                        mushroom.setSize(sf::Vector2f(2.0f, 2.0f));
                        mushroom.setPosition(sf::Vector2f(centipedes[i][j].getPosition().x - 10.0f,centipedes[i][j].getPosition().y));
                        level1.push_back(mushroom);
                        centipedes[i].erase(centipedes[i].begin());
                        RMovement[i].erase(RMovement[i].begin());
                        LMovement[i].erase(LMovement[i].begin());
                        score+=500;
                    }
                    else
                    {
                        if(j==0)
                        {
                            Head *newCentipede = new Head("Sprites/centipede_head.png","Sprites/centipede_head.png");
                            newCentipede->setPosition(sf::Vector2f(centipedes[i][j+1].getPosition()));
                            newCentipede->setSize(sf::Vector2f(4.0f,4.0f));
                            centipedes[i][j+1] = *newCentipede;
                            mushroom.setSize(sf::Vector2f(2.0f, 2.0f));
                            mushroom.setPosition(sf::Vector2f(centipedes[i][j].getPosition().x - 10.0f,centipedes[i][j].getPosition().y));
                            level1.push_back(mushroom);
                            centipedes[i].erase(centipedes[i].begin());
                            RMovement[i].erase(RMovement[i].begin());
                            LMovement[i].erase(LMovement[i].begin());
                            score+=500;

                        }
                        else if(j == centipedes[i].size()-1)
                        {
                            mushroom.setSize(sf::Vector2f(2.0f, 2.0f));
                            mushroom.setPosition(sf::Vector2f(centipedes[i][j].getPosition().x - 10.0f,centipedes[i][j].getPosition().y));
                            level1.push_back(mushroom);
                            centipedes[i].erase(centipedes[i].end());
                            RMovement[i].erase(RMovement[i].end());
                            LMovement[i].erase(LMovement[i].end());
                            score+=100;

                        }
                        else
                        {
                            // Calculate the body destroyed
                            int bodyDestroyed = j+1;

                            std::vector<Head> newCent;
                            std::vector<bool> newLeftMovement;
                            std::vector<bool> newRightMovement;


                            Head *newCentipede = new Head("Sprites/centipede_head.png","Sprites/centipede_head.png");
                            newCentipede->setPosition(sf::Vector2f(centipedes[i][j+1].getPosition()));
                            newCentipede->setSize(sf::Vector2f(4.0f,4.0f));
                            newCent.push_back(*newCentipede);
                            newLeftMovement.push_back(true);
                            newRightMovement.push_back(false);

                            for(int x= bodyDestroyed + 1;x<centipedes[i].size();x++)
                            {
                                Head *newCentipede = new Head("Sprites/centipede_body.png","Sprites/centipede_body.png");
                                newCentipede->setSize(sf::Vector2f(4.0f,4.0f));
                                newCentipede->setPosition(sf::Vector2f(centipedes[i][x].getPosition()));
                                newCent.push_back(*newCentipede);
                                newLeftMovement.push_back(true);
                                newRightMovement.push_back(false);
                            }
                            LMovement.push_back(newLeftMovement);
                            RMovement.push_back(newRightMovement);
                            centipedes.push_back(newCent);


                            mushroom.setSize(sf::Vector2f(2.0f, 2.0f));
                            mushroom.setPosition(sf::Vector2f(centipedes[i][j].getPosition().x - 10.0f,centipedes[i][j].getPosition().y));
                            level1.push_back(mushroom);

                            int sizeToBeDestroyed = centipedes[i].size();

                            for(int x=j;x<sizeToBeDestroyed;x++)
                            {
                                centipedes[i].erase(centipedes[i].end());
                                RMovement[i].erase(RMovement[i].end());
                                LMovement[i].erase(LMovement[i].end());
                            }

                            score+=100;
                        }
                    }
                    scoreCount.setString(std::to_string(score));
                }
            }
            if(centipedes[i].size() == 0)
            {
                centipedes.erase(centipedes.begin() + i);
                LMovement.erase(LMovement.begin()+i);
                RMovement.erase(RMovement.begin()+i);
            }
        }
    }

    if(centipedes.size() == 0)
    {
        retry = true;
        sf::Font gameOverFont;
        if(!gameOverFont.loadFromFile("Font/cosmic.ttf"))
        {
            std:: cout << "File failed to load! \n";
        }
        sf::Text gameOverText;
        gameOverText.setFont(myFont);
        gameOverText.setCharacterSize(100);
        gameOverText.setPosition(sf::Vector2f(window.getSize().x/8, window.getSize().y/4));
        gameOverText.setFillColor(sf::Color::White);

        std::string gameOverMessage="You won! \nFinal score:";
        gameOverMessage=gameOverMessage.append(std::to_string(score));

        gameOverText.setString(gameOverMessage);
        window.draw(gameOverText);
    }
    if(healthVector.size()<=0)
    {
        retry = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            int mushroomSize = level1.size();
            for(int i=0;i<mushroomSize;i++)
            {
                level1.erase(level1.begin() + i);
            }

            int centipedeSize = centipedes.size();
            for(int i=0;i<centipedeSize;i++)
            {
                centipedes.erase(centipedes.begin());
                LMovement.erase(LMovement.begin());
                RMovement.erase(RMovement.begin());
            }
            int healthSize = healthVector.size();
            for(int i=0;i<healthSize;i++)
            {
                healthVector.erase(healthVector.begin());
            }

            score = 0;

            initializeGame(window);
        }
        else
        {
            sf::Font gameOverFont;
            if(!gameOverFont.loadFromFile("Font/cosmic.ttf"))
            {
                std:: cout << "File failed to load! \n";
            }
            sf::Text gameOverText;
            gameOverText.setFont(myFont);
            gameOverText.setCharacterSize(100);
            gameOverText.setPosition(sf::Vector2f(window.getSize().x/8, window.getSize().y/4));
            gameOverText.setFillColor(sf::Color::White);

            std::string gameOverMessage="Press enter to retry! \nFinal score:";
            gameOverMessage=gameOverMessage.append(std::to_string(score));

            gameOverText.setString(gameOverMessage);
            window.draw(gameOverText);
        }
    }

}

void Centipede::addEvents(const sf::RenderWindow &window, sf::Event& event)
{

}

void Centipede::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
//    window.draw(thumbnailSprite);
//    window.draw(blaster);
    if(!retry)
    {
        window.draw(p);
        for (int i = 0; i < level1.size(); i++)
        {
            window.draw(level1[i]);
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
    //    for(int i =0; i<centipede.size();i++)
    //    {
    //        window.draw(centipede[i]);
    //    }
        for(int i=0; i<centipedes.size(); i++)
            for(int j =0; j<centipedes[i].size();j++)
            {
                window.draw(centipedes[i][j]);
            }
        for (int i=0; i<FleasV.size(); i++)
        {
            window.draw(FleasV[i]);
        }
        for (int i=0; i<SpiderV.size(); i++)
        {
            window.draw(SpiderV[i]);
        }
        for(int i=0;i<healthVector.size();i++)
        {
            window.draw(healthVector[i]);
        }
        window.draw(scoreCount);
    }
}

void Centipede::exit()
{

};

void Centipede::initializeGame(sf::RenderWindow& window)
{
    int healthXCoordinate=20;
    for(int i=0 ; i<3; i++)
    {
        Health* health = new Health("Sprites/PlayerHealth.png");
        health->setSize(sf::Vector2f(0.8f,0.8f));
        health->setPosition(sf::Vector2f(healthXCoordinate,200));
        healthVector.push_back(*health);
        healthXCoordinate+=50;
    }
    // Initialize scores
    if(!myFont.loadFromFile("Font/DS-DIGII.TTF"))
    {
        std:: cout << "Font file error \n";
    }
    scoreCount.setFont(myFont);
    scoreCount.setString(std::to_string(score));
    scoreCount.setCharacterSize(100);
    scoreCount.setFillColor(sf::Color::White);


    bulletTexture.loadFromFile("Sprites/bullet.png");


    srand(time(NULL));

    // Initialize mushrooms
    for (int i = 0; i < 40; i++)
    {
        mushroom.setSize(sf::Vector2f(2.0f, 2.0f));
        mushroom.setPosition(sf::Vector2f(rand() % 1080 + 420 , rand() % 1080 + 30));
        level1.push_back(mushroom);
    }

    // Initialize player
    p.setSize(sf::Vector2f(2.50f, 2.50f));
    p.setPos(sf::Vector2f(window.getSize().x / 2, window.getSize().y -75));

    // Head of the centipede
    Head *centipedeHead = new Head("Sprites/centipede_head.png","Sprites/centipede_head.png");
    centipedeHead->setPosition(sf::Vector2f(window.getSize().x/2, 0));
    centipedeHead->setSize(sf::Vector2f(4.0f,4.0f));
    centipede.push_back(*centipedeHead);
    leftMovement.push_back(true);
    rightMovement.push_back(false);

    // Body of the centipede
    for(int i=1;i<11;i++)
    {
        Head *centipedeBody = new Head("Sprites/centipede_body.png","Sprites/centipede_body.png");
        centipedeBody->setSize(sf::Vector2f(4.0f,4.0f));
        centipedeBody->setPosition(sf::Vector2f(window.getSize().x/2,((-30*(i+1)+30))));
        centipede.push_back(*centipedeBody);
        leftMovement.push_back(true);
        rightMovement.push_back(false);
    }
    LMovement.push_back(leftMovement);
    RMovement.push_back(rightMovement);
    centipedes.push_back(centipede);

    for(int i=0;i<3;i++)
    {
        Flea *newFlea = new Flea("Sprites/flea.png");
        newFlea->setPosition(sf::Vector2f(rand()% 1080 + 420,-50));
        newFlea->setSize(sf::Vector2f(2.0f,2.0f));
        FleasV.push_back(*newFlea);
    }

    retry = false;
}

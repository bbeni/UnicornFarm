//
//  Player.h
//  Unicorn Farm
//
//  Created by Beni on 26.04.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#ifndef Unicorn_Farm_Player_h
#define Unicorn_Farm_Player_h



#include <SFML/Graphics/Sprite.hpp>

#include "common.hpp"
#include "AnimatedSprite.hpp"
#include "World.hpp"

class Player
{
public:
    Player(sf::Transformable trans, std::string name);
    ~Player();

    void update(sf::Time delta);
    void applyCollision(World& w);

    void move(sf::Vector2f delta);

    void setPosition(sf::Vector2f pos);
    const sf::Vector2f* getPosition();

    const sf::Vector2f* getAnimationPosition();
    void setAnimationPosition(sf::Vector2f pos);

    void playCurrentAnimation();
    void pauseCurrentAnimation();

    void setCurrentAnimation(std::string name);
    Animation* getCurrentAnimation();
    AnimatedSprite* getAnimatedSprite();

    const sf::FloatRect& getCollisionRect();

    void setMaxSpeed(float speed);
    void setSpeed(float speed);
    void setAcceleration(float acc);
    void setWalkingDirection(sf::Vector2f direction);
    void walk();
    void stop();

    sf::Vector2f getLastMovement();


private:
    int generateSweetAnimation(std::map<std::string, Animation>& animations, sf::Texture& texture, std::string file);

    std::string _name;

    sf::Transformable _trans;

    bool _walking;
    float MAX_SPEED;
    float _speed;
    float _acceleration;

    sf::Vector2f _walkingDirection;

    sf::FloatRect _collisionRect;
    sf::Vector2f _lastmovement;

    sf::Texture _tex;

    Animation* _currentAnimation;

    animation_dict _animationDict;

    AnimatedSprite _animatedSprite;


};



#endif

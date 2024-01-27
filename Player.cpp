//
//  Player.cpp
//  Unicorn Farm
//
//  Created by Beni on 29.04.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "Player.hpp"

#include "ResourcePath.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <iostream>
#include <math.h>
#include <assert.h>


Player::Player(sf::Transformable trans, std::string name):
 _name(name)
{

    setMaxSpeed(4);
    setAcceleration(0.2);
    setSpeed(0);

    _trans.setPosition(trans.getPosition());
    _trans.setRotation(trans.getRotation());
    _trans.setScale(trans.getScale());
    _trans.setOrigin(trans.getOrigin());
    _collisionRect = sf::FloatRect(trans.getPosition().x - 0.25,trans.getPosition().y,0.5,0.5);



    // set up AnimatedSprite
    AnimatedSprite aSprite(sf::seconds(0.2), true, false);
    _animatedSprite = aSprite;




    if(generateSweetAnimation(_animationDict, _tex, "player.png"))
        std::cerr << "failed to gereate animation" << std::endl;

    setCurrentAnimation("Down");

}

Player::~Player()
{

}



void Player::applyCollision(World& w)
{
    sf::FloatRect r = getCollisionRect();

//    std::cout << r.left << " " << r.width << " " << r.top << " " << r.height << std::endl;
    if (w.collides(r))
    {
        move(-getLastMovement());
    }
}

const sf::FloatRect& Player::getCollisionRect()
{
    return _collisionRect;
}


void Player::move(sf::Vector2f delta)
{
    _trans.move(delta);
    _collisionRect = sf::FloatRect(_collisionRect.left + delta.x, _collisionRect.top + delta.y,_collisionRect.width, _collisionRect.height);
//    _animatedSprite.move(delta);
}

void Player::setAnimationPosition(sf::Vector2f pos)
{
    _animatedSprite.setPosition(pos);
}

const sf::Vector2f* Player::getAnimationPosition()
{
    return &_animatedSprite.getPosition();
}

void Player::setPosition(sf::Vector2f pos)
{
    _trans.setPosition(pos);

}

const sf::Vector2f* Player::getPosition()
{
    return &_trans.getPosition();
}

void Player::update(sf::Time delta)
{
    _animatedSprite.update(delta);

    sf::Vector2f movement(0.0f, 0.0f);

    if (_walking)
    {
        _speed += (_acceleration * delta.asSeconds());

        if (_speed > MAX_SPEED)
        {
            _speed = MAX_SPEED;
        }
    } else {
        _speed -= (_acceleration * delta.asSeconds());
        if (_speed <= 0)
        {
            _speed = 0;
        }
    }

    movement = _walkingDirection * _speed * delta.asSeconds();
    _lastmovement = movement;
    move(movement);

}

sf::Vector2f Player::getLastMovement()
{
    return _lastmovement;
}

void Player::setMaxSpeed(float speed)
{
    MAX_SPEED = speed;
}
void Player::setSpeed(float speed)
{
    _speed = speed;

}
void Player::setAcceleration(float acc)
{
    _acceleration = acc;

}
void Player::setWalkingDirection(sf::Vector2f direction)
{
    _walkingDirection = direction;

    //normalize the direction (length to 1)
    float l = sqrtf(_walkingDirection.x * _walkingDirection.x + _walkingDirection.y * _walkingDirection.y);

    if (l != 0)
        _walkingDirection /= l;

    assert(0.9999999f <= sqrtf(_walkingDirection.x * _walkingDirection.x + _walkingDirection.y * _walkingDirection.y));
    assert(sqrtf(_walkingDirection.x * _walkingDirection.x + _walkingDirection.y * _walkingDirection.y) <= 1.0000001f);
}
void Player::walk()
{
    _walking = true;
}
void Player::stop()
{
    _walking = false;
}

void Player::setCurrentAnimation(std::string name)
{
    _currentAnimation = &_animationDict[name];
}

Animation* Player::getCurrentAnimation()
{
    return _currentAnimation;
}

AnimatedSprite* Player::getAnimatedSprite()
{
    return &_animatedSprite;
}

void Player::playCurrentAnimation()
{
    _animatedSprite.play(*getCurrentAnimation());
}

void Player::pauseCurrentAnimation()
{
    _animatedSprite.pause();
}

int Player::generateSweetAnimation(std::map<std::string, Animation>& animations, sf::Texture& texture, std::string file)
{
    if (!texture.loadFromFile(file)) {
        return EXIT_FAILURE;
    }

    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    animations["Down"] = walkingAnimationDown;
    animations["Left"] = walkingAnimationLeft;
    animations["Right"] = walkingAnimationRight;
    animations["Up"] = walkingAnimationUp;

    return 0;
}










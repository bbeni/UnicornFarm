//
//  World.h
//  Unicorn Farm
//
//  Created by Beni on 25.04.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#ifndef Unicorn_Farm_World_h
#define Unicorn_Farm_World_h

#include "common.hpp"

#include <string>
#include <vector>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>



enum TileEnum{
    NOTHING,
    
    FLOOR,
    ROCK,
};

typedef std::map<TileEnum, sf::Sprite> sprite_enum_dict;

class World
{
public:
    World(int width, int height, int blockWidth, int blockHeight, std::string name);
    World(int blockWidth, int blockHeight, std::string image, std::string name);
    ~World() {};
    
    void fromImage(sf::Image& data, int width, int height);
    
    
    void draw(sf::RenderTarget& target, sf::RenderStates states, sf::Vector2f cameraPos, screenSize screen);
    
    void populateRandom();
    
    
    void setTile(int x, int y, TileEnum tile);
    TileEnum getTile(int x, int y);
    TileEnum getTile(sf::Vector2i index);
    
    sf::Vector2i getTileXYAt(sf::Vector2f pos);
    
    void mapSprite(sf::Sprite sprite, TileEnum tile);
    sf::Sprite* getSprite(TileEnum tile);
    
    void fillWith(TileEnum tile);
    void fillRectWith(int left, int top, int width, int height, TileEnum tile);
    
    //collision
    //cehck if a rect collides
    bool collides(sf::FloatRect rect);

    //check if a point collides
    bool collides(sf::Vector2f point);
    
    //check if a circle collides
    bool collides(sf::Vector2f mid, float radius);
    
    
private:

    int _width;
    int _height;
    int _size;
    
    int _blockWidth;
    int _blockHeight;
    
    std::string _name;
    
    std::vector<TileEnum> _tiles;
    
    sprite_enum_dict _spriteObjects;
};


#endif

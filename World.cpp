//
//  World.cpp
//  Unicorn Farm
//
//  Created by Beni on 25.04.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include "World.hpp"

#include "ResourcePath.hpp"

#include <iostream>
#include <math.h>

World::World (int width, int height, int blockWidth, int blockHeight, std::string name):
_width(width), _height(height), _name(name), _blockWidth(blockWidth), _blockHeight(blockHeight)
{
    _size = _width * _height;

    _tiles.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            _tiles.push_back(NOTHING);
        }
    }
}

World::World(int blockWidth, int blockHeight, std::string image, std::string name):
_name(name), _blockWidth(blockWidth), _blockHeight(blockHeight)
{
    sf::Image data;
    data.loadFromFile(image);
    int width = data.getSize().x;
    int height = data.getSize().y;

    _height = height + 8;
    _width = width + 8;
    _size = _width * _height;

    _tiles.clear();
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            _tiles.push_back(NOTHING);
        }
    }

    fillWith(FLOOR);


    fromImage(data, 4, 4);



}

void World::fromImage(sf::Image& data, int atX, int atY)
{

    for (int i = atX; i < _width + atX; i++)
    {
        for (int j = atY; j < _height + atY; j++)
        {
            sf::Color c = data.getPixel(i - atX, j - atY);
            if (c == sf::Color::Black)
                setTile(i, j, ROCK);

        }
    }

    fillRectWith(0, 0, _width, atY, ROCK);
    fillRectWith(0, atY, atX, _height - atY, ROCK);
    fillRectWith(atX, atY + data.getSize().y, _width - atX, _height - data.getSize().y -atY, ROCK);
    fillRectWith(atX + data.getSize().x, atY, _width - data.getSize().x - atX, data.getSize().y, ROCK);


}

void World::fillWith(TileEnum tile)
{
    for(std::vector<TileEnum>::iterator it = _tiles.begin(); it != _tiles.end(); ++it)
    {
        *it = tile;
    }
}

void World::fillRectWith(int left, int top, int width, int height, TileEnum tile)
{
    std::vector<TileEnum>::iterator begin = _tiles.begin() + left + top * _width;
    std::vector<TileEnum>::iterator end = _tiles.begin() + left + width + (top + height - 1) * _width;

    std::vector<TileEnum>::iterator it;

    int xCounter = 0;

    for(it = begin; it != end; ++it)
    {
        xCounter++;
        if (xCounter <= width)
        {
            *it = tile;

        }
        if (xCounter == _width)
        {
            xCounter = 0;
        }
    }
}

void World::populateRandom()
{
    fillWith(FLOOR);

}

void World::mapSprite(sf::Sprite sprite, TileEnum tile)
{
    _spriteObjects[tile] = sprite;
}

sf::Sprite* World::getSprite(const TileEnum tile)
{
    return &_spriteObjects[tile];
}

void World::setTile(int x, int y, const TileEnum tile)
{
//    std::vector<TileEnum>::iterator it;
//    it = _tiles.begin();
//    it = _tiles.insert(it + y * _width + x, tile);
    _tiles[x + _width * y] = tile;
}

TileEnum World::getTile(int x, int y)
{
    return _tiles[y * _width + x];
}

TileEnum World::getTile(sf::Vector2i index)
{
    return _tiles[index.y * _width + index.x];
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states, sf::Vector2f pos, screenSize screen)
{
//    int left = screen.w/2 - _blockWidth * 1;
//    int right = screen.w/2 + _blockWidth * 1;
//    int top = screen.h/2 - _blockHeight * 1;
//    int bottom = screen.h/2 + _blockHeight * 1;

//    std::cout << pos.x << " " << pos.y << std::endl;

    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            sf::Sprite* block = getSprite(getTile(j, i));
//            block->setOrigin(_blockWidth/6, _blockHeight/6);
            int x = (-pos.x + j) * _blockWidth + screen.w/2;
            int y = (-pos.y + i )* _blockHeight + screen.h/2;
            block->setPosition(x, y);


            //if ((left <= x && x <= right) && (top <= y && y <= bottom))
            {
                target.draw(*block, states);
            }
        }
    }
}

sf::Vector2i World::getTileXYAt(sf::Vector2f pos)
{
    int x = floorf(pos.x);
    int y = floorf(pos.y);
//    std::cout << x << " " << y << std::endl;

    return sf::Vector2i(x, y);
}


bool World::collides(sf::FloatRect rect)
{
    sf::Vector2f a(rect.left, rect.top);
    sf::Vector2f b(rect.left + rect.width, rect.top);
    sf::Vector2f c(rect.left + rect.width, rect.top + rect.height);
    sf::Vector2f d(rect.left, rect.top + rect.height);

    int points[4];
    points[0] = getTile(getTileXYAt(a));
    points[1] = getTile(getTileXYAt(b));
    points[2] = getTile(getTileXYAt(c));
    points[3] = getTile(getTileXYAt(d));

    int collision = ROCK;

    if (collision == points[0] ||
        collision == points[1] ||
        collision == points[2] ||
        collision == points[3]      )
        return true;
    return false;
}

//check if a point collides
bool World::collides(sf::Vector2f point)
{
    int tile = getTile(getTileXYAt(point));
    if (tile == ROCK)
    {
        return true;
//        std::cout << "Rocky" << std::endl;
    }

    return false;
}

//check if a circle collides
bool World::collides(sf::Vector2f mid, float radius)
{
    return false;
}

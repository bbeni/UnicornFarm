//
//  Tile.h
//  Unicorn Farm
//
//  Created by Beni on 02.05.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#ifndef Unicorn_Farm_Tile_h
#define Unicorn_Farm_Tile_h

class Tile
{
public:
    Tile();
    ~Tile();
    
    
private:
    sf::FloatRect collisionBounds;
    AnimatedSprite display;
    sf::Vector2i pos;
    
}


#endif

//
//  main.h
//  Unicorn Farm
//
//  Created by Beni on 29.04.15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#ifndef Unicorn_Farm_common_h
#define Unicorn_Farm_common_h

#include <map>
#include <string>
#include "Animation.hpp"

typedef std::map<std::string, Animation> animation_dict;

struct screenSize{
    int w;
    int h;
};


#endif

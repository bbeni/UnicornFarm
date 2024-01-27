
LDFLAGS="-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network"
CFLAGS="-std=c++14 -Wall -Wextra"


set -xe

if [ ! -d build ]; then
    mkdir build
fi

g++ main.cpp -c -o build/main.o $CFLAGS
g++ World.cpp -c -o build/world.o $CFLAGS
g++ Player.cpp -c -o build/player.o $CFLAGS
g++ Animation.cpp -c -o build/animation.o $CFLAGS
g++ AnimatedSprite.cpp -c -o build/sprite.o $CFLAGS


g++ build/main.o build/player.o build/world.o build/animation.o build/sprite.o -o build/unicorn_farm $LDFLAGS 

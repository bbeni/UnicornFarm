
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also/Users/beni/Desktop/Unicorn Farm/Unicorn Farm.xcodeproj copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

//#define NDEBUG
#include <assert.h>

void * __gxx_personality_v0=0;
void * _Unwind_Resume =0;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include "common.hpp"

#include "Animation.hpp"
#include "World.hpp"
#include "AnimatedSprite.hpp"
#include "Player.hpp"

#include <iostream>
#include <string>
#include <map>

#include <math.h>

int generate_sweet_animation(animation_dict& animations, sf::Texture& texture);

int main(int, char const**)
{
    screenSize screen;
    screen.w = 800;
    screen.h = 600;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screen.w, screen.h), "SFML window", sf::Style::Default);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    sf::Texture run_cycle;
    run_cycle.loadFromFile("spritesheetvolt_run.png");

    sf::Texture dirt;
    dirt.loadFromFile("dirt32.jpg");
    dirt.setSmooth(false);

    sf::Texture stone;
    stone.loadFromFile("stone32.jpg");
    stone.setSmooth(false);

    sf::Sprite runner;
    runner.setTexture(run_cycle);
    runner.setTextureRect(sf::IntRect(0,0,280,385));

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Unicorns.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.setLoop(true);
    //music.play();



    //setting up the world
//    World world(10, 10, 96, 96, "poo");
//
//
//    world.setTile(1, 1, FLOOR);
//    world.setTile(1, 3, FLOOR);
//    world.setTile(4, 4, FLOOR);
//
//    assert(world.getTile(1, 1) == FLOOR);
//    assert(world.getTile(1, 3) == FLOOR);
//    assert(world.getTile(3, 3) == NOTHING);
//    assert(world.getTile(4, 4) == FLOOR);
//    assert(world.getTile(9, 9) == NOTHING);
//
//    world.populateRandom();

    sf::Sprite floor;
    floor.setTexture(dirt);
    floor.setScale(3, 3);

    sf::Sprite rock;
    rock.setTexture(stone);
    rock.setScale(3, 3);

//    world.mapSprite(floor, FLOOR);
//    world.mapSprite(rock, ROCK);
//
//    world.fillRectWith(2, 3, 4, 1, ROCK);

    World world2(96, 96, "testlevel.png", "World 2");

    world2.mapSprite(floor, FLOOR);
    world2.mapSprite(rock, ROCK);






    sf::Transformable camera;
    camera.setPosition(4.5f, 4.5f);

    float playerWidth = 96;
    float playerHeight = 96;

    Player player1(camera, "Player1");
    player1.setAnimationPosition(
                        sf::Vector2f(screen.w/2 - playerWidth/2,
                                     screen.h/2 - playerHeight/2));

    player1.getAnimatedSprite()->setScale(3, 3);


    sf::CircleShape p(3);
    p.setPosition(0, 0);
    p.setFillColor(sf::Color::Black);


    sf::Clock clock;
    float speed = 4.0f;
    bool noKeyWasPressed = true;

    // Start the game loop
    std::cout << "started game loop" << std::endl;
    while (window.isOpen())
    {

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Espace pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        //Get elapsed Time
        sf::Time frameTime = clock.restart();

        sf::Vector2f movement(0.f, 0.f);
        player1.walk();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player1.setCurrentAnimation("Up");
            movement.y -= 1;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player1.setCurrentAnimation("Down");
            movement.y += 1;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player1.setCurrentAnimation("Left");
            movement.x -= 1;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player1.setCurrentAnimation("Right");
            movement.x += 1;
            noKeyWasPressed = false;
        }

        player1.setWalkingDirection(movement);

        player1.playCurrentAnimation();

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            player1.stop();
            player1.pauseCurrentAnimation();
        }
        noKeyWasPressed = true;



        // update
        player1.update(frameTime);

        player1.applyCollision(world2);


        p.setPosition(player1.getAnimationPosition()->x + playerWidth/2,player1.getAnimationPosition()->y+playerHeight/2);



        // draw
        window.clear(sf::Color(215,0,215));

        world2.draw(window, sf::RenderStates::Default, *player1.getPosition(), screen);

//        std::cout << player1.getPosition()->x << std::endl;

        window.draw(*player1.getAnimatedSprite());
        window.draw(p);

        window.display();
    }

    return EXIT_SUCCESS;
}

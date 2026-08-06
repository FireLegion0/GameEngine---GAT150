// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "../Engine/File.h"
#include "../Engine/Font.h"
#include "../Engine/Text.h"
#include "SpaceGame.h"

#include <fmod.hpp>

#include <iostream>
#include <vector>
#include "SDL3/SDL.h"
#include "../Engine/Scene.h"
#include <map>
#include <memory>
#include <random>

#define TEXT "Hello!\n"
#define MAX(a, b) ((a > b) ? a : b)

using namespace nu;

/*
class Object {
public:
    Object() { std::cout << "Constructor\n"; }
    ~Object() { std::cout << "Destructor\n"; }

	Object(const Object& object) { std::cout << "Copy\n"; }
	Object& operator = (const Object& object) { std::cout << "Assignment\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG() {
	seed = (seed * 1103515245 + 12345) ;
    return seed;
}
*/

int main() {

    /*
    for (size_t i = 0; i < 10; ++i) {
        std::cout << RNG() << " ";
    }
	std::cout << std::endl;

	seed = 1234;
    for (size_t i = 0; i < 10; ++i) {
        std::cout << RNG() << " ";
    }
	std::cout << std::endl;

	nu::SeedRandom((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; ++i) {
        std::cout << rand() << " ";
    }
	std::cout << std::endl;

    std::random_device randDev;
	std::cout << randDev.min() << std::endl;
	std::cout << randDev.max() << std::endl;
	std::cout << randDev.entropy() << std::endl;

    std::mt19937 randGen(randDev());

	std::uniform_int_distribution<int> dist(0, 20);
    for (size_t i = 0; i < 10; ++i) {
		std::cout << dist(randGen) << " ";
    }
	std::cout << std::endl;

	std::uniform_real_distribution<float> distF(-10.0f, 40.0f);
    for (size_t i = 0; i < 10; ++i) {
		std::cout << distF(randGen) << " ";
    }
	std::cout << std::endl;
    */

    //return 0;

    // create audio system
    nu::SetWorkingDirectory("assets");

	//INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();


    std::vector<Vector2> points;

    //MAIN LOOP
    bool quit = false;
    while (!quit) {

        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
            }
        }

        //ENGINE
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();
        game.Update(dt);

        if (Engine::Get().GetInput().GetMouseDown(Input::MouseButton::Left)) {
			if (points.empty()) {
				points.push_back(Engine::Get().GetInput().GetMousePosition());
			}
            else
            {
                Vector2 lastPoint = points.back() - Engine::Get().GetInput().GetMousePosition();

                if (lastPoint.Length() > 30.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

		if (Engine::Get().GetInput().GetMousePressed(Input::MouseButton::Right)) {
			if(!points.empty()) {
				points.pop_back();
			}
		}

		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_C)) {
            if (!points.empty()) {
                points.clear();
            }
		}


        //RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(0.5f, 0.5f, 0.5f); // Set render draw color to green
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y); // Render a random point
        }
		
        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // Render the screen
    }

    //SHUTDOWN
    Engine::Get().Shutdown();


    return 0;
}

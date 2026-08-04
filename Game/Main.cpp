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

#define TEXT "Hello!\n"
#define MAX(a, b) ((a > b) ? a : b)

using namespace nu;

class Object {
public:
    Object() { std::cout << "Constructor\n"; }
    ~Object() { std::cout << "Destructor\n"; }

	Object(const Object& object) { std::cout << "Copy\n"; }
	Object& operator = (const Object& object) { std::cout << "Assignment\n"; return *this; }
};

int main() {

    std::cout << "======object test======\n";
    {
        Object objectA;
		Object objectB(objectA);
        Object objectC;
		objectC = objectA;
    }

    std::cout << "\n======raw pointers======\n";
    {
		Object* objectA = new Object();
		std::cout << objectA << std::endl;

		Object* objectB = new Object(*objectA);
		std::cout << objectB << std::endl;

		Object* objectC = nullptr;
        objectC = objectA;
		std::cout << objectC << std::endl;

        delete objectA;
		delete objectB;
        //delete objectC;
    }

	std::cout << "\n======smart pointers======\n";
	{
		std::unique_ptr<Object> objectA = std::make_unique<Object>();
		std::cout << objectA.get() << std::endl;

		std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
		std::cout << objectA.get() << std::endl;
		std::cout << objectB.get() << std::endl;

        objectB.reset();
	}

	std::cout << "\n======shared pointers======\n";
	std::shared_ptr<Object> objectC;
	{
		auto objectA = std::make_shared<Object>();
		std::cout << objectA.get() << std::endl;
		std::cout << objectA.use_count() << std::endl;
		auto objectB = objectA;
		std::cout << objectB.get() << std::endl;
		std::cout << objectB.use_count() << std::endl;
		objectC = objectA;
		std::cout << objectC.get() << std::endl;
		std::cout << objectC.use_count() << std::endl;
	}
	std::cout << objectC.use_count() << std::endl;

    //return 0;

    // create audio system
    nu::SetWorkingDirectory("assets");

	//INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/kirby.jpg", Engine::Get().GetRenderer());

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

        Engine::Get().GetRenderer().DrawTexture(*texture, 30, 30);

        Engine::Get().GetRenderer().Present(); // Render the screen
    }

    //SHUTDOWN
    Engine::Get().Shutdown();


    return 0;
}

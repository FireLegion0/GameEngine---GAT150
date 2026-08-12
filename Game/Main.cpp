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
#include <fstream>

#define TEXT "Hello!\n"
#define MAX(a, b) ((a > b) ? a : b)

using namespace nu;

class Animal {
public:
    virtual void Speak() {
		std::cout << "E" << std::endl;
    }
};

class Cat : public Animal {
public:
    void Speak() override {
		std::cout << "Meow" << std::endl;
    }
};

class Dog : public Animal {
public:
    void Speak() override {
		std::cout << "Woof" << std::endl;
    }
};

class Bird : public Animal {
public:
    void Speak() override {
		std::cout << "Tweet" << std::endl;
    }
};

Animal* AnimalFactory(const std::string& id) {
    Animal* animal = nullptr;

	if (nu::EqualsIgnoreCase(id, "Cat")) {
		animal = new Cat();
	}
	else if (nu::EqualsIgnoreCase(id, "Dog")) {
		animal = new Dog();
	}
	else if (nu::EqualsIgnoreCase(id, "Bird")) {
		animal = new Bird();
	}

    return animal;
}

std::map<std::string, std::unique_ptr<ICreator>> registry;

int main() {
	nu::SetWorkingDirectory("assets"); //Keep this at the top of main() to ensure the working directory is set before any assets are loaded

	Factory::Instance().Register<Actor>("Actor");
	Factory::Instance().Register<Object>("Object");
	Factory::Instance().Register<Player>("Player");

	auto actor = Factory::Instance().Create<Actor>("Actor");
	std::cout << actor->IsActive() << std::endl;

	auto object = Factory::Instance().Create("Object");
	std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");

	json::document_t document;
    if (json::Load("data/scene.json", document)) {
		player->Read(document);
		std::cout << player->GetName() << std::endl;
		std::cout << player->GetTag() << std::endl;

        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
    }

    return 0;

    // create audio system

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the age data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }


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

        //for (int i = 0; i < (int)points.size() - 1; i++) {
        //    Engine::Get().GetRenderer().SetColor(0.5f, 0.5f, 0.5f); // Set render draw color to green
        //    Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y); // Render a random point
        //}
		
        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present(); // Render the screen
    }

    //SHUTDOWN
    Engine::Get().Shutdown();


    return 0;
}

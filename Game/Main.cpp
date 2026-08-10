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

int main() {

    // create audio system
    nu::SetWorkingDirectory("assets");

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

    /*
    {
        //read file (input file)
		std::ifstream file("data/game.txt");
        if (file.is_open()) {
            std::string str;
			while (std::getline(file, str)) {
				std::cout << str << std::endl;
			}
        }
        else {
			std::cout << "Failed to open file: data/game.txt" << std::endl;
        }
    }

    {
		//write file (output file)
        std::ofstream file("data/game.txt", std::ios::app);
        if (file.is_open()) {
			file << "\nHave a wonderful day!\n";
        }
    }
    
    {
		//read/write (input/output file)
        std::fstream file("data/game.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open()) {
            //input
            file << "I exist\n";
            file.seekg(0);
			//output
			std::string str;
            while (std::getline(file, str)) {
                std::cout << str << std::endl;
            }
        }
    }

    //save game data
    {
        std::string name;
        int score;
        bool livin;

        bool save = false;
        if (save) {
			name = "Eddie";
			score = 10000;
			livin = true;

            //save game data
			std::ofstream file("data/saveGame.txt", std::ios::trunc);
            if (file.is_open()) {
				file << name << std::endl;
				file << score << std::endl;
				file << std::boolalpha << livin << std::endl;
            }
        }

        //load game data
		bool load = true;
        if (load) {
			std::ifstream file("data/saveGame.txt");
            if (file.is_open()) {
                std::getline(file, name);

                std::string str;
				std::getline(file, str);

                score = std::stoi(str);

                file >> std::boolalpha >> livin;
            }


        }

		std::cout << name << " | " << score << " | " << std::boolalpha << livin << std::endl;

    }
    */

    return 0;

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

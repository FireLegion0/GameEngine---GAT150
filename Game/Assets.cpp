#include "Assets.h"

using namespace nu;

namespace assets {
	Mesh playerMesh{ { Vector2{2, 0}, Vector2{0, 2}, Vector2{-3,1}, Vector2{-1,0}, Vector2{-3,-1}, Vector2{0, -2}, Vector2{ 2, 0 } }, Color{0.0f, 0.0f, 1.0f} };
	std::shared_ptr<Model> playerModel = std::make_shared<Model>(std::vector<Mesh>{playerMesh});

	Mesh enemyMesh{ { Vector2{2, 0}, Vector2{0, 2}, Vector2{-3,1}, Vector2{-1,0}, Vector2{-3,-1}, Vector2{0, -2}, Vector2{ 2, 0 } }, Color{1.0f, 0.0f, 0.0f} };
	std::shared_ptr<Model> enemyModel = std::make_shared<Model>(std::vector<Mesh>{enemyMesh});

	Mesh astroidMesh{ { { 0, -3 }, { 2, -2 }, { 3, 0 }, { 1, 1 }, { 2, 2 }, { 0, 3 }, { 0, 1 }, { -2, 2 }, { -3, 0 }, { -2, -1 }, { -2, -2 }, { 0, -3 } } , Color{1.0f, 1.0f, 1.0f} };
	std::shared_ptr<Model> astroidModel = std::make_shared<Model>(std::vector<Mesh>{astroidMesh});

	Mesh bossMesh{ { { 5, 0 }, { 3, -2 }, { 2, -1 }, { -3, -3 }, { -1, 0 }, { -3, 3 }, { 2, 1 }, { 3, 2 }, { 5, 0 } }, Color{1.0f, 0.5f, 0.0f} };
	std::shared_ptr<Model> bossModel = std::make_shared<Model>(std::vector<Mesh>{bossMesh});

	Mesh bulletMesh{ { Vector2{ -1, -1 }, Vector2{ 1, 0 }, Vector2{ -1, 1 }, Vector2{ -1, -1 }, }, Color{ 0.5f, 1.0f, 0.0f } };
	std::shared_ptr<Model> bulletModel = std::make_shared<Model>(std::vector<Mesh>{bulletMesh});
}
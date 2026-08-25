#pragma once

#include "Renderer/Model.h"
#include <memory>

namespace assets {
	extern std::shared_ptr<nu::Model> playerModel;
	extern std::shared_ptr<nu::Model> enemyModel;
	extern std::shared_ptr<nu::Model> bossModel;
	extern std::shared_ptr<nu::Model> astroidModel;
	extern std::shared_ptr<nu::Model> bulletModel;
}
#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Astroid.h"
#include "Assets.h"
#include <memory>

using namespace nu;

bool SpaceGame::Initialize() {
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/airstrike.ttf", 64.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "XENON", Color{ 1.0f, 1.0f, 1.0f });

	m_scoreText = new Text(Resources().GetWithID<Font>("score_font", "fonts/airstrike.ttf", 32.0f));
	m_livesText = new Text(Resources().GetWithID<Font>("lives_font", "fonts/airstrike.ttf", 32.0f));

	Engine::Get().GetAudio().AddSound("shoot", "Audio/laser.wav");
	Engine::Get().GetAudio().AddSound("explode", "Audio/Explosion_Debris.wav");

	return true;
}

void SpaceGame::Update(float dt) {
	switch (m_gamestate) {
		case GameState::Title:
			if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
				m_gamestate = GameState::StartGame;
			}
			break;
		case GameState::StartGame:
			m_live = 3;
			m_score = 0;
			m_spawnTime = 5.0f;
			m_gamestate = GameState::StartLevel;
			break;
		case GameState::StartLevel:
			m_scene->RemvoeAllActors();
			m_scene->Load("data/level.json");
			SpawnPlayer();
			//SpawnBoss();
			m_spawnTime = 5.0f;
			m_gamestate = GameState::Game;
			break;
		case GameState::Game:
			m_spawnTimer -= dt;
			m_bossSpawnTimer -= dt;
			if (m_spawnTimer <= 0) {
				m_spawnTimer = m_spawnTime;
				SpawnEnemy();
				SpawnAstroid();
			}
			if (m_bossSpawnTimer <= 0) {
				m_bossSpawnTimer = m_bossSpawnTime;
				SpawnBoss();
			}
			break;
		case GameState::GameOver:
			m_scene->RemvoeAllActors();
			m_stateTime -= dt;
			if (m_stateTime <= 0) {
				m_gamestate = GameState::Title;
			}
			break;
	}

	Game::Update(dt);
}

void SpaceGame::Draw(Renderer& renderer) {
	renderer.EnableCamera(false);

	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/forest_background.png", Engine::Get().GetRenderer()), 500, 500);

	switch (m_gamestate) {
	case GameState::Title:
		m_titleText->Draw(renderer, 400, 400);
		break;
	case GameState::StartGame:
		break;
	case GameState::StartLevel:
		break;
	case GameState::Game:
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30, 30);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_live), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() - 160, 30);
		
		break;
	case GameState::GameOver:
		break;
	}
	renderer.EnableCamera(true);

	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
	m_live--;
	if (m_live <= 0) {
		m_gamestate = GameState::GameOver;
	}
	else {
		m_gamestate = GameState::StartLevel;
	}

	m_stateTime = 2.0f;
}

void SpaceGame::SpawnPlayer() {
	auto actor = Factory::Instance().Create<Actor>("PlayerProto");
	m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy() {
	auto actor = Factory::Instance().Create<Actor>("EnemyProto");
	actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor));

	auto actor2 = Factory::Instance().Create<Actor>("FlyingEnemyProto");
	actor2->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	m_scene->AddActor(std::move(actor2));
}

void SpaceGame::SpawnAstroid() {
	//auto actor = Factory::Instance().Create<Actor>("AstroidProto");
	//actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	//m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnBoss() {
	//auto actor = Factory::Instance().Create<Actor>("BossProto");
	//actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });
	//m_scene->AddActor(std::move(actor));
}

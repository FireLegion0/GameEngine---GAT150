#include "SpaceGame.h"
#include "../Engine/Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Astroid.h"
#include "Assets.h"

using namespace nu;

bool SpaceGame::Initialize() {
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleFont = new Font();
	m_titleFont->Load("fonts/airstrike.ttf", 64);

	m_titleText = new Text(m_titleFont);
	m_titleText->Create(Engine::Get().GetRenderer(), "XENON", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = new Font();
	m_gameFont->Load("fonts/airstrike.ttf", 32);

	m_scoreText = new Text(m_gameFont);
	m_livesText = new Text(m_gameFont);

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
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	playerDesc.model = assets::playerModel;
	playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };
	playerDesc.damping = 3.0f;
	playerDesc.speed = 2000.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>( playerDesc );
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy() {
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.tag = "Enemy";
	enemyDesc.model = assets::enemyModel;
	enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
	enemyDesc.damping = 3.0f;
	enemyDesc.speed = RandomFloat(100.0f, 2000.0f);

	//std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemyDesc);
	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::SpawnAstroid() {
	AstroidDesc astroidDesc;
	astroidDesc.tag = "Astroid";
	astroidDesc.name = "Astroid";
	astroidDesc.model = assets::astroidModel;
	astroidDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
	astroidDesc.damping = 3.0f;
	astroidDesc.speed = RandomFloat(100.0f, 2000.0f);

	//Astroid* astroid = new Astroid{ astroidDesc };
	m_scene->AddActor(std::move(std::make_unique<Astroid>(astroidDesc)));
}

void SpaceGame::SpawnBoss() {
	BossDesc bossDesc;
	bossDesc.name = "Boss";
	bossDesc.tag = "Enemy";
	bossDesc.health = 3;
	bossDesc.model = assets::bossModel;
	bossDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
	bossDesc.damping = 3.0f;
	bossDesc.speed = RandomFloat(100.0f, 2000.0f);

	Boss* boss = new Boss{ bossDesc };
	m_scene->AddActor(std::move(std::make_unique<Boss>(bossDesc)));
}

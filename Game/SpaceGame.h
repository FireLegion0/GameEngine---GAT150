#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"

class SpaceGame : public nu::Game {
public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) :
		Game{ scene }
	{ }

	bool Initialize() override;


	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	void OnPlayerDeath();
	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnAstroid();
	void SpawnBoss();

	int m_score{ 0 };
	int m_live{ 0 };

	float m_stateTime = 0.0f;

	float m_spawnTime = 5.0f;
	float m_spawnTimer = m_spawnTime;

	float m_bossSpawnTime = 15.0f;
	float m_bossSpawnTimer = m_bossSpawnTime;

	GameState m_gamestate = GameState::Title;

	nu::res_t<nu::Font> m_titleFont;
	nu::res_t<nu::Font> m_gameFont;

	//nu::Font* m_titleFont{ nullptr };
	nu::Text* m_titleText{ nullptr };

	//nu::Font* m_gameOverFont{ nullptr };
	nu::Text* m_gameOverText{ nullptr };

	//nu::Font* m_gameFont{ nullptr };
	nu::Text* m_scoreText{ nullptr };
	nu::Text* m_livesText{ nullptr };
};
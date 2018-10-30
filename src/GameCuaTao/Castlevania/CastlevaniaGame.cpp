#include "Direct2DGame/Input/InputHelper.h"
#include "CastlevaniaGame.h"
#include "Scenes/MenuScene.h"
#include "Settings/Fonts.h"
#include "Utilities/AudioManager.h"
#include "Settings/Audios.h"

using namespace Castlevania;

CastlevaniaGame::CastlevaniaGame()
{
	content->SetRootDirectory("Castlevania/Content");

	window->Width(528);
	window->Height(487);
}

void CastlevaniaGame::Initialize()
{
	Game::Initialize();

	sceneManager = std::make_unique<SceneManager>(*this);
	sceneManager->SetNextScene(Scene::MENU);
}

void CastlevaniaGame::LoadContent()
{
	Fonts::LoadContent(*content);
	AudioManager::LoadContent(*content, GAME_AUDIO);
}

void CastlevaniaGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	InputHelper::Update();
	sceneManager->Update(deltaTime);
}

void CastlevaniaGame::Draw(GameTime gameTime)
{
	GetGraphicsDevice().Clear(Color::LavenderBlue());

	sceneManager->Draw(gameTime);
}
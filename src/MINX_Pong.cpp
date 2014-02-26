
#include "MINX_Pong.h"

using namespace MINX_MINX_PONG;


MINX_Pong::MINX_Pong() : Game::Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.

	isRunning = true;
	Game::SetVideoOptions(640, 480, 32, 0, "MINX_Pong");
}

void MINX_Pong::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	Game::Initialize();
}

void MINX_Pong::LoadContent()
{
	//Put stuff here that loads content for your game.
	Game::LoadContent();
}

void MINX_Pong::UnloadContent()
{
	//Put stuff here that unloads content from your game.
	Game::UnloadContent();
}

void MINX_Pong::Update(GameTime * gameTime)
{
	//Put stuff here to update the logic in your game each tick.
	Game::Update(gameTime);
}

void MINX_Pong::Draw(GameTime * gameTime)
{
	gameWindow->Clear();

	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}

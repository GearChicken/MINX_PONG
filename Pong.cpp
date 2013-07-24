/*
    MINX - A C++ Graphics and Input Wrapper Library
    Copyright (C) 2013  MINX Team

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	*/
#include "Pong.h"
#include <iostream>

using namespace MINX_PONG;
using namespace MINX;

Vector2 paddlePosition = Vector2(0,0);
Pong::Pong()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	isRunning = true;
}

void Pong::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	
	keyboard= new Input::Keyboard(this);
	keyboard->Initialize();

	Game::Initialize();

	SDL_WM_SetCaption("MINX Pong", "MINX Pong");
}

void Pong::LoadContent()
{
	//Put stuff here that loads content for your game.
	Game::LoadContent();
}

void Pong::UnloadContent()
{
	//Put stuff here that unloads content from your game.
	Game::UnloadContent();
}

void Pong::Update(GameTime * gameTime)
{
	//Put stuff here to update the logic in your game each tick.
	keyboard->Update(gameTime);
	if(keyboard->getButton(SDLK_UP).state)
	{
		paddlePosition.Y--;
	}
	if(keyboard->getButton(SDLK_DOWN).state)
	{
		paddlePosition.Y++;
	}
	cout << paddlePosition.Y << "\n";
	SDL_Delay(10);
	Game::Update(gameTime);
}

void Pong::Draw(GameTime * gameTime)
{

	SDL_FillRect(gameWindow->screen, NULL, 0x000000);

	Graphics::Primitives::drawRectangle(new Graphics::Color(255,255,255,0), 50, paddlePosition.Y, 100, 100, gameWindow->screen);
	
	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}

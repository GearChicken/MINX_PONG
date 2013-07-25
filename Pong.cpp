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
#include "Point.h"
#include "Vector2.h"


using namespace MINX_PONG;
using namespace MINX;

Point paddlePosition = Point(50,0);
Point paddle2Position = Point(590,0);
Point ballPosition = Point(320,240);
Vector2 ballVelocity = Vector2(1,1);
int playerScore = 0;
int computerScore = 0;
Graphics::Color * white = new Graphics::Color(255,255,255,255);
Pong::Pong() : Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	isRunning = true;
}

void Pong::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	
	keyboard= new Input::Keyboard(this);
	paddle2Position.Y = rand() % 380;
	ballPosition.Y = rand() % 140 + 100;
	ballPosition.X = rand() % 200 + 220;
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
	if(keyboard->getButton(SDLK_UP).state)
	{
		paddlePosition.Y--;
	}
	if(keyboard->getButton(SDLK_DOWN).state)
	{
		paddlePosition.Y++;
	}
	if(paddlePosition.Y < 5)
	{
		paddlePosition.Y = 5;
	}
	if(paddlePosition.Y > 380)
	{
		paddlePosition.Y = 380;
	}
	if(paddle2Position.Y > 375)
	{
		paddle2Position.Y = 375;
	}
	if(ballPosition.X < paddlePosition.X + 20 && ballPosition.X > paddlePosition.X && ballPosition.Y + 16 > paddlePosition.Y && ballPosition.Y < paddlePosition.Y + 100)
	{
		ballVelocity.X*=-1;
	}
	if(ballPosition.X + 16 > paddle2Position.X && ballPosition.X + 16 < paddle2Position.X + 20 && ballPosition.Y + 16 > paddle2Position.Y && ballPosition.Y < paddle2Position.Y + 100)
	{
		ballVelocity.X*=-1;
	}
	if(ballPosition.Y < 0 || ballPosition.Y > 464)
	{
		ballVelocity.Y*=-1;
	}
	if(ballVelocity.X > 0)
	{
		if(ballPosition.Y < paddle2Position.Y+50)
		{
			paddle2Position.Y--;
		} else
		if(ballPosition.Y > paddle2Position.Y+50)
		{
			paddle2Position.Y++;
		}
	}
	if(ballPosition.X > 624){
		computerScore++;
		ballPosition.Y = rand() % 140 + 100;
		ballPosition.X = rand() % 200 + 220;
	}
	if(ballPosition.X < 0){
		playerScore++;
		ballPosition.Y = rand() % 140 + 100;
		ballPosition.X = rand() % 200 + 220;
	}
	ballPosition.X += (int)ballVelocity.X;
	ballPosition.Y += (int)ballVelocity.Y;
	SDL_Delay(5);
	Game::Update(gameTime);
}

void Pong::Draw(GameTime * gameTime)
{

	SDL_FillRect(gameWindow->screen, NULL, 0x000000);

	Graphics::Primitives::drawRectangle(white, paddlePosition.X, paddlePosition.Y, 20, 100, gameWindow->screen);
	Graphics::Primitives::drawRectangle(white, ballPosition.X, ballPosition.Y, 16, 16, gameWindow->screen);
	Graphics::Primitives::drawRectangle(white,paddle2Position.X, paddle2Position.Y, 20, 100, gameWindow->screen);
	
	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}

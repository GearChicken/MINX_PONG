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
#include "Graphics/GameWindow.h"
#include "Audio/AudioClip.h"
#include "Pong.h"
#include <iostream>
#include "Point.h"
#include "Vector2.h"
#include "Graphics/Font.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <Input/Mouse.h>
using namespace MINX_PONG;
using namespace MINX;
using namespace MINX::Graphics;
using namespace MINX::Input;
using namespace MINX::Audio;
using namespace std;

TTF_Font* font;
AudioClip collisionSound("ball.wav",false,false);
Point paddlePosition = Point(50,0);
Vector2 paddleVelocity = Vector2(0,0);
Point paddle2Position = Point(590,0);
Vector2 paddle2Velocity = Vector2(0,0);
Point ballPosition = Point(320,240);
Vector2 ballVelocity = Vector2(1,1);
Mouse * mouse;
int playerScore = 0;
int computerScore = 0;
Graphics::Color * white = new Graphics::Color(255,255,255,255);

string ToString(int val)
{
	stringstream ss;
	ss << val;
	return ss.str();
}

string intToBinary(int number)
{
	string result;
	do result.push_back('0' + (number & 1));
	while (number >>=1);
	
	reverse(result.begin(), result.end());
	return result;
}
void drawScore(string scoreString, Point drawingPoint, GameWindow* gameWindow)
{
	for(string::size_type i = 0; i < scoreString.size(); ++i)
	{
		if(scoreString[i] == *"0")
		{
			Graphics::Primitives::drawOutlineRectangle(white, drawingPoint.X + i*10, drawingPoint.Y, 5, 10, gameWindow->screen);
		}
		if(scoreString[i] == *"1")
		{
			Graphics::Primitives::drawRectangle(white, drawingPoint.X + i*10, drawingPoint.Y, 5, 10, gameWindow->screen);
		}
	}
}
Pong::Pong() : Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	desiredFPS = 180;
	isRunning = true;
	desiredFPS = 200;
}

void Pong::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	
	keyboard= new Input::Keyboard(this);
	mouse = new Mouse(this);
	paddle2Position.Y = rand() % 380;
	ballPosition.Y = rand() % 140 + 100;
	ballPosition.X = rand() % 200 + 220;
	Game::Initialize();

	SDL_WM_SetCaption("MINX Pong", "MINX Pong");
}

void Pong::LoadContent()
{
	//Put stuff here that loads content for your game.
	font = content->loadTTFFont("Ubuntu-B.ttf", 24, "font");
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
	if(keyboard->getButton(SDLK_UP).state || mouse->getButton(4).state) //4 is scroll up
	{
		paddleVelocity.Y =-1;
	}
	if(keyboard->getButton(SDLK_DOWN).state || mouse->getButton(5).state) //5 is scroll down
	{
		paddleVelocity.Y =1;
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
		ballVelocity.Y += paddleVelocity.Y/3;
		collisionSound.setPosition(270,0);
		collisionSound.play();
	}
	if(ballPosition.X + 16 > paddle2Position.X && ballPosition.X + 16 < paddle2Position.X + 20 && ballPosition.Y + 16 > paddle2Position.Y && ballPosition.Y < paddle2Position.Y + 100)
	{
		ballVelocity.Y += paddle2Velocity.Y/3;
		ballVelocity.X*=-1;
		collisionSound.setPosition(90,0);
		collisionSound.play();
	}
	if(ballPosition.Y < 0 || ballPosition.Y > 464)
	{
		ballVelocity.Y*=-1;
		collisionSound.setPosition(360+(ballPosition.X-320)*90/320,0);
		collisionSound.play();
	}
	if(ballVelocity.X > 0)
	{
		if(ballPosition.Y < paddle2Position.Y+50)
		{
			paddle2Velocity.Y =-1;
		} else
		if(ballPosition.Y > paddle2Position.Y+50)
		{
			paddle2Velocity.Y =+1;
		}
	}
	if(ballPosition.X > 624){
		playerScore++;
		ballPosition.Y = rand() % 140 + 100;
		ballPosition.X = rand() % 200 + 220;
		ballVelocity = Vector2(-1,-1);
	}
	if(ballPosition.X < 0){
		computerScore++;
		ballPosition.Y = rand() % 140 + 100;
		ballPosition.X = rand() % 200 + 220;
		ballVelocity = Vector2(1,1);	
	}
	if(ballVelocity.lengthSquared() > 9)
	{
		ballVelocity = ballVelocity.normalize();
		ballVelocity = ballVelocity * 3;
	}
	if(abs(ballVelocity.X) < 1)
	{
		ballVelocity.X*=1.5;
	}
	paddlePosition.Y += paddleVelocity.Y;
	paddle2Position.Y += paddle2Velocity.Y;
	ballPosition.X += (int)ballVelocity.X;
	ballPosition.Y += (int)ballVelocity.Y;
	paddleVelocity.Y = 0;
	paddle2Velocity.Y = 0;
	Game::Update(gameTime);
}

void Pong::Draw(GameTime * gameTime)
{

	SDL_FillRect(gameWindow->screen, NULL, 0x000000);

	Graphics::Primitives::drawRectangle(white, paddlePosition.X, paddlePosition.Y, 20, 100, gameWindow->screen);
	Graphics::Primitives::drawRectangle(white, ballPosition.X, ballPosition.Y, 16, 16, gameWindow->screen);
	Graphics::Primitives::drawRectangle(white,paddle2Position.X, paddle2Position.Y, 20, 100, gameWindow->screen);
	
	DrawString(50,50, "Player Score: " + ToString(playerScore), gameWindow->screen, font);
	DrawString(500,430, "Computer Score: " + ToString(computerScore), gameWindow->screen, font);
	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}

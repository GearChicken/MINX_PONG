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
//AUTOGENERATED FILE: DO NOT EDIT
#include "Graphics/Primitives.h"
#include "Input/Keyboard.h"
#include "Game.h"
#include "GameTime.h"
#include "Point.h"
#ifndef PONG_H_
#define PONG_H_

using namespace MINX;

namespace MINX_PONG
{
	class Pong : public Game
	{
		public:
			Pong();
			void Initialize();
			void LoadContent();
			void UnloadContent();
			void Update(GameTime * gameTime);
			void Draw(GameTime * gameTime);
			Input::Keyboard* keyboard;
	};
}

#endif

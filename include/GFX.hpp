/*
	Diese Datei ist Teil von Stack-Todo-Liste.
	Copyright (C) 2021 bei SuperSaiyajinStackZ.

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

	Additional Terms 7.b and 7.c of GPLv3 apply to this file:
		* Requiring preservation of specified reasonable legal notices or
		  author attributions in that material or in the Appropriate Legal
		  Notices displayed by works containing it.
		* Prohibiting misrepresentation of the origin of that material,
		  or requiring that modified versions of such material be marked in
		  reasonable ways as different from the original version.
*/

#ifndef _STACK_TODO_LISTE_GFX_HPP
#define _STACK_TODO_LISTE_GFX_HPP

#include "Core.hpp"
#include "screenCommon.hpp"
#include "sprites.h"

#define BG_FARBE C2D_Color32(38, 38, 38, 255)
#define BAR_FARBE C2D_Color32(64, 64, 64, 255)
#define TEXT_FARBE C2D_Color32(180, 180, 180, 255)
#define BOX_HOEHE 70 // Box Höhe.
#define BOX_BREITE 360 // Box Breite.

namespace GFX {
	extern C2D_SpriteSheet Sprites;
	void AufgabenBlock(const AufgabenListe &Aufgabe, const uint8_t YPos);
	void DrawBasis(const bool Bildschirm);
};

#endif
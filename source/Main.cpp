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

#include "GFX.hpp"
#include "Menu.hpp"
#include <3ds.h> // 3DS relevant.
#include <dirent.h> // Für mkdir.

bool Verlassen = false;

/*
	Der Touch-Position Klick Handle.

	const Structs::ButtonPos Position: Die Position, auf welche der Check durchgeführt werden soll.
	touchPosition Touch: Die TouchPosition.

	Wiedergibt true, falls angeklickt -> Ansonsten false.
*/
bool Klick(const Structs::ButtonPos Position, touchPosition Touch) {
	if (Touch.px >= Position.x && Touch.px <= (Position.x + Position.w) && Touch.py >= Position.y && Touch.py <= (Position.y + Position.h)) return true;
	return false;
};

int main() {
	/* Initialisiere den notwendigen Kram für die Anwendung. */
	romfsInit();
	gfxInitDefault();
	Gui::init();

	/* Erstelle die Verzeichnisse, falls nicht vorhanden. */
	mkdir("sdmc:/3ds", 0x777);
	mkdir("sdmc:/3ds/StackTODOListe", 0x777);

	/* Initialisiere die SpriteSheet. */
	Gui::loadSheet("romfs:/gfx/sprites.t3x", GFX::Sprites);

	/* Gehe zum Menü. */
	Gui::setScreen(std::make_unique<Menu>(), false, true);

	/* Haupt-Logik. */
	while(aptMainLoop() && !Verlassen) {
		/* Scanne den Input. */
		touchPosition Touch;
		hidScanInput();
		const uint32_t Down = hidKeysDown();
		const uint32_t Held = hidKeysHeld();
		hidTouchRead(&Touch);

		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		Gui::DrawScreen(true);
		Gui::ScreenLogic(Down, Held, Touch, false, true);
		C3D_FrameEnd(0);
	}

	/* Deinitialisiere alles und beende die Anwendung. */
	Gui::unloadSheet(GFX::Sprites);
	Gui::exit();
	gfxExit();
	romfsExit();
	return 0;
};
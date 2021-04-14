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

#include "App.hpp"
#include "GFX.hpp"

/* Alle Menüs. */
#include "Aufgabenliste.hpp"
#include "AddierMenu.hpp"
#include "MitwirkendeMenu.hpp"
#include "UnterMenu.hpp"

#include <3ds.h>
#include <dirent.h>

/* Ein paar Variablen. */
App::MenuTyp App::Menutyp = App::MenuTyp::UnterMenu;
AufgabenListe App::Aufgabe;
std::unique_ptr<AufgabenListeCore> App::Aufgaben = nullptr;
size_t App::Index = 0, App::AufgabenIndex = 0, App::MenuIndex = 0;
bool App::AufgabeSelected = false, App::Verlassen = false;

/*
	Initialisiere die Anwendung.
*/
void App::Initialisieren() {
	/* Initialisiere den notwendigen Kram für die Anwendung. */
	romfsInit();
	gfxInitDefault();
	Gui::init();

	/* Erstelle die Verzeichnisse, falls nicht vorhanden. */
	mkdir("sdmc:/3ds", 0x777);
	mkdir("sdmc:/3ds/StackTODOListe", 0x777);

	/* Initialisiere die SpriteSheet. */
	Gui::loadSheet("romfs:/gfx/sprites.t3x", GFX::Sprites);

	App::Aufgaben = std::make_unique<AufgabenListeCore>();
	if (App::Aufgaben->AufgabenAnzahl() > 0) App::Menutyp = App::MenuTyp::Liste;
};

/*
	Die Hauptlogik der Anwendung.
*/
int App::HauptLogik() {
	App::Initialisieren();

	while(aptMainLoop() && !App::Verlassen) {
		Gui::clearTextBufs();
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		App::Zeichnung();
		App::Logik();
		C3D_FrameEnd(0);
	};

	App::Beenden();
	return 0;
};

/*
	Beende die Anwendung.
*/
void App::Beenden() {
	App::Aufgaben->ListeSpeichern();
	Gui::unloadSheet(GFX::Sprites);
	Gui::exit();
	gfxExit();
	romfsExit();
};

/*
	Der Zeichnungs-Part der Anwendung.
*/
void App::Zeichnung() {
	Aufgabenliste::ZeichneListe();
	GFX::DrawBasis(false);

	switch(App::Menutyp) {
		case App::MenuTyp::Liste:
		case App::MenuTyp::UnterMenu:
			UnterMenu::ZeichneMenu();
			break;

		case App::MenuTyp::Addieren:
			AddierMenu::ZeichneMenu();
			break;

		case App::MenuTyp::Mitwirkende:
			MitwirkendeMenu::ZeichneMenu();
			break;
	}
};

/*
	Der Logik-Part der Anwendung.
*/
void App::Logik() {
	uint32_t Down = 0, Held = 0;
	touchPosition Touch;

	hidScanInput();
	Down = hidKeysDown();
	Held = hidKeysHeld();
	hidTouchRead(&Touch);

	switch(App::Menutyp) {
		case App::MenuTyp::Liste:
			Aufgabenliste::ListenLogik(Down, Held);
			UnterMenu::MenuListenLogik(Down, Held, Touch);
			break;

		case App::MenuTyp::UnterMenu:
			UnterMenu::MenuLogik(Down, Held, Touch);
			UnterMenu::MenuListenLogik(Down, Held, Touch);
			break;

		case App::MenuTyp::Addieren:
			AddierMenu::MenuLogik(Down, Held, Touch);
			break;

		case App::MenuTyp::Mitwirkende:
			MitwirkendeMenu::MenuLogik(Down, Held, Touch);
			break;
	}
};

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
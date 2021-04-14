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
#include "UnterMenu.hpp"

static const std::vector<Structs::ButtonPos> UnterMenuSchaltflaechen = {
	{ 30, 40, 120, 70 }, // Aufgabe Hinzufügen.
	{ 170, 40, 120, 70 }, // Mitwirkende Ansehen.
	{ 30, 130, 120, 70 }  // Aufgabenliste Leeren.
};

static const Structs::ButtonPos MenuVerlassen = { 0, 0, 20, 20 };
extern bool Klick(const Structs::ButtonPos Position, touchPosition Touch);

void UnterMenu::ZeichneMenu() {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Unter-Menü"); // Menü Titel.
	if (App::Aufgaben->AufgabenAnzahl() > 0) {
		Gui::DrawSprite(GFX::Sprites, (App::Menutyp == App::MenuTyp::Liste ? sprites_down_idx : sprites_up_idx), 2, 1); // Hoch / Runter Pfeil.
	}

	/* Aufgabe Hinzufügen. */
	Gui::Draw_Rect(30, 50, 120, 70, BAR_FARBE);
	Gui::DrawString(41, 60, 0.4f, TEXT_FARBE, "Aufgabe Hinzufügen");
	Gui::DrawSprite(GFX::Sprites, sprites_add_idx, 30 + 48, 85);

	/* Mitwirkende Ansehen. */
	Gui::Draw_Rect(170, 50, 120, 70, BAR_FARBE);
	Gui::DrawString(178, 60, 0.4f, TEXT_FARBE, "Mitwirkende Ansehen");
	Gui::DrawSprite(GFX::Sprites, sprites_credits_idx, 170 + 48, 85);

	/* Aufgabenliste Leeren. */
	Gui::Draw_Rect(30, 140, 120, 70, BAR_FARBE);
	Gui::DrawString(39, 150, 0.4f, TEXT_FARBE, "Aufgabenliste Leeren");
	Gui::DrawSprite(GFX::Sprites, sprites_remove_idx, 30 + 48, 175);

	/* Zeichne den Stift. */
	if (App::Menutyp == App::MenuTyp::UnterMenu) Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, UnterMenuSchaltflaechen[App::MenuIndex].x + 80, UnterMenuSchaltflaechen[App::MenuIndex].y + 30);
};

void UnterMenu::Leeren() {
	App::Index = 0;

	while(App::Aufgaben->AufgabenAnzahl() > 0) { App::Aufgaben->Entferne(0); };
};

void UnterMenu::MenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	if (Down & KEY_DOWN) {
		if (App::MenuIndex == 0) App::MenuIndex = 2;
	}

	if (Down & KEY_UP) {
		if (App::MenuIndex > 1) App::MenuIndex -= 2;
	}

	if (Down & KEY_RIGHT) {
		if (App::MenuIndex == 0) App::MenuIndex++;
	}

	if (Down & KEY_LEFT) {
		if (App::MenuIndex == 1) App::MenuIndex--;
	}

	if (Down & KEY_A) {
		switch(App::MenuIndex) {
			case 0: // Aufgabe Hinzufügen.
				App::Menutyp = App::MenuTyp::Addieren;
				break;

			case 1: // Mitwirkende / Credits Ansehen.
				App::Menutyp = App::MenuTyp::Mitwirkende;
				break;

			case 2: // Aufgabenliste Leeren.
				UnterMenu::Leeren();
				break;
		}
	}

	if (Down & KEY_X) {
		if (App::Aufgaben->AufgabenAnzahl() > 0) App::Menutyp = App::MenuTyp::Liste; // Wechsel zum TODO-Listen Modus.
	}
};

void UnterMenu::MenuListenLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	/* Touch-Klick Handle. */
	if (Down & KEY_TOUCH) {
		/* Wechsel zwischen Liste und Unter-Menü. */
		if (Klick(MenuVerlassen, Touch)) {
			if (App::Aufgaben->AufgabenAnzahl() > 0) App::Menutyp = (App::Menutyp == App::MenuTyp::Liste ? App::MenuTyp::UnterMenu : App::MenuTyp::Liste);

		/* Aufgabe Hinzufügen. */
		} else if (Klick(UnterMenuSchaltflaechen[0], Touch)) {
			App::Menutyp = App::MenuTyp::Addieren;

		/* Mitwirkende / Credits Ansehen. */
		} else if (Klick(UnterMenuSchaltflaechen[1], Touch)) {
			App::Menutyp = App::MenuTyp::Mitwirkende;

		/* Aufgabenliste Leeren. */
		} else if (Klick(UnterMenuSchaltflaechen[2], Touch)) {
			UnterMenu::Leeren();
			App::Menutyp = App::MenuTyp::UnterMenu;
		}
	}

	if (Down & KEY_START) App::Verlassen = true;
}
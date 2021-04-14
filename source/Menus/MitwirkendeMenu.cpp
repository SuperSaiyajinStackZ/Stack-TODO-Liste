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
#include "MitwirkendeMenu.hpp"

static const Structs::ButtonPos MenuVerlassen = { 0, 0, 20, 20 };
extern bool Klick(const Structs::ButtonPos Position, touchPosition Touch);

void MitwirkendeMenu::ZeichneMenu() {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Mitwirkende-Menü"); // Menü-Titel.
	Gui::DrawSprite(GFX::Sprites, sprites_back_idx, 2, 1); // Zurück.

	/* Mitwirkenden Text. */
	Gui::DrawStringCentered(0, 35, 0.6f, TEXT_FARBE, "Entwickelt von SuperSaiyajinStackZ.");
	Gui::DrawStringCentered(0, 60, 0.45f, TEXT_FARBE, "Universal-Team: Universal-Core.");

	/* Bild von StackZ. */
	Gui::DrawSprite(GFX::Sprites, sprites_stackz_idx, 100, 100);
};

void MitwirkendeMenu::MenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	if ((Down & KEY_B) || (Down & KEY_TOUCH && Klick(MenuVerlassen, Touch))) App::Menutyp = App::MenuTyp::UnterMenu; // Gehe zurück zum Unter-Menü.
};
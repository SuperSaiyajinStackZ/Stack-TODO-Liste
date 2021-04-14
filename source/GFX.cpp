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

C2D_SpriteSheet GFX::Sprites = nullptr;

/*
	Zeichnet einen Aufgaben-Block.

	const AufgabenListe &Aufgabe: Die Aufgabe welche gezeichnet werden soll.
	const uint8_t YPos: Die Y-Position des Blocks. uint8_t, weil die Höhe nur 240 Pixel ist.
*/
void GFX::AufgabenBlock(const AufgabenListe &Aufgabe, const uint8_t YPos) {
	/* Zeichne den Block. */
	Gui::Draw_Rect(20, YPos, BOX_BREITE, BOX_HOEHE, BAR_FARBE);

	/* Zeichne den Text für den Block. */
	Gui::DrawStringCentered(0, YPos + 5, 0.6f, TEXT_FARBE, Aufgabe.Titel, BOX_BREITE - 20); // Titel.
	Gui::DrawString(20 + 5, YPos + 25, 0.45f, TEXT_FARBE, Aufgabe.Beschreibung, BOX_BREITE - 10, BOX_HOEHE - 25, nullptr, C2D_WordWrap); // Beschreibung.

	/* Minus zum Entfernen. */
	Gui::DrawSprite(GFX::Sprites, sprites_remove_idx, (20 + BOX_BREITE) - 24, YPos);

	/* Zeichne den Erledigt Status. */
	Gui::DrawSprite(GFX::Sprites, sprites_checkbox_idx, (20 + BOX_BREITE) - 24, YPos + (BOX_HOEHE - 24));
	if (Aufgabe.Erledigt) Gui::DrawSprite(GFX::Sprites, sprites_mark_idx, (20 + BOX_BREITE) - 20, YPos + (BOX_HOEHE - 20));

	if (Aufgabe.ZeitBeinhaltet) {
		/* Zeige die Aufgaben-Zeit an. */
		Gui::DrawStringCentered(0, YPos - 15, 0.4f, TEXT_FARBE, "Aufgaben-Zeit: Jahr: " +
			std::to_string(Aufgabe.Jahr) +
			", Monat: " + std::to_string(Aufgabe.Monat) +
			", Tag: " + std::to_string(Aufgabe.Tag)
		);
	}
};

/*
	Zeichnet den Basis Bildschirm.

	const bool Bildschirm: Ob der obere (true) oder untere (false) Bildschirm gezeichnet werden soll.
*/
void GFX::DrawBasis(const bool Bildschirm) {
	Gui::ScreenDraw((Bildschirm ? Top : Bottom));

	Gui::Draw_Rect(0, 0, (Bildschirm ? 400 : 320), 20, BAR_FARBE);
	Gui::Draw_Rect(0, 20, (Bildschirm ? 400 : 320), 220, BG_FARBE);
};
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
#include "Aufgabenliste.hpp"
#include "GFX.hpp"
#include "Utils.hpp"

const std::vector<Structs::ButtonPos> AufgabenFlaechen = {
	/* TODO-Listen Boxen. */
	{ 20, 40, BOX_BREITE, BOX_HOEHE },
	{ 20, 140, BOX_BREITE, BOX_HOEHE },

	{ 365, 60, 15, 15 }, // Ausgewählte Box.
	{ 365, 40, 15, 15 }, // Minus.
	{ 365, 80, 15, 15 }  // Markierungs-Box.
};

void Aufgabenliste::ZeichneListe() {
	GFX::DrawBasis(true);
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Stack-TODO-Liste");
	Gui::DrawString(395, 1, 0.55f, TEXT_FARBE, "v1.1.0", 0, 0, nullptr, C2D_AlignRight);
	Gui::DrawStringCentered(-165, 0, 0.35f, TEXT_FARBE, Utils::DatumZeit(), 0, 0, nullptr);

	/* Zeichne die Top Aufgaben-Liste. */
	if (App::Aufgaben->AufgabenAnzahl() > 0) {
		if (App::Index < 2) {
			GFX::AufgabenBlock(App::Aufgaben->Aufgabe(0), AufgabenFlaechen[0].y);
			if (App::Aufgaben->AufgabenAnzahl() > 1) GFX::AufgabenBlock(App::Aufgaben->Aufgabe(1), AufgabenFlaechen[1].y);

		} else {
			GFX::AufgabenBlock(App::Aufgaben->Aufgabe(App::Index - 1), AufgabenFlaechen[0].y);
			GFX::AufgabenBlock(App::Aufgaben->Aufgabe(App::Index), AufgabenFlaechen[1].y);
		}

		/* Listen-Modus -> Zeichne den Stift auf den oberen Bildschirm. */
		if (App::Menutyp == App::MenuTyp::Liste) {
			if (!App::AufgabeSelected) Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, AufgabenFlaechen[2].x, AufgabenFlaechen[2].y + (App::Index > 0 ? 100 : 0));
			else { // Falls die Aufgabe ausgewählt wurde.
				switch(App::AufgabenIndex) {
					case 0:
						Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, AufgabenFlaechen[3].x, AufgabenFlaechen[3].y + (App::Index > 0 ? 100 : 0));
						break;

					case 1:
						Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, AufgabenFlaechen[4].x, AufgabenFlaechen[4].y + (App::Index > 0 ? 100 : 0));
						break;
				}
			}
		}
	}
};

/* Entfernt die ausgewählte Aufgabe. */
void Aufgabenliste::AufgabeEntfernen() {
	if (App::Aufgaben->AufgabenAnzahl() > 0) {
		App::AufgabeSelected = false;
		App::Aufgaben->Entferne(App::Index);

		if (App::Aufgaben->AufgabenAnzahl() > 0) {
			/* Aktualisiere Aufgaben-Index, falls notwendig. */
			if (App::Index > App::Aufgaben->AufgabenAnzahl() - 1) App::Index = App::Aufgaben->AufgabenAnzahl() - 1;

			/* Falls 0 Aufgaben, gehe zum Unter-Menü. */
		} else {
			App::Menutyp = App::MenuTyp::UnterMenu;
		}
	}
};

void Aufgabenliste::ListenLogik(uint32_t Down, uint32_t Held) {
	if (Down & KEY_DOWN) {
		if (!App::AufgabeSelected) { // Listen Index.
			if (App::Index < App::Aufgaben->AufgabenAnzahl() - 1) App::Index++;

		} else { // Aufgaben Index.
			if (App::AufgabenIndex < 1) App::AufgabenIndex++;
		}
	}

	if (Down & KEY_UP) {
		if (!App::AufgabeSelected) { // Listen Index.
			if (App::Index > 0) App::Index--;

		} else { // Aufgaben Index.
			if (App::AufgabenIndex > 0) App::AufgabenIndex--;
		}
	}

	if (Down & KEY_A) {
		if (!App::AufgabeSelected) { // Listen Index.
			App::AufgabeSelected = true;

		} else { // Aufgaben Index.
			switch(App::AufgabenIndex) {
				case 0: // Aufgabe Entfernen.
					Aufgabenliste::AufgabeEntfernen();
					break;

				case 1: // Erledigt umschalten.
					App::Aufgaben->Erledigt(App::Index, !App::Aufgaben->Erledigt(App::Index));
					break;
			}
		}
	}

	/* Falls die Aufgabe ausgewählt worden ist, gehe zurück zum nicht ausgewählten Modus. */
	if (Down & KEY_B) {
		if (App::AufgabeSelected) App::AufgabeSelected = false;
	}

	/* Gehe zum Unter-Menü. */
	if (Down & KEY_X) {
		App::AufgabeSelected = false;
		App::Menutyp = App::MenuTyp::UnterMenu;
	}
};
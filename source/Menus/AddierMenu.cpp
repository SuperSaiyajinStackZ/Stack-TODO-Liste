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

#include "AddierMenu.hpp"
#include "App.hpp"
#include "GFX.hpp"
#include "Utils.hpp"

static const std::vector<Structs::ButtonPos> AddierSchaltflaechen = {
	{ 300, 0, 20, 20 }, // Nächste Seite.
	{ 20, 55, 280, 30 }, // Titel.
	{ 20, 120, 280, 60 }, // Beschreibung.
	{ 60, 200, 200, 20 }, // Hinzufügen.

	{ 130, 55, 60, 25 }, // Tag.
	{ 130, 120, 60, 25 }, // Monat.
	{ 130, 185, 60, 25 } // Jahr.
};

static const Structs::ButtonPos MenuVerlassen = { 0, 0, 20, 20 };
extern bool Klick(const Structs::ButtonPos Position, touchPosition Touch);

static void ZeichneErsteSeite() {
	Gui::DrawSprite(GFX::Sprites, sprites_right_idx, 298, 1); // Nächste Seite.

	/* Aufgaben-Titel. */
	Gui::DrawStringCentered(0, 35, 0.5f, TEXT_FARBE, "Aufgaben Titel");
	Gui::Draw_Rect(20, 55, 280, 30, BAR_FARBE);
	Gui::DrawStringCentered(0, 61, 0.5f, TEXT_FARBE, App::Aufgabe.Titel, 260);

	/* Aufgaben-Beschreibung. */
	Gui::DrawStringCentered(0, 100, 0.5f, TEXT_FARBE, "Aufgaben Beschreibung");
	Gui::Draw_Rect(20, 120, 280, 60, BAR_FARBE);
	Gui::DrawString(25, 125, 0.4f, TEXT_FARBE, App::Aufgabe.Beschreibung, 260, 40, nullptr, C2D_WordWrap);

	/* Aufgabe Hinzufügen. */
	Gui::Draw_Rect(60, 200, 200, 20, BAR_FARBE);
	Gui::DrawStringCentered(0, 202, 0.5f, TEXT_FARBE, "Aufgabe Hinzufügen");
};


static void ZeichneZweiteSeite() {
	Gui::DrawStringCentered(0, 35, 0.5f, TEXT_FARBE, "Aufgaben-Tag");
	Gui::Draw_Rect(130, 55, 60, 25, BAR_FARBE);
	Gui::DrawStringCentered(0, 61, 0.5f, TEXT_FARBE, std::to_string(App::Aufgabe.Tag), 260);

	Gui::DrawStringCentered(0, 100, 0.5f, TEXT_FARBE, "Aufgaben-Monat");
	Gui::Draw_Rect(130, 120, 60, 25, BAR_FARBE);
	Gui::DrawStringCentered(0, 126, 0.5f, TEXT_FARBE, std::to_string(App::Aufgabe.Monat), 260);

	Gui::DrawStringCentered(0, 165, 0.5f, TEXT_FARBE, "Aufgaben-Jahr");
	Gui::Draw_Rect(130, 185, 60, 25, BAR_FARBE);
	Gui::DrawStringCentered(0, 191, 0.5f, TEXT_FARBE, std::to_string(App::Aufgabe.Jahr), 260);
};


void AddierMenu::ZeichneMenu() {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Aufgaben-Hinzufüger-Menü"); // Menü Titel.
	Gui::DrawSprite(GFX::Sprites, sprites_back_idx, 2, 1); // Zurück.

	if (App::MenuIndex < 3) ZeichneErsteSeite();
	else ZeichneZweiteSeite();

	/* Zeichne den Stift. */
	Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, AddierSchaltflaechen[App::MenuIndex + 1].x + AddierSchaltflaechen[App::MenuIndex + 1].w - 15, AddierSchaltflaechen[App::MenuIndex + 1].y + AddierSchaltflaechen[App::MenuIndex + 1].h - 15);
};

void AddierMenu::MenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	if (Down & KEY_DOWN) {
		if (App::MenuIndex < 5) App::MenuIndex++;
	}

	if (Down & KEY_RIGHT) {
		if (App::MenuIndex < 3) App::MenuIndex = 3;
	}

	if (Down & KEY_LEFT) {
		if (App::MenuIndex > 2) App::MenuIndex = 0;
	}

	if (Down & KEY_UP) {
		if (App::MenuIndex > 0) App::MenuIndex--;
	}

	/* Touch-Klick Handle. */
	if (Down & KEY_TOUCH) {
		if (App::MenuIndex < 3) { // Erste Seite.
			/* Gehe zur nächsten Seite. */
			if (Klick(AddierSchaltflaechen[0], Touch)) {
				App::MenuIndex = 3;

				/* Gehe zurück zum Unter-Menü. */
			} else if (Klick(MenuVerlassen, Touch)) {
				/* Setze Titel und Beschreibung zurück. */
				App::Aufgabe.Titel = "";
				App::Aufgabe.Beschreibung = "";
				App::Aufgabe.Tag = 1;
				App::Aufgabe.Monat = 1;
				App::Aufgabe.Jahr = 2000;
				App::Aufgabe.ZeitBeinhaltet = false;

				App::MenuIndex = 0;
				App::Menutyp = App::MenuTyp::UnterMenu;

			/* Ändere den Titel der Aufgabe. */
			} else if (Klick(AddierSchaltflaechen[1], Touch)) {
				const std::string Text = Utils::Keyboard(60, "Gebe den Aufgaben-Titel ein.");
				if (Text != "") App::Aufgabe.Titel = Text;

			/* Ändere die Beschreibung der Aufgabe. */
			} else if (Klick(AddierSchaltflaechen[2], Touch)) {
				const std::string Text = Utils::Keyboard(255, "Gebe die Aufgaben-Beschreibung ein.");
				if (Text != "") App::Aufgabe.Beschreibung = Text;

			/* Füge Aufgabe zur TODO-Liste und gehe zurück zum Unter-Menü. */
			} else if (Klick(AddierSchaltflaechen[3], Touch)) {
				/* Überprüfe, ob der Titel bereits existiert. */
				for (size_t Idx = 0; Idx < App::Aufgaben->AufgabenAnzahl(); Idx++) {
					if (App::Aufgabe.Titel == App::Aufgaben->Titel(Idx)) return;
				}

				/* Füge die Aufgabe der Liste hinzu. */
				App::Aufgaben->Addiere(App::Aufgabe);

				/* Setze Titel und Beschreibung zurück. */
				App::Aufgabe.Titel = "";
				App::Aufgabe.Beschreibung = "";
				App::Aufgabe.Tag = 1;
				App::Aufgabe.Monat = 1;
				App::Aufgabe.Jahr = 2000;
				App::Aufgabe.ZeitBeinhaltet = false;

				/* Gehe zurück zum Unter-Menü. */
				App::MenuIndex = 0;
				App::Menutyp = App::MenuTyp::UnterMenu;
			}

		} else { // Zweite Seite.
			/* Gehe Seite zurück. */
			if (Klick(MenuVerlassen, Touch)) {
				App::MenuIndex = 0;

				/* Tag Input. */
			} else if (Klick(AddierSchaltflaechen[4], Touch)) {
				int Res = Utils::Numpad(2, "Gebe den Aufgaben-Tag ein.", App::Aufgabe.Tag);
				if (Res <= Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
					App::Aufgabe.Tag = Res;
					App::Aufgabe.ZeitBeinhaltet = true;
				}

				/* Monat Input. */
			} else if (Klick(AddierSchaltflaechen[5], Touch)) {
				int Res = Utils::Numpad(2, "Gebe den Aufgaben-Monat ein.", App::Aufgabe.Monat);
				if (Res < 13) {
					App::Aufgabe.Monat = Res;

					if (App::Aufgabe.Tag > Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
						App::Aufgabe.Tag = Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr);
					}

					App::Aufgabe.ZeitBeinhaltet = true;
				}

				/* Jahr Input. */
			} else if (Klick(AddierSchaltflaechen[6], Touch)) {
				int Res = Utils::Numpad(4, "Gebe das Aufgaben-Jahr ein.", App::Aufgabe.Jahr);
				if (Res < 2051) {
					App::Aufgabe.Jahr = Res;

					if (App::Aufgabe.Tag > Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
						App::Aufgabe.Tag = Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr);
					}

					App::Aufgabe.ZeitBeinhaltet = true;
				}
			}
		}
	}

	if (Down & KEY_A) {
		std::string Text = "";
		int Res = 0;

		switch(App::MenuIndex) {
			case 0:
				/* Ändere den Titel der Aufgabe. */
				Text = Utils::Keyboard(60, "Gebe den Aufgaben-Titel ein.");
				if (Text != "") App::Aufgabe.Titel = Text;
				break;

			case 1:
				/* Ändere die Beschreibung der Aufgabe. */
				Text = Utils::Keyboard(255, "Gebe die Aufgaben-Beschreibung ein.");
				if (Text != "") App::Aufgabe.Beschreibung = Text;
				break;

			case 2:
				/* Überprüfe, ob der Titel bereits existiert. */
				for (size_t Idx = 0; Idx < App::Aufgaben->AufgabenAnzahl(); Idx++) {
					if (App::Aufgabe.Titel == App::Aufgaben->Titel(Idx)) return;
				}

				/* Füge Aufgabe zur TODO-Liste und gehe zurück zum Unter-Menü. */
				App::Aufgaben->Addiere(App::Aufgabe);

				/* Setze Titel und Beschreibung zurück. */
				App::Aufgabe.Titel = "";
				App::Aufgabe.Beschreibung = "";
				App::Aufgabe.Tag = 1;
				App::Aufgabe.Monat = 1;
				App::Aufgabe.Jahr = 2000;
				App::Aufgabe.ZeitBeinhaltet = false;

				/* Gehe zurück zum Unter-Menü. */
				App::MenuIndex = 0;
				App::Menutyp = App::MenuTyp::UnterMenu;
				break;

			case 3:
				/* Tag Input. */
				Res = Utils::Numpad(2, "Gebe den Aufgaben-Tag ein.", App::Aufgabe.Tag);
				if (Res <= Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
					App::Aufgabe.Tag = Res;
					App::Aufgabe.ZeitBeinhaltet = true;
				}
				break;

			case 4:
				/* Monat Input. */
				Res = Utils::Numpad(2, "Gebe den Aufgaben-Monat ein.", App::Aufgabe.Monat);
				if (Res < 13) {
					App::Aufgabe.Monat = Res;

					if (App::Aufgabe.Tag > Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
						App::Aufgabe.Tag = Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr);
					}

					App::Aufgabe.ZeitBeinhaltet = true;
				}
				break;

			case 5:
				/* Jahr Input. */
				Res = Utils::Numpad(4, "Gebe das Aufgaben-Jahr ein.", App::Aufgabe.Jahr);
				if (Res < 2051) {
					App::Aufgabe.Jahr = Res;

					if (App::Aufgabe.Tag > Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr)) {
						App::Aufgabe.Tag = Utils::MaximaleTage(App::Aufgabe.Monat, App::Aufgabe.Jahr);
					}

					App::Aufgabe.ZeitBeinhaltet = true;
				}
				break;
		}
	}

	/* Gehe zurück zum Unter-Menü. */
	if (Down & KEY_B) {
		/* Setze Titel und Beschreibung zurück. */
		App::Aufgabe.Titel = "";
		App::Aufgabe.Beschreibung = "";
		App::Aufgabe.Tag = 1;
		App::Aufgabe.Monat = 1;
		App::Aufgabe.Jahr = 2000;
		App::Aufgabe.ZeitBeinhaltet = false;

		App::MenuIndex = 0;
		App::Menutyp = App::MenuTyp::UnterMenu;
	}
};
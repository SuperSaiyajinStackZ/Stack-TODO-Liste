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

extern bool Klick(const Structs::ButtonPos Position, touchPosition Touch), Verlassen;

/* Haupt-Zeichnungs Teil. */
void Menu::Draw(void) const {
	this->TODOListe(); // Zeichne den oberen Bildschirm / die TODO Liste.

	GFX::DrawBasis(false);
	switch(this->Menutyp) {
		case MenuTyp::Liste:
		case MenuTyp::UnterMenu:
			this->UnterMenu();
			break;

		case MenuTyp::Addieren:
			this->AddierMenu();
			break;

		case MenuTyp::Mitwirkende:
			this->MitwirkendeMenu();
			break;
	}
};

/* Haupt-Logik's Teil. */
void Menu::Logic(u32 Down, u32 Held, touchPosition Touch) {
	switch(this->Menutyp) {
		case MenuTyp::Liste:
			this->ListenLogik(Down, Held, Touch);
			break;

		case MenuTyp::UnterMenu:
			this->UnterMenuLogik(Down, Held, Touch);
			break;

		case MenuTyp::Addieren:
			this->AddierLogik(Down, Held, Touch);
			break;

		case MenuTyp::Mitwirkende:
			this->MitwirkendeLogik(Down, Held, Touch);
			break;
	}
};


/*
	TODO-Listen Teil.

	void Menu::TODOListe(void) const: Zeichnet die TODO-Liste auf dem oberen Bildschirm.
	void Menu::AufgabeEntfernen(): Entfernt die ausgewählte Aufgabe.
	void Menu::ListenLogik(uint32_t Down, uint32_t Held, touchPosition Touch): Die Input Logik.
*/
void Menu::TODOListe(void) const {
	GFX::DrawBasis(true);
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Stack-TODO-Liste");
	Gui::DrawString(395, 1, 0.55f, TEXT_FARBE, "v1.0.0", 0, 0, nullptr, C2D_AlignRight);

	/* Zeichne die Top Aufgaben-Liste. */
	if (this->Aufgaben->AufgabenAnzahl() > 0) {
		if (this->Index < 2) {
			GFX::AufgabenBlock(this->Aufgaben->Aufgabe(0), this->TODOFlaechen[0].y);
			if (this->Aufgaben->AufgabenAnzahl() > 1) GFX::AufgabenBlock(this->Aufgaben->Aufgabe(1), this->TODOFlaechen[1].y);

		} else {
			GFX::AufgabenBlock(this->Aufgaben->Aufgabe(this->Index - 1), this->TODOFlaechen[0].y);
			GFX::AufgabenBlock(this->Aufgaben->Aufgabe(this->Index), this->TODOFlaechen[1].y);
		}

		/* Listen-Modus -> Zeichne den Stift auf den oberen Bildschirm. */
		if (this->Menutyp == MenuTyp::Liste) {
			if (!this->AufgabeSelected) Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, this->TODOFlaechen[2].x, this->TODOFlaechen[2].y + (this->Index > 0 ? 100 : 0));
			else { // Falls die Aufgabe ausgewählt wurde.
				switch(this->AufgabenIndex) {
					case 0:
						Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, this->TODOFlaechen[3].x, this->TODOFlaechen[3].y + (this->Index > 0 ? 100 : 0));
						break;

					case 1:
						Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, this->TODOFlaechen[4].x, this->TODOFlaechen[4].y + (this->Index > 0 ? 100 : 0));
						break;
				}
			}
		}
	}
};

/* Entfernt die ausgewählte Aufgabe. */
void Menu::AufgabeEntfernen() {
	if (this->Aufgaben->AufgabenAnzahl() > 0) {
		this->AufgabeSelected = false;
		this->Aufgaben->Entferne(this->Index);

		if (this->Aufgaben->AufgabenAnzahl() > 0) {
			/* Aktualisiere Aufgaben-Index, falls notwendig. */
			if (this->Index > this->Aufgaben->AufgabenAnzahl() - 1) this->Index = this->Aufgaben->AufgabenAnzahl() - 1;

			/* Falls 0 Aufgaben, gehe zum Unter-Menü. */
		} else {
			this->Menutyp = MenuTyp::UnterMenu;
		}
	}
};

/* TODO-Listen Logik. */
void Menu::ListenLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	if (Down & KEY_DOWN) {
		if (!this->AufgabeSelected) { // Listen Index.
			if (this->Index < this->Aufgaben->AufgabenAnzahl() - 1) this->Index++;

		} else { // Aufgaben Index.
			if (this->AufgabenIndex < 1) this->AufgabenIndex++;
		}
	}


	if (Down & KEY_UP) {
		if (!this->AufgabeSelected) { // Listen Index.
			if (this->Index > 0) this->Index--;

		} else { // Aufgaben Index.
			if (this->AufgabenIndex > 0) this->AufgabenIndex--;
		}
	}

	if (Down & KEY_A) {
		if (!this->AufgabeSelected) { // Listen Index.
			this->AufgabeSelected = true;

		} else { // Aufgaben Index.
			switch(this->AufgabenIndex) {
				case 0: // Aufgabe Entfernen.
					this->AufgabeEntfernen();
					break;

				case 1: // Erledigt umschalten.
					this->Aufgaben->Erledigt(this->Index, !this->Aufgaben->Erledigt(this->Index));
					break;
			}
		}
	}

	this->ListMenuLogik(Down, Held, Touch);

	/* Falls die Aufgabe ausgewählt worden ist, gehe zurück zum nicht ausgewählten Modus. */
	if (Down & KEY_B) {
		if (this->AufgabeSelected) this->AufgabeSelected = false;
	}

	/* Gehe zum Unter-Menü. */
	if (Down & KEY_X) {
		this->AufgabeSelected = false;
		this->Menutyp = MenuTyp::UnterMenu;
	}
};

/* Dies wird geteilt mit der TODO-Listen Logik UND der Unter-Menü Logik. */
void Menu::ListMenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	/* Touch-Klick Handle. */
	if (Down & KEY_TOUCH) {
		/* Wechsel zwischen Liste und Unter-Menü. */
		if (Klick(this->MenuVerlassen, Touch)) {
			if (this->Aufgaben->AufgabenAnzahl() > 0) this->Menutyp = (this->Menutyp == MenuTyp::Liste ? MenuTyp::UnterMenu : MenuTyp::Liste);

		/* Aufgabe Hinzufügen. */
		} else if (Klick(this->UnterMenuSchaltflaechen[0], Touch)) {
			this->Menutyp = MenuTyp::Addieren;

		/* Mitwirkende / Credits Ansehen. */
		} else if (Klick(this->UnterMenuSchaltflaechen[1], Touch)) {
			this->Menutyp = MenuTyp::Mitwirkende;

		/* Aufgabenliste Leeren. */
		} else if (Klick(this->UnterMenuSchaltflaechen[2], Touch)) {
			this->Leeren();
			this->Menutyp = MenuTyp::UnterMenu;
		}
	}

	if (Down & KEY_START) Verlassen = true;
};



/*
	Unter-Menü Teil.

	void Menu::UnterMenue(void) const: Zeichnet das Unter-Menü auf dem unteren Bildschirm.
	void Menu::Leeren(): Leert die komplette TODO Liste.
	void Menu::UnterMenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch): Die Input Logik.
*/
void Menu::UnterMenu(void) const {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Unter-Menü"); // Menü Titel.
	if (this->Aufgaben->AufgabenAnzahl() > 0) {
		Gui::DrawSprite(GFX::Sprites, (this->Menutyp == MenuTyp::Liste ? sprites_down_idx : sprites_up_idx), 2, 1); // Hoch / Runter Pfeil.
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
	if (this->Menutyp == MenuTyp::UnterMenu) Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, this->UnterMenuSchaltflaechen[this->UnterMenuIndex].x + 80, this->UnterMenuSchaltflaechen[this->UnterMenuIndex].y + 30);
};

/* Leert die TODO-Liste komplett. */
void Menu::Leeren() {
	this->Index = 0;

	while(this->Aufgaben->AufgabenAnzahl() > 0) { this->Aufgaben->Entferne(0); };
};

/* Unter-Menü Logik. */
void Menu::UnterMenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch) {
	if (Down & KEY_DOWN) {
		if (this->UnterMenuIndex == 0) this->UnterMenuIndex = 2;
	}

	if (Down & KEY_UP) {
		if (this->UnterMenuIndex > 1) this->UnterMenuIndex -= 2;
	}

	if (Down & KEY_RIGHT) {
		if (this->UnterMenuIndex == 0) this->UnterMenuIndex++;
	}

	if (Down & KEY_LEFT) {
		if (this->UnterMenuIndex == 1) this->UnterMenuIndex--;
	}

	this->ListMenuLogik(Down, Held, Touch);

	if (Down & KEY_A) {
		switch(this->UnterMenuIndex) {
			case 0: // Aufgabe Hinzufügen.
				this->Menutyp = MenuTyp::Addieren;
				break;

			case 1: // Mitwirkende / Credits Ansehen.
				this->Menutyp = MenuTyp::Mitwirkende;
				break;

			case 2: // Aufgabenliste Leeren.
				this->Leeren();
				break;
		}
	}

	if (Down & KEY_X) {
		if (this->Aufgaben->AufgabenAnzahl() > 0) this->Menutyp = MenuTyp::Liste; // Wechsel zum TODO-Listen Modus.
	}
};



/*
	Hinzufüger-Menü Teil.

	void Menu::AddierMenu(void) const: Zeichnet das Hinzufüger-Menü auf dem unteren Bildschirm.
	void Menu::AddierLogik(uint32_t Down, uint32_t Held, touchPosition Touch): Die Input Logik.
*/
void Menu::AddierMenu(void) const {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Aufgaben-Hinzufüger-Menü"); // Menü Titel.
	Gui::DrawSprite(GFX::Sprites, sprites_back_idx, 2, 1); // Zurück.

	/* Aufgaben-Titel. */
	Gui::DrawStringCentered(0, 35, 0.5f, TEXT_FARBE, "Aufgaben Titel");
	Gui::Draw_Rect(20, 55, 280, 30, BAR_FARBE);
	Gui::DrawStringCentered(0, 61, 0.5f, TEXT_FARBE, this->Aufgabe.Titel, 260);

	/* Aufgaben-Beschreibung. */
	Gui::DrawStringCentered(0, 100, 0.5f, TEXT_FARBE, "Aufgaben Beschreibung");
	Gui::Draw_Rect(20, 120, 280, 60, BAR_FARBE);
	Gui::DrawString(25, 125, 0.4f, TEXT_FARBE, this->Aufgabe.Beschreibung, 260, 40, nullptr, C2D_WordWrap);

	/* Aufgabe Hinzufügen. */
	Gui::Draw_Rect(60, 200, 200, 20, BAR_FARBE);
	Gui::DrawStringCentered(0, 202, 0.5f, TEXT_FARBE, "Aufgabe Hinzufügen");

	/* Zeichne den Stift. */
	Gui::DrawSprite(GFX::Sprites, sprites_stift_idx, this->AddierSchaltflaechen[this->UnterMenuIndex].x + this->AddierSchaltflaechen[this->UnterMenuIndex].w - 15, this->AddierSchaltflaechen[this->UnterMenuIndex].y + this->AddierSchaltflaechen[this->UnterMenuIndex].h - 15);
};

/* Hinzufüger-Menü Logik. */
void Menu::AddierLogik(u32 Down, u32 Held, touchPosition Touch) {
	if (Down & KEY_DOWN) {
		if (this->UnterMenuIndex < 2) this->UnterMenuIndex++;
	}

	if (Down & KEY_UP) {
		if (this->UnterMenuIndex > 0) this->UnterMenuIndex--;
	}

	/* Touch-Klick Handle. */
	if (Down & KEY_TOUCH) {
		/* Gehe zurück zum Unter-Menü. */
		if (Klick(this->MenuVerlassen, Touch)) {
			/* Setze Titel und Beschreibung zurück. */
			this->Aufgabe.Titel = "";
			this->Aufgabe.Beschreibung = "";
			this->UnterMenuIndex = 0;
			this->Menutyp = MenuTyp::UnterMenu;

		/* Ändere den Titel der Aufgabe. */
		} else if (Klick(this->AddierSchaltflaechen[0], Touch)) {
			const std::string Text = GFX::Keyboard(60, "Gebe den Aufgaben-Titel ein.");
			if (Text != "") this->Aufgabe.Titel = Text;

		/* Ändere die Beschreibung der Aufgabe. */
		} else if (Klick(this->AddierSchaltflaechen[1], Touch)) {
			const std::string Text = GFX::Keyboard(255, "Gebe die Aufgaben-Beschreibung ein.");
			if (Text != "") this->Aufgabe.Beschreibung = Text;

		/* Füge Aufgabe zur TODO-Liste und gehe zurück zum Unter-Menü. */
		} else if (Klick(this->AddierSchaltflaechen[2], Touch)) {
			/* Überprüfe, ob der Titel bereits existiert. */
			for (size_t Idx = 0; Idx < this->Aufgaben->AufgabenAnzahl(); Idx++) {
				if (this->Aufgabe.Titel == this->Aufgaben->Titel(Idx)) return;
			}

			/* Füge die Aufgabe der Liste hinzu. */
			this->Aufgaben->Addiere(this->Aufgabe);

			/* Setze Titel und Beschreibung zurück. */
			this->Aufgabe.Titel = "";
			this->Aufgabe.Beschreibung = "";

			/* Gehe zurück zum Unter-Menü. */
			this->UnterMenuIndex = 0;
			this->Menutyp = MenuTyp::UnterMenu;
		}
	}


	if (Down & KEY_A) {
		std::string Text = "";

		switch(this->UnterMenuIndex) {
			case 0:
				/* Ändere den Titel der Aufgabe. */
				Text = GFX::Keyboard(60, "Gebe den Aufgaben-Titel ein.");
				if (Text != "") this->Aufgabe.Titel = Text;
				break;

			case 1:
				/* Ändere die Beschreibung der Aufgabe. */
				Text = GFX::Keyboard(255, "Gebe die Aufgaben-Beschreibung ein.");
				if (Text != "") this->Aufgabe.Beschreibung = Text;
				break;

			case 2:
				/* Überprüfe, ob der Titel bereits existiert. */
				for (size_t Idx = 0; Idx < this->Aufgaben->AufgabenAnzahl(); Idx++) {
					if (this->Aufgabe.Titel == this->Aufgaben->Titel(Idx)) return;
				}

				/* Füge Aufgabe zur TODO-Liste und gehe zurück zum Unter-Menü. */
				this->Aufgaben->Addiere(this->Aufgabe);

				/* Setze Titel und Beschreibung zurück. */
				this->Aufgabe.Titel = "";
				this->Aufgabe.Beschreibung = "";

				/* Gehe zurück zum Unter-Menü. */
				this->UnterMenuIndex = 0;
				this->Menutyp = MenuTyp::UnterMenu;
				break;
		}
	}

	/* Gehe zurück zum Unter-Menü. */
	if (Down & KEY_B) {
		/* Setze Titel und Beschreibung zurück. */
		this->Aufgabe.Titel = "";
		this->Aufgabe.Beschreibung = "";
		this->UnterMenuIndex = 0;
		this->Menutyp = MenuTyp::UnterMenu;
	}
};



/*
	Mitwirkenden Teil.

	void Menu::MitwirkendeMenu(void) const: Zeichnet das Mitwirkenden-Menü auf dem unteren Bildschirm.
	void Menu::MitwirkendeLogik(uint32_t Down, uint32_t Held, touchPosition Touch): Die Input Logik.
*/
void Menu::MitwirkendeMenu(void) const {
	Gui::DrawStringCentered(0, 1, 0.55f, TEXT_FARBE, "Mitwirkende-Menü"); // Menü-Titel.
	Gui::DrawSprite(GFX::Sprites, sprites_back_idx, 2, 1); // Zurück.

	/* Mitwirkenden Text. */
	Gui::DrawStringCentered(0, 35, 0.6f, TEXT_FARBE, "Entwickelt von SuperSaiyajinStackZ.");
	Gui::DrawStringCentered(0, 60, 0.45f, TEXT_FARBE, "Universal-Team: Universal-Core.");

	/* Bild von StackZ. */
	Gui::DrawSprite(GFX::Sprites, sprites_stackz_idx, 100, 100);
};

/* Mitwirkenden Menü Logik. */
void Menu::MitwirkendeLogik(u32 Down, u32 Held, touchPosition Touch) {
	if ((Down & KEY_B) || (Down & KEY_TOUCH && Klick(this->MenuVerlassen, Touch))) this->Menutyp = MenuTyp::UnterMenu; // Gehe zurück zum Unter-Menü.
};
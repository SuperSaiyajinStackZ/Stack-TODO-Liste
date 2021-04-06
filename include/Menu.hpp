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

#ifndef _STACK_TODO_LISTE_MENU_HPP
#define _STACK_TODO_LISTE_MENU_HPP

#include "Core.hpp"
#include "screen.hpp"
#include "screenCommon.hpp"

class Menu : public Screen {
public:
	Menu() { // Lade die Liste beim betreten.
		this->Aufgaben = std::make_unique<AufgabenListeCore>();
		if (this->Aufgaben->AufgabenAnzahl() > 0) this->Menutyp = MenuTyp::Liste;
	};
	~Menu() { this->Aufgaben->ListeSpeichern(); }; // Speichere die Liste beim verlassen.

	void Draw(void) const override;
	void Logic(u32 Down, u32 Held, touchPosition Touch) override;
private:
	/* Die Menü-Typen. */
	enum class MenuTyp : uint8_t { Liste, UnterMenu, Addieren, Mitwirkende };
	MenuTyp Menutyp = MenuTyp::UnterMenu;

	/* Die Temporäre Aufgabe und alle Aufgaben. */
	AufgabenListe Aufgabe;
	std::unique_ptr<AufgabenListeCore> Aufgaben = nullptr;

	/* Ein paar andere Variablen. */
	bool AufgabeSelected = false;
	size_t Index = 0, AufgabenIndex = 0, UnterMenuIndex = 0;
	const Structs::ButtonPos MenuVerlassen = { 0, 0, 20, 20 };

	/* Dies wird geteilt mit der TODO-Listen Logik UND der Unter-Menü Logik. */
	void ListMenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch);

	/* Listen Logik. */
	void TODOListe(void) const;
	void AufgabeEntfernen();
	void ListenLogik(uint32_t Down, uint32_t Held, touchPosition Touch);
	const std::vector<Structs::ButtonPos> TODOFlaechen = {
		/* TODO-Listen Boxen. */
		{ 20, 40, BOX_BREITE, BOX_HOEHE },
		{ 20, 140, BOX_BREITE, BOX_HOEHE },

		{ 365, 60, 15, 15 }, // Ausgewählte Box.
		{ 365, 40, 15, 15 }, // Minus.
		{ 365, 80, 15, 15 }  // Markierungs-Box.
	};

	/* Unter-Menü Logik. */
	void UnterMenu(void) const;
	void Leeren();
	void UnterMenuLogik(uint32_t Down, uint32_t Held, touchPosition Touch);
	const std::vector<Structs::ButtonPos> UnterMenuSchaltflaechen = {
		{ 30, 40, 120, 70 }, // Aufgabe Hinzufügen.
		{ 170, 40, 120, 70 }, // Mitwirkende Ansehen.
		{ 30, 130, 120, 70 }  // Aufgabenliste Leeren.
	};

	/* Addier Menü. */
	void AddierMenu(void) const;
	void AddierLogik(u32 Down, u32 Held, touchPosition Touch);
	const std::vector<Structs::ButtonPos> AddierSchaltflaechen = {
		{ 20, 55, 280, 30 }, // Titel.
		{ 20, 120, 280, 60 }, // Beschreibung.
		{ 60, 200, 200, 20 } // Hinzufügen.
	};

	/* Mitwirkende Menü. */
	void MitwirkendeMenu(void) const;
	void MitwirkendeLogik(u32 Down, u32 Held, touchPosition Touch);
};

#endif
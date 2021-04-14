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

#ifndef _STACK_TODO_LISTE_APP_HPP
#define _STACK_TODO_LISTE_APP_HPP

#include "Core.hpp"
#include <memory>
#include <string>

namespace App {
	enum class MenuTyp : uint8_t { Liste, UnterMenu, Addieren, Mitwirkende };

	/* Variablen. */
	extern MenuTyp Menutyp;
	extern AufgabenListe Aufgabe;
	extern std::unique_ptr<AufgabenListeCore> Aufgaben;
	extern size_t Index, AufgabenIndex, MenuIndex;
	extern bool AufgabeSelected, Verlassen;

	/* Funktionen. */
	void Initialisieren();
	int HauptLogik();
	void Beenden();
	void Zeichnung();
	void Logik();
};

#endif
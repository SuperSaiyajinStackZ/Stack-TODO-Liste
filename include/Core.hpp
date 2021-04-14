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

#ifndef _STACK_TODO_LISTE_CORE_HPP
#define _STACK_TODO_LISTE_CORE_HPP

#include "JSON.hpp"
#include <string>

#define _JSON_PFAD "sdmc:/3ds/StackTODOListe/AufgabenListe.json"

/*
	Aufgaben-Liste Struktur.
*/
struct AufgabenListe {
	std::string Titel = "";
	std::string Beschreibung = "";
	bool Erledigt = false;
	uint8_t Tag = 1;
	uint8_t Monat = 1;
	uint16_t Jahr = 2000; // 65535 / 65536 (uint16_t) sollte genug sein.
	bool ZeitBeinhaltet = false;
};

class AufgabenListeCore {
public:
	AufgabenListeCore(const std::string &Liste = _JSON_PFAD) : ListenDatei(Liste) { this->LadeListe(this->ListenDatei); };

	void LadeListe(const std::string &Liste);
	void InitialisiereListe(const std::string &Liste);

	/* Wiedergebe den Inhalt der Aufgaben. */
	std::string Titel(const size_t Index) const;
	std::string Beschreibung(const size_t Index) const;
	bool Erledigt(const size_t Index) const;
	uint8_t Tag(const size_t Index) const;
	uint8_t Monat(const size_t Index) const;
	uint16_t Jahr(const size_t Index) const;
	AufgabenListe Aufgabe(const size_t Index) const;

	/* Utilities */
	void Erledigt(const size_t Index, const bool IstErledigt);
	void Entferne(const size_t Index);
	void Addiere(const AufgabenListe &Aufgabe);
	void ListeSpeichern();
	size_t AufgabenAnzahl() const;
private:
	std::string ListenDatei = "";
	nlohmann::json AufgabenJSON = nullptr;
	std::vector<AufgabenListe> Aufgaben = { };
	bool ListeGut = false;
};

#endif
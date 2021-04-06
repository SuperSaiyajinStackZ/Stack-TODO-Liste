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

#include "Core.hpp"
#include <unistd.h> // Für den Existenz Check der JSON Datei.

/*
	Lädt die Aufgaben-Liste von einer Datei.
*/
void AufgabenListeCore::LadeListe(const std::string &Liste) {
	this->ListenDatei = Liste;
	this->Aufgaben.clear(); // Leere die Liste.

	/* Überprüfe, ob die Datei existiert. */
	if (access(Liste.c_str(), F_OK) != 0) this->InitialisiereListe(Liste);

	FILE *Datei = fopen(Liste.c_str(), "rt");
	if (Datei) {
		this->AufgabenJSON = nlohmann::json::parse(Datei, nullptr, false);
		fclose(Datei);
	}

	if (this->AufgabenJSON.is_discarded()) {
		this->ListeGut = false;
		this->AufgabenJSON = { };
		return;
	}

	/* Initialisiere die eigentliche Aufgaben-Liste. */
	for(auto It = this->AufgabenJSON.begin(); It != this->AufgabenJSON.end(); ++It) {
		AufgabenListe Aufgabe = { "", "", false };

		Aufgabe.Titel = It.key();
		if (this->AufgabenJSON[It.key()].contains("Beschreibung") && this->AufgabenJSON[It.key()]["Beschreibung"].is_string()) {
			Aufgabe.Beschreibung = this->AufgabenJSON[It.key()]["Beschreibung"];
		}

		if (this->AufgabenJSON[It.key()].contains("Erledigt") && this->AufgabenJSON[It.key()]["Erledigt"].is_boolean()) {
			Aufgabe.Erledigt = this->AufgabenJSON[It.key()]["Erledigt"];
		}

		this->Aufgaben.push_back(Aufgabe); // Füge die Aufgabe zu den Aufgaben hinzu.
	}

	this->ListeGut = true;
};

/*
	Initialisiert die Liste mit einer gültigen JSON Datei.

	const std::string &Liste: Der Pfad zur JSON Liste.
*/
void AufgabenListeCore::InitialisiereListe(const std::string &Liste) {
	FILE *Datei = fopen(Liste.c_str(), "w");
	char Temp[2] = { '{', '}' };
	fwrite(Temp, sizeof(Temp), 1, Datei);
	fclose(Datei);
};

/*
	Erhalte den Titel einer Aufgabe.

	const size_t Index: Der Index der Aufgabe.
*/
std::string AufgabenListeCore::Titel(const size_t Index) const {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) return this->Aufgaben[Index].Titel;
	return "";
};

/*
	Erhalte die Beschreibung einer Aufgabe.

	const size_t Index: Der Index der Aufgabe.
*/
std::string AufgabenListeCore::Beschreibung(const size_t Index) const {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) return this->Aufgaben[Index].Beschreibung;
	return "";
};


/*
	Erhalte den Erledigt Status einer Aufgabe.

	const size_t Index: Der Index der Aufgabe.
*/
bool AufgabenListeCore::Erledigt(const size_t Index) const {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) return this->Aufgaben[Index].Erledigt;
	return false;
};


/*
	Erhalte eine komplette Aufgabe.

	const size_t Index: Der Index der Aufgabe.
*/
AufgabenListe AufgabenListeCore::Aufgabe(const size_t Index) const {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) return this->Aufgaben[Index];
	return { "", "", false };
};

/*
	Setze den Erledigt Status einer Aufgabe.

	const size_t Index: Der Index der Aufgabe.
	const bool IstErledigt: Ob Erledigt (true) oder nicht (false).
*/
void AufgabenListeCore::Erledigt(const size_t Index, const bool IstErledigt) {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) {
		this->Aufgaben[Index].Erledigt = IstErledigt;

		if (!this->AufgabenJSON.is_discarded()) this->AufgabenJSON[this->Aufgaben[Index].Titel]["Erledigt"] = IstErledigt;
	}
};

/*
	Entferne eine Aufgabe von der Liste.

	const size_t Index: Der Index der Aufgabe.
*/
void AufgabenListeCore::Entferne(const size_t Index) {
	if (Index < this->AufgabenAnzahl() && this->ListeGut) {
		this->AufgabenJSON.erase(this->Aufgaben[Index].Titel); // Entferne von der JSON.
		this->Aufgaben.erase(this->Aufgaben.begin() + Index); // Entferne von der Liste.
	}
};

/*
	Addiert eine Aufgabe zu der Liste.

	const AufgabenListe &Aufgabe: Die Aufgabe, welche Hinzugefügt werden soll.
*/
void AufgabenListeCore::Addiere(const AufgabenListe &Aufgabe) {
	if (this->ListeGut) {
		this->Aufgaben.push_back(Aufgabe);

		nlohmann::json Objekt = {{ "Beschreibung", Aufgabe.Beschreibung }, { "Erledigt", Aufgabe.Erledigt }};
		this->AufgabenJSON.push_back({ Aufgabe.Titel, Objekt });
	}
};

/*
	Speichert die Liste zur Datei.
*/
void AufgabenListeCore::ListeSpeichern() {
	if (this->ListeGut && !this->AufgabenJSON.is_discarded()) {
		FILE *Datei = fopen(this->ListenDatei.c_str(), "wb");
		fwrite(this->AufgabenJSON.dump(1, '\t').c_str(), 1, this->AufgabenJSON.dump(1, '\t').size(), Datei);
		fclose(Datei);
	}
};

/*
	Wiedergibt die Anzahl der Aufgaben.
*/
size_t AufgabenListeCore::AufgabenAnzahl() const {
	if (this->ListeGut && !this->Aufgaben.empty()) return this->Aufgaben.size();
	return 0;
};
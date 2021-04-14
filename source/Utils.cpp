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
#include "Utils.hpp"
#include <3ds.h>

time_t Utils::Unixzeit = time(nullptr);

/* Monats-Namen. */
static std::string Monate[] = {
	"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"
};

/*
	Wiedergebe die aktuelle Zeit und das Datum als String wieder. Das Format ist:

	Tag, Monat Jahr
	Stunde:Minute
*/
const std::string Utils::DatumZeit() {
	Utils::Unixzeit = time(nullptr);
	struct tm *Zeitstrukt = gmtime((const time_t *)&Utils::Unixzeit);
	char Result[100];

	/*
		Tag, Monat Jahr
		Stunde:Minute
	*/
	snprintf(Result, sizeof(Result), "%02i, %s %i\n%02i:%02i",
			Zeitstrukt->tm_mday, Monate[Zeitstrukt->tm_mon].c_str(), Zeitstrukt->tm_year + 1900, Zeitstrukt->tm_hour, Zeitstrukt->tm_min
	);

	return Result;
};

/*
	Wiedergibt die Maximale Anzahl der Tagen eines bestimmten Jahres und Monats.

	const uint8_t Monat: Der Monat.
	const uint16_t Jahr: Das Jahr.
*/
uint8_t Utils::MaximaleTage(const uint8_t Monat, const uint16_t Jahr) {
	switch(Monat) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;

		case 4:
		case 6:
		case 9:
		case 11:
			return 30;

		case 2:
			return (Jahr % 4) ? 28 : 29; // Februar ist ein spezieller Monat, lol.

		default:
			return 31;
	}
};

/*
	Öffnet das System Keyboard, damit etwas eingegeben werden kann.

	const size_t Laenge: Die Länge der Zeichen, die eingegeben werden können.
	const std::string &Text: Der Hilfe-Text welcher angezeigt werden soll.
*/
std::string Utils::Keyboard(const size_t Laenge, const std::string &Text) {
	C3D_FrameEnd(0);

	SwkbdState Status;
	swkbdInit(&Status, SWKBD_TYPE_NORMAL, 2, Laenge);
	char Temp[Laenge + 1] = { 0 };
	swkbdSetHintText(&Status, Text.c_str());
	swkbdSetValidation(&Status, SWKBD_NOTBLANK_NOTEMPTY, SWKBD_FILTER_PROFANITY, 0);

	SwkbdButton Result = swkbdInputText(&Status, Temp, sizeof(Temp));
	Temp[Laenge] = '\0';

	return (Result == SWKBD_BUTTON_CONFIRM ? Temp : "");
};

/*
	Öffnet das System Keyboard, damit etwas eingegeben werden kann.

	const size_t Laenge: Die Länge der Zeichen, die eingegeben werden können.
	const std::string &Text: Der Hilfe-Text welcher angezeigt werden soll.
	int AlterWert: Der Alte wert, welcher wiedergeben wird, falls abgebrochen wird.
*/
int Utils::Numpad(const size_t Laenge, const std::string &Text, int AlterWert) {
	C3D_FrameEnd(0);

	SwkbdState Status;
	swkbdInit(&Status, SWKBD_TYPE_NUMPAD, 2, Laenge);
	char Temp[Laenge + 1] = { 0 };
	swkbdSetHintText(&Status, Text.c_str());

	SwkbdButton Result = swkbdInputText(&Status, Temp, sizeof(Temp));
	Temp[Laenge] = '\0';

	return (Result == SWKBD_BUTTON_CONFIRM ? std::atoi(Temp) : AlterWert);
};
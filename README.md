# Stack-TODO-Liste

German: Ein TODO-Listen Tool für den Nintendo 3DS.

English: A TODO-List Tool for the Nintendo 3DS.

**Den Pfad der TODO-Liste findest du unter `sdmc:/3ds/StackTODOListe/AufgabenListe.json`.**

## Screenshots
**Screenshots zu Stack-TODO-Liste findest du hier.**

![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Aufgaben-Hinzufüger-Menü-1.png)
![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Aufgaben-Hinzufüger-Menü-2.png)
![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Haupt-Screen.png)
![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Mitwirkenden-Menü.png)

## Features
- [x] Verwalte deine TODO's und Markiere deine Aufgaben als Erledigt, Unerledigt; Setze ein Datum fest zur Übersicht, wann die Aufgabe erledigt werden soll oder entferne sie aus der TODO-Liste falls diese nicht mehr benötigt werden im TODO-Listen Modus.
- [x] Füge neue TODO's hinzu über `Aufgabe Hinzufügen`. Dort kannst du den Titel, die Beschreibung und das Datum der Aufgabe setzen.
- [x] Siehe die Mitwirkenden an über `Mitwirkende Ansehen`.
- [x] Leere die komplette TODO-Liste über `Aufgabenliste Leeren`.

Die Liste wird automatisch beim verlassen der Anwendung gespeichert.

## TODO-Listen Format
Die TODO-Liste wird im JSON format verwaltet.

Hier ist ein Beispiel:
```json
{
	"Test": {
		"Beschreibung": "Die Beschreibung / The Description",
		"Erledigt": false,
		"Jahr": 2000,
		"Monat": 1,
		"Tag": 1,
		"Zeitbeinhaltet": true
	}
}
```

Jede Aufgabe enthält folgende Dinge:
- [x] Beschreibung: Die Beschreibung, welche als zweiter Text angezeigt wird.
- [x] Erledigt: Ob Erledigt (true) oder Unerledigt (false).
- [x] Tag: Der Tag an der die Aufgabe spätestens erledigt werden soll (Optional).
- [x] Monat: Der Monat an der die Aufgabe spätestens erledigt werden soll (Optional).
- [x] Jahr: Das Jahr an der die Aufgabe spätestens erledigt werden soll (Optional).
- [x] Zeitbeinhaltet: Ob die Zeit beinhaltet wurde oder nicht. Dies wird verwendet, um das Datum über der Aufgaben-Box anzuzeigen.

## Credits
[SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Haupt-Entwickler von Stack-TODO-Liste.

[Universal-Team](https://github.com/Universal-Team): Für Universal-Core.
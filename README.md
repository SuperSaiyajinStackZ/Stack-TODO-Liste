# Stack-TODO-Liste

German: Ein TODO-Listen Tool für den Nintendo 3DS.

English: A TODO-List Tool for the Nintendo 3DS.

**Der Pfad der TODO-Liste findest du unter `sdmc:/3ds/StackTODOListe/AufgabenListe.json`.**

## Screenshots
**Screenshots zu Stack-TODO-Liste findest du hier.**

![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Aufgaben-Hinzufüger-Menü.png)
![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Haupt-Screen.png)
![](https://github.com/SuperSaiyajinStackZ/Stack-TODO-Liste/blob/main/screenshots/Mitwirkenden-Menü.png)

## Features
- [x] Verwalte deine TODO's und Markiere deine Aufgaben als Erledigt, Unerledigt oder entferne sie aus der TODO-Liste falls diese nicht mehr benötigt werden im TODO-Listen Modus.
- [x] Füge neue TODO's hinzu über `Aufgabe Hinzufügen`. Dort kannst du den Titel und die Beschreibung der Aufgabe setzen.
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
		"Erledigt": false
	}
}
```

Jede Aufgabe enthält folgende Dinge:
- [x] Beschreibung: Die Beschreibung, welche als zweiter Text angezeigt wird.
- [x] Erledigt: Ob Erledigt (true) oder Unerledigt (false).

## Credits
[SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Haupt-Entwickler von Stack-TODO-Liste.

[Universal-Team](https://github.com/Universal-Team): Für Universal-Core.
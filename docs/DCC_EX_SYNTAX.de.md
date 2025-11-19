## 1. Vollständige EBNF (Syntaxdefinition)

Die Erweiterte Backus-Naur-Form (EBNF) definiert die "Grammatik" oder Struktur *jeder* Nachricht, die an die oder von der Kommandozentrale gesendet wird.

```ebnf
(* Eine Nachricht ist ein einzelner Befehl oder eine einzelne Antwort,
   eingeschlossen in spitze Klammern. *)
Nachricht    ::= "<" Opcode ( " " Parameter )* ">"

(* Der Opcode ist IMMER ein einzelnes Zeichen.
   Er ist Groß-/Kleinschreibung-sensitiv
   (z. B. 'T' ist ein Befehl, 't' ist eine Antwort). *)
Opcode       ::= ZEICHEN

(* Parameter werden durch Leerzeichen getrennt. *)
Parameter    ::= Schlüsselwort | Numerisch | Zeichenkette

(* Ein Schlüsselwort ist eine Zeichenfolge ohne Leerzeichen.
   Es besteht aus Buchstaben (a-z, A-Z), Ziffern (0-9) und/
   oder dem Unterstrich (_).
   Schlüsselwörter sind NICHT Groß-/Kleinschreibung-sensitiv. *)
Schlüsselwort::= ( BUCHSTABE | ZIFFER | "_" )+

(* Eine Zahl ist eine Folge von Ziffern.
   Sie kann optional ein negatives Vorzeichen (-) haben.
   Dezimalzahlen oder Fließkommazahlen werden nicht unterstützt. *)
Numerisch    ::= [ "-" ] ZIFFER+

(* Eine Zeichenkette ist eine beliebige Zeichenfolge,
   die in doppelte Anführungszeichen (") eingeschlossen ist.
   Sie kann Leerzeichen enthalten. *)
Zeichenkette ::= '"' ( JEDES_ZEICHEN_AUSSER_ANFÜHRUNGSZEICHEN )* '"'

````

-----

## 2\. Vollständige Befehlstabelle (Opcode-Referenz)

Dies ist die vollständige Liste aller Opcodes (Befehle und Antworten), kategorisiert nach ihrer Funktion.

### A. Gleisstrom & Status

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`1`** | Befehl | (keine) | Schaltet den Gleisstrom (Gleis 0 / HAUPT) EIN. |
| **`0`** | Befehl | (keine) | Schaltet den Gleisstrom (Gleis 0 / HAUPT) AUS. |
| **`p`** | Befehl | `<Gleis> <Status>` | Setzt den Stromstatus (`0`=AUS, `1`=EIN) für ein bestimmtes Gleis (`0`=HAUPT, `1`=PROG). |
| `p` | Antwort | `<Gleis> <Status>` | Antwort auf einen `<p>`-Befehl oder eine Statusänderung. |
| **`c`** | Befehl | (keine) | Fordert einen detaillierten Statusbericht von der Kommandozentrale an (Version, Stromstatus usw.). |
| `c` | Antwort | `<Zentralenstatus>` | Sendet den detaillierten Statusbericht (Format: `<p0 1><p1 0><v 5.1.0 (Git-....)...>`). |
| **`S`** | Befehl | (keine) | Fordert einen vollständigen Status-Dump aller bekannten Geräte an (Weichen, Loks usw.). |
| `S` | Antwort | `<S ...>` | Antwort auf `<S>` (Formatdetails variieren). |
| **`i`** | Befehl | (keine) | Fordert Hardware- und Board-Informationen an (wird von EX-Installer verwendet). |
| `i` | Antwort | `<i ...>` | Sendet Hardware-Informationen. |
| **`Z`** | Befehl | (keine) | Führt einen Software-Reset (Neustart) der Kommandozentrale durch. |

### B. Loksteuerung (Fahrregler)

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`t`** | Befehl | `<Lok> <Geschw> <Richt> <Stufen>` | **Haupt-Fahrbefehl:** Steuert Lok (`Lok`-Adresse), Geschwindigkeit (`0-126`), Richtung (`0`=Rück, `1`=Vor) und Fahrstufen (`1`=14, `2`=28, `4`=128). |
| **`s`** | Befehl | `<Lok> <Geschw> <Richt>` | **Einfacher Fahrbefehl:** Verwendet die Standard-Fahrstufe (normalerweise 128). Geschwindigkeit (`0-126`), Richtung (`0`=Rück, `1`=Vor). |
| **`f`** | Befehl | `<Lok> <F_Num> <Status>` | Schaltet eine Funktion (`0-28`) für eine Lok (`Lok`) EIN (`1`) oder AUS (`0`). |
| **`F`** | Befehl | `<Lok> <F_Num> <Status>` | Veraltet, aber unterstützt. Identisch mit `<f>`. |
| **`l`** | Befehl | (keine) | Listet alle Loks auf, die sich derzeit im internen Roster (Speicher) befinden. |
| `l` | Antwort | `<Lok> <Reg> <GeschwByte> <FMap>` | Antwort auf `<l>`: Sendet den Lokstatus (`GeschwByte` ist DCC-kodiert, `FMap` ist eine Bitmaske der Funktionen). |
| **`X`** | Befehl | `<Lok>` | Löst den Nothalt für eine einzelne Lok aus (setzt die Geschwindigkeit auf -1). |
| **`K`** | Befehl | (keine) | Sendet ein Nothalt-Signal an *alle* Loks. |
| **`E`** | Befehl | (keine) | Setzt den Nothalt-Status für *alle* Loks zurück (setzt die Geschwindigkeit auf 0). |
| **`R`** | Befehl | `<Lok>` | Löscht (entfernt) eine Lok aus dem internen Speicher (Roster). |
| `R` | Antwort | `<Lok>` | Bestätigt das Löschen der Lok. |

### C. CV-Programmierung (Service- & Hauptgleis)

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`R`** | Befehl | `<CV> <Gleis>` | **CV lesen:** Liest CV (`1-1024`) auf dem Programmiergleis (`1`=PROG) oder Hauptgleis (`0`=POM). |
| `r` | Antwort | `<CV> <Wert>` | Antwort auf `<R>`: Sendet den gelesenen CV-Wert (`-1` oder `-2` bei Fehler). |
| **`W`** | Befehl | `<CV> <Wert> <Gleis>` | **CV schreiben (Byte):** Schreibt den Wert (`0-255`) in die CV (`1-1024`) auf PROG (`1`) oder POM (`0`). |
| `w` | Antwort | `<CV> <Wert>` | Antwort auf `<W>` (nur vom Programmiergleis): Bestätigt den geschriebenen Wert. |
| **`B`** | Befehl | `<CV> <Bit> <Wert> <Gleis>` | **CV schreiben (Bit):** Schreibt einen einzelnen Bit-Wert (`0` oder `1`) an eine Bit-Position (`0-7`) innerhalb einer CV. |
| `b` | Antwort | `<CV> <Bit> <Wert>` | Antwort auf `<B>` (nur vom Programmiergleis). |
| **`P`** | Befehl | `<CV> <Wert>` | **Paged-Modus-Schreiben:** Schreibt einen CV-Wert *direkt* auf das Programmiergleis (keine Bestätigung). |
| **`M`** | Befehl | `<Adr> <Wert>` | **Direkt-Modus-Schreiben:** Schreibt einen Wert *direkt* an eine Registeradresse (`Adr`). (Nur für Experten) |

### D. Zubehör (Weichen, Signale, etc.)

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`T`** | Befehl | `<ID> <Status>` | Stellt eine Weiche mit `ID` auf einen Status (`0`=Abzweig/Geschlossen, `1`=Gerade/Offen). |
| `H` | Antwort | `T <ID> <Status>` | Broadcast-Nachricht: Meldet, dass die Weiche `ID` ihren Status geändert hat (`0`/`1`). |
| **`Q`** | Befehl | `<ID> <Status>` | Stellt ein einfaches Zubehör (Signal) mit `ID` auf einen Status (`0`=AUS, `1`=EIN). |
| `H` | Antwort | `Q <ID> <Status>` | Broadcast-Nachricht: Meldet, dass das Zubehör `ID` seinen Status geändert hat (`0`/`1`). |

### E. Sensoren & E/A

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`Y`** | Befehl | `<ID> <Status>` | Setzt den Status eines VPIN (virtueller Pin) `ID` manuell auf `Status` (`0`/`1`). |
| `H` | Antwort | `Y <ID> <Status>` | Broadcast-Nachricht: Meldet, dass der Sensor/VPIN `ID` seinen Status geändert hat (`0`/`1`). |
| **`N`** | Befehl | `<VPin> <Typ> <Status>` | Definiert einen VPIN (`VPin`) mit einem Typ (z. B. `INPUT`, `OUTPUT`) und setzt seinen Anfangszustand (`Status`). |
| **`U`** | Befehl | `<VPin>` | Entfernt (undefiniert) einen VPIN (`VPin`). |

### F. JSON-Befehle (Listen & Konfiguration)

*(Diese Befehle verwenden JSON für komplexe Antworten; der Befehl selbst bleibt einfach.)*
| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`J`** | Befehl | `<Schlüsselwort>` | **JSON-Abfrage:** Fordert eine Liste oder Daten im JSON-Format an. |
| | | `T` | `<JT>` Fordert die Liste aller definierten Weichen an. |
| | | `A` | `<JA>` Fordert die Liste aller definierten Zubehörteile an. |
| | | `L` | `<JL>` Fordert die Liste aller definierten Loks (Roster) an. |
| | | `S` | `<JS>` Fordert die Liste aller definierten Sensoren an. |
| | | `O` | `<JO>` Fordert die Liste aller definierten Ausgänge an. |
| | | `R` | `<JR>` Fordert die Liste aller definierten Routen (EX-RAIL) an. |
| | | `C` | `<JC>` Fordert die Liste aller definierten Stromsensoren an. |
| `j` | Antwort | `<Schlüsselwort> [JSON-Daten]` | Antwort auf einen `<J>`-Befehl (z. B. `<jT [...]>`). |
| **`=`** | Befehl | `<JSON-Zeichenkette>` | Sendet einen Konfigurationsbefehl im JSON-Format (z. B. um Geräte zu definieren). |
| `=` | Antwort | `<JSON-Zeichenkette>` | Antwort/Bestätigung auf einen JSON-Konfigurationsbefehl. |

### G. Diagnose & System

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| **`D`** | Befehl | `<Schlüsselwort> [Parameter...]` | **Diagnosebefehl:** Führt verschiedene Diagnoseaktionen durch. |
| | | `ACK` | `<D ACK>` Schaltet den ACK-Impulstest für das Programmiergleis um. |
| | | `WIFI [ON\|OFF]` | `<D WIFI ON>` Schaltet das WLAN-Debugging EIN/AUS. |
| | | `SERIAL [ON\|OFF]`| `<D SERIAL ON>` Schaltet das serielle Debugging EIN/AUS. |
| | | `ETH [ON\|OFF]` | `<D ETH ON>` Schaltet das Ethernet-Debugging EIN/AUS. |
| | | `RAM` | `<D RAM>` Zeigt die Menge des freien Speichers an. |
| | | `I2C` | `<D I2C>` Scannt den I2C-Bus und listet gefundene Geräte auf. |
| | | `EEPROM` | `<D EEPROM>` Gibt den Inhalt des EEPROM aus (Debug). |
| | | `CLEAR` | `<D CLEAR>` Löscht alle im EEPROM gespeicherten Geräte (Weichen, Sensoren usw.). |
| | | `SHOW` | `<D SHOW>` Listet alle VPINs und ihre Zuweisungen auf. |
| `D` | Antwort | `[Text]` | Antwort auf einen Diagnosebefehl (Format variiert stark, oft menschenlesbarer Text). |
| **`V`** | Befehl | (keine) | Listet alle definierten Variablen und ihre Werte auf. |
| `V` | Antwort | `[Text]` | Antwort auf `<V>`. |
| **`+`** | Befehl | (keine) | Aktiviert den "Echo"-Modus (sendet alle empfangenen Befehle zurück). |
| **`-`** | Befehl | (keine) | Deaktiviert den "Echo"-Modus. |
| **`?`** | Befehl | (keine) | Fordert eine Liste aller verfügbaren Befehle (Opcodes) von der Zentrale an. |
| `?` | Antwort | `[Text]` | Sendet die Liste der implementierten Opcodes. |
| **`h`, `help`** | Befehl | `[Befehl]` | **Reserviert für Hilfe:** Diese Opcodes sind zusammen mit `?` für den Aufruf eines Hilfesystems reserviert. Das `debug_cli`-Beispiel bietet eine Referenzimplementierung. Siehe die [Debug-CLI-Syntax](./DEBUG_CLI_SYNTAX.de.md) für Details. |

### H. Fehler- & Broadcast-Antworten

| OPCODE | Typ | Parameter | Beschreibung |
| :--- | :--- | :--- | :--- |
| `X` | Antwort | (keine) | **Fehler:** Der letzte gesendete Befehl war ungültig, unbekannt oder syntaktisch falsch. |
| `H` | Antwort | `<Typ> [...]` | **Broadcast:** Eine allgemeine Nachricht, die eine Zustandsänderung meldet (z. B. Weiche, Sensor). Siehe Abschnitte D & E. |
| `*` | Antwort | `[Text]` | **Debug-Nachricht:** Eine allgemeine, menschenlesbare Debug- oder Statusnachricht (z. B. `<* WiFi connected>`). |

```
```

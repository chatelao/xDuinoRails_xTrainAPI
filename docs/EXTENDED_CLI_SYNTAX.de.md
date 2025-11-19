# Erweiterte CLI-Syntax

Dieses Dokument definiert die erweiterte Kommandozeilen-Schnittstellen (CLI) Syntax für die xDuinoRails_xTrainAPI. Diese Syntax ist selbsterklärender und leichter lesbar als die alten DCC-EX Einzelzeichen-Befehle. Sie beinhaltet außerdem Befehle für alle Ereignisse, die von der `IUnifiedModelTrainListener`-Schnittstelle unterstützt werden.

Die erweiterte Syntax folgt einem einheitlichen Format: `<BEFEHL param1="wert1" param2="wert2" ...>`.

**Hinweis zu den Befehlsformaten:** Die `CmdLineParser`-Klasse ist so konzipiert, dass sie jederzeit sowohl die alten Einzelzeichen-Befehle als auch die erweiterten Befehle akzeptiert. Die `CmdLinePrinter`-Klasse kann jedoch so konfiguriert werden, dass sie entweder das alte oder das erweiterte Format ausgibt. Dies wird durch das `USE_EXTENDED_CLI_SYNTAX`-Kompilierungsflag gesteuert. Standardmäßig wird die erweiterte Syntax für die Ausgabe verwendet. Um die alte Syntax für die Ausgabe zu verwenden, setzen Sie dieses Flag beim Kompilieren auf `0`.

## A. Gleisstrom & Status

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `POWER` | `<1>`/`<0>` | `state` ("ON" oder "OFF") | Schaltet den Gleisstrom ein oder aus. | `<POWER state="ON">` |
| `SET_POWER` | `<p>` | `track` (0=MAIN, 1=PROG), `state` (0=OFF, 1=ON) | Setzt den Strom für ein bestimmtes Gleis. | `<SET_POWER track="1" state="1">` |
| `STATUS` | `<c>` | (keine) | Fordert einen detaillierten Statusbericht an. | `<STATUS>` |
| `FULL_STATUS` | `<S>` | (keine) | Fordert einen vollständigen Status-Dump aller Geräte an. | `<FULL_STATUS>` |
| `HARDWARE_INFO` | `<i>` | (keine) | Fordert Hardware- und Board-Informationen an. | `<HARDWARE_INFO>` |
| `REBOOT` | `<Z>` | (keine) | Startet die Kommandozentrale neu. | `<REBOOT>` |

## B. Loksteuerung (Fahrregler)

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `THROTTLE` | `<t>` | `cab`, `speed` (0-126), `direction` (0=REV, 1=FWD), `steps` (14, 28, 128) | Haupt-Fahrbefehl. | `<THROTTLE cab="123" speed="100" direction="1" steps="128">` |
| `SIMPLE_THROTTLE` | `<s>` | `cab`, `speed` (0-126), `direction` (0=REV, 1=FWD) | Einfacher Fahrbefehl. | `<SIMPLE_THROTTLE cab="123" speed="100" direction="1">` |
| `FUNCTION` | `<f>`/`<F>` | `cab`, `function` (0-28), `state` (0=OFF, 1=ON) | Schaltet eine Lokomotivfunktion um. | `<FUNCTION cab="123" function="1" state="1">` |
| `LIST_LOCOS` | `<l>` | (keine) | Listet alle Loks im Roster auf. | `<LIST_LOCOS>` |
| `EMERGENCY_STOP_LOCO` | `<X>` | `cab` | Nothalt für eine einzelne Lok. | `<EMERGENCY_STOP_LOCO cab="123">` |
| `EMERGENCY_STOP_ALL` | `<K>` | (keine) | Nothalt für alle Loks. | `<EMERGENCY_STOP_ALL>` |
| `RESET_EMERGENCY_STOP_ALL` | `<E>` | (keine) | Setzt den Nothalt für alle Loks zurück. | `<RESET_EMERGENCY_STOP_ALL>` |
| `DELETE_LOCO` | `<R>` | `cab` | Löscht eine Lok aus dem Roster. | `<DELETE_LOCO cab="123">` |

## C. CV-Programmierung

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `READ_CV` | `<R>` | `cv`, `track` (0=POM, 1=PROG) | Liest eine CV. | `<READ_CV cv="1" track="1">` |
| `WRITE_CV_BYTE` | `<W>` | `cv`, `value`, `track` (0=POM, 1=PROG) | Schreibt ein Byte in eine CV. | `<WRITE_CV_BYTE cv="1" value="123" track="1">` |
| `WRITE_CV_BIT` | `<B>` | `cv`, `bit`, `value`, `track` (0=POM, 1=PROG) | Schreibt ein Bit in eine CV. | `<WRITE_CV_BIT cv="1" bit="7" value="1" track="1">` |
| `PAGED_MODE_WRITE` | `<P>` | `cv`, `value` | Paged-Modus CV-Schreiben. | `<PAGED_MODE_WRITE cv="1" value="123">` |
| `DIRECT_MODE_WRITE` | `<M>` | `address`, `value` | Direkt-Modus Register-Schreiben. | `<DIRECT_MODE_WRITE address="1024" value="123">` |

## D. Zubehör

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `TURNOUT` | `<T>` | `id`, `state` (0=THROWN, 1=STRAIGHT) | Stellt den Zustand einer Weiche ein. | `<TURNOUT id="456" state="1">` |
| `ACCESSORY` | `<Q>` | `id`, `state` (0=OFF, 1=ON) | Stellt den Zustand eines Zubehörs ein. | `<ACCESSORY id="789" state="1">` |

## E. Sensoren & E/A

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `VPIN` | `<Y>` | `id`, `state` (0/1) | Setzt den Zustand eines VPIN manuell. | `<VPIN id="1" state="1">` |
| `DEFINE_VPIN` | `<N>` | `vpin`, `type`, `state` (0/1) | Definiert einen VPIN. | `<DEFINE_VPIN vpin="1" type="INPUT" state="0">` |
| `UNDEFINE_VPIN` | `<U>` | `vpin` | Macht einen VPIN undefiniert. | `<UNDEFINE_VPIN vpin="1">` |

## F. JSON-Befehle

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `JSON_QUERY` | `<J>` | `type` ("T", "A", "L", "S", "O", "R", "C") | Fordert Daten im JSON-Format an. | `<JSON_QUERY type="T">` |
| `JSON_CONFIG` | `<=>` | `json` | Sendet einen Konfigurationsbefehl in JSON. | `<JSON_CONFIG json="{...}">` |

## G. Diagnose & System

| Befehl | Alt | Parameter | Beschreibung | Beispiel |
| :--- | :--- | :--- | :--- | :--- |
| `DIAGNOSTIC` | `<D>` | `command`, `params` | Führt verschiedene Diagnoseaktionen durch. | `<DIAGNOSTIC command="RAM">` |
| `LIST_VARIABLES` | `<V>` | (keine) | Listet alle definierten Variablen auf. | `<LIST_VARIABLES>` |
| `ECHO` | `<+>`/`<->` | `state` ("ON" oder "OFF") | Aktiviert oder deaktiviert den Echo-Modus. | `<ECHO state="ON">` |
| `LIST_COMMANDS` | `<?>` | (keine) | Fordert eine Liste der verfügbaren Befehle an. | `<LIST_COMMANDS>` |

## H. Vorgeschlagene neue Befehle

Diese Befehle werden vorgeschlagen, um Ereignisse in der `IUnifiedModelTrainListener`-Schnittstelle abzudecken, die von der alten DCC-EX-Syntax nicht abgedeckt werden.

| Befehl | Beschreibung | Parameter | Beispiel |
| :--- | :--- | :--- | :--- |
| `LOCO_FUNCTION_ANALOG` | Setzt einen analogen Wert für eine Lokfunktion. | `cab`, `function`, `value` | `<LOCO_FUNCTION_ANALOG cab="123" function="8" value="255">` |
| `DISPATCH` | Ändert den Dispatch-Status einer Lok. | `cab`, `state` ("ACQUIRED" oder "RELEASED"), `owner` | `<DISPATCH cab="123" state="ACQUIRED" owner="user1">` |
| `CONSIST_LINK` | Verbindet zwei Loks in einem Verbund. | `master`, `slave`, `type`, `inverted` (true/false) | `<CONSIST_LINK master="123" slave="456" type="ADVANCED" inverted="false">` |
| `CONSIST_UNLINK` | Trennt eine Lok von einem Verbund. | `slave` | `<CONSIST_UNLINK slave="456">` |
| `ACCESSORY_ANALOG` | Setzt einen analogen Wert für ein Zubehör. | `address`, `value` (0.0-1.0) | `<ACCESSORY_ANALOG address="789" value="0.75">` |
| `ACCESSORY_ERROR` | Meldet einen Zubehörfehler. | `address`, `errorId`, `errorMessage` | `<ACCESSORY_ERROR address="789" errorId="1" errorMessage="Overload">` |
| `SENSOR` | Setzt den Zustand eines Sensors. | `id`, `state` ("ACTIVE" oder "INACTIVE") | `<SENSOR id="101" state="ACTIVE">` |
| `FAST_CLOCK` | Aktualisiert die schnelle Uhr. | `time` (Unix-Zeitstempel), `factor` | `<FAST_CLOCK time="1678886400" factor="4.0">` |
| `HARDWARE_NODE_ATTACHED` | Meldet einen neuen Hardware-Knoten. | `uid`, `productName`, `booster` (true/false) | `<HARDWARE_NODE_ATTACHED uid="abc-123" productName="xPressNet" booster="false">` |
| `HARDWARE_NODE_LOST` | Meldet einen verlorenen Hardware-Knoten. | `uid` | `<HARDWARE_NODE_LOST uid="abc-123">` |
| `SYSTEM_MESSAGE` | Sendet eine Systemnachricht. | `source`, `message` | `<SYSTEM_MESSAGE source="WebServer" message="User logged in">` |
| `LOCO_DETECTED_ON_BLOCK` | Meldet eine auf einem Block erkannte Lok. | `sensorId`, `cab`, `orientation` ("FORWARD" oder "REVERSE") | `<LOCO_DETECTED_ON_BLOCK sensorId="202" cab="123" orientation="FORWARD">` |
| `LOCO_TELEMETRY` | Meldet Telemetriedaten für eine Lok. | `cab`, `type`, `value` | `<LOCO_TELEMETRY cab="123" type="SPEED" value="50.5">` |
| `LOCO_EXTERNAL_STATE` | Ändert den externen Zustand einer Lok. | `cab`, `state` | `<LOCO_EXTERNAL_STATE cab="123" state="PARKED">` |
| `LOCO_RAILCOM_RAW` | Sendet rohe RailCom-Daten. | `cab`, `appId`, `data` (Hex-String) | `<LOCO_RAILCOM_RAW cab="123" appId="1" data="A0B1C2">` |
| `NEW_LOCO_DISCOVERED` | Meldet eine neu entdeckte Lok. | `cab`, `name`, `icon` | `<NEW_LOCO_DISCOVERED cab="123" name="Big Boy" icon="steam_loco.png">` |
| `CV_READ_RESULT` | Meldet das Ergebnis eines CV-Lesevorgangs. | `cab`, `cv`, `value`, `success` (true/false) | `<CV_READ_RESULT cab="123" cv="1" value="10" success="true">` |
| `SUSI_CONFIG_READ` | Meldet das Ergebnis eines SUSI-Konfigurationslesevorgangs. | `cab`, `bank`, `index`, `value` | `<SUSI_CONFIG_READ cab="123" bank="1" index="2" value="3">` |
| `CONFIG_BLOCK_LOADED` | Meldet, dass ein Konfigurationsblock geladen wurde. | `cab`, `domain`, `data` (Hex-String) | `<CONFIG_BLOCK_LOADED cab="123" domain="sound" data="DEADBEEF">` |
| `PROGRESS_UPDATE` | Meldet den Fortschritt eines Vorgangs. | `operation`, `percent` | `<PROGRESS_UPDATE operation="Firmware Update" percent="75.5">` |
| `MECHANICAL_SYNC_EVENT` | Meldet ein mechanisches Synchronisationsereignis. | `cab`, `type`, `value` | `<MECHANICAL_SYNC_EVENT cab="123" type="CHUFF" value="1">` |

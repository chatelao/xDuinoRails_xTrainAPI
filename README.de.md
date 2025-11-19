# xTrainAPI - Einheitliche Modellbahnsteuerung

Willkommen beim xTrainAPI-Projekt! Dieses Repository enthält eine C++-basierte API zur Steuerung von digitalen Modelleisenbahnen und deren Zubehör.

## Dokumentation

Unsere API-Dokumentation wird automatisch generiert und auf GitHub Pages gehostet.

*   **Doxygen (C++ API):** Eine detaillierte Dokumentation der C++-Schnittstelle, Klassen und Methoden finden Sie hier:
    [Doxygen-Dokumentation](https://chatelao.github.io/xDuinoRails_xTrainAPI/doxygen)

*   **Swagger (REST API):** Die Spezifikation für unsere REST-Schnittstelle, einschließlich interaktiver Endpunkte, ist hier verfügbar:
    [Swagger UI](https://chatelao.github.io/xDuinoRails_xTrainAPI/swagger)

*   **Web-Tool:** Eine einfache Webanwendung zur Interaktion mit der xTrainAPI ist hier verfügbar:
    [Web-Tool](https://chatelao.github.io/xDuinoRails_xTrainAPI/webtool)

## Was ist xTrainAPI?

xTrainAPI ist eine einheitliche Schnittstelle, die es ermöglicht, verschiedene digitale Modellbahnsysteme über eine einzige, konsistente API zu steuern. Dies vereinfacht die Entwicklung von Steuerungssoftware, indem die Komplexität einzelner Protokolle (wie DCC, Märklin Motorola usw.) abstrahiert wird.

## Kernkonzepte

Die API ist in C++ als abstrakte Schnittstelle (`IUnifiedModelTrainListener`) definiert und dient als „Single Source of Truth“. Alle anderen Artefakte, wie die XML-Schemata und die OpenAPI-Spezifikation, werden von dieser C++-Header-Datei abgeleitet.

Für ein tieferes Verständnis der in der API verwendeten Begriffe und Datenfelder werfen Sie bitte einen Blick auf unser [Glossar](XTTRAIN_GLOSSARY.de.md) und das [Datenwörterbuch](DATA_DICTIONNARY.de.md).

## Mitwirken

Wir freuen uns über Beiträge! Bitte lesen Sie unsere `AGENTS.md`, bevor Sie Änderungen am Code vornehmen.

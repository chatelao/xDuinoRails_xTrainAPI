# xTrainAPI - Einheitliche Modellbahnsteuerung

Willkommen beim xTrainAPI-Projekt! Dieses Repository enthält eine C++-basierte API zur Steuerung von digitalen Modelleisenbahnen und deren Zubehör.

## Dokumentation

Unsere API-Dokumentation wird automatisch generiert und auf GitHub Pages gehostet.

*   **Doxygen (C++ API):** Eine detaillierte Dokumentation des C++-Interfaces, der Klassen und Methoden finden Sie hier:
    [Doxygen-Dokumentation](https://xtrainapi.github.io/xTrainAPI/doxygen/)

*   **Swagger (REST API):** Die Spezifikation unserer REST-Schnittstelle, inklusive interaktiver Endpunkte, ist hier verfügbar:
    [Swagger UI](https://xtrainapi.github.io/xTrainAPI/swagger/)

## Was ist xTrainAPI?

xTrainAPI ist eine vereinheitlichte Schnittstelle, die es ermöglicht, verschiedene digitale Modellbahnsysteme über ein einziges, konsistentes API zu steuern. Dies vereinfacht die Entwicklung von Steuerungssoftware, da die Komplexität der einzelnen Protokolle (wie DCC, Märklin Motorola, etc.) abstrahiert wird.

## Kernkonzepte

Die API ist in C++ als abstrakte Schnittstelle (`IUnifiedModelTrainListener`) definiert und dient als "Single Source of Truth". Alle anderen Artefakte, wie die XML-Schemata und die OpenAPI-Spezifikation, werden von dieser C++-Header-Datei abgeleitet.

Für ein tieferes Verständnis der in der API verwendeten Begriffe und Datenfelder, werfen Sie bitte einen Blick in unser [Glossar](XTTRAIN_GLOSSARY.md) und das [Data Dictionary](DATA_DICTIONARY.md).

## Mitwirken

Wir freuen uns über Beiträge! Bitte lesen Sie unsere `AGENTS.md`, bevor Sie Änderungen am Code vornehmen.

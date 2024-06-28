# invent
Collaborating on the Absolut project

## Veien videre

Nye eiere ønsker å kommersialisere Absolut - og de trenger hjelp fra oss til dette.

Oppstart for forprosjektet er satt til Mandag 1/7-2024 og forprosjektets kalender indikerer ca 2 ukers jobb for to mann strukket over ca 4 uker.

Forprosjektets mål er å legge grunnlaget for en "refactoring" jobb av Absolut koden slik at det er mulig å kommersialisere denne uten å være bundet av forskjellige lisenskriterier som per idag forhindrer å gjøre dette til et kommersielt produkt.

Dette dokumentets intensjon er å gi en innføring og beskrivelse av utfordringer vi ser samt legge fundamentet for hvordan vi tenker å løse oppgaven.

## Delmål

- [Funksjonalitetsbeskrivelse av Absolut](./FunctionaltyDescription.md)
- [Repeterbare tester av kritiske komponenter for Absolut](./FunctionalityTesting.md)
- [Sikre byggemiljøet for komponentene i Absolut](./Toolchain.md)
- [En plan for veien videre](./Recommendations.md)

## Første gjennomgang

Absolut prosjektet per nå har mange avhengigheter (både internt og externt).

Binærfiler bygges i dag med en Community versjon av Qt og kan produsere tre separate verktøy (versjoner).

- Absolut (Fullversjon med GUI)
  - AbsolutNoLib (kjernefunksjonalitet, kommandolinje)
  - AbsolutNoLibMPI (kjernefunksjonalitet med MPI,  kommandolinje)



## Forkortelser

|#|Forkortelse|Beskrivelse|
|---|---|---|
|1.|GUI|Grafisk brukergrensesnitt|
|2.|MPI|AbominationMPI|


## Referanser
- [Det opprinnelige Absolut prosjektet](https://github.com/csi-greifflab/Absolut)
- [Qt Community version lisens](https://www.qt.io/download-open-source)


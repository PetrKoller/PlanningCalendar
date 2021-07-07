##Plánovací kalendář
##Zadání z progtestu
Aplikace pro správu kalendáře s možností vytvářet události a jejich hledání.

Implementujte následující funcionalitu:

    1) denní, týdenní a měsíční zobrazení kalendáře
    2) vytvářet a spravovat události (čas, místo, datum, účastníci, ...)
    3) možnost nastavit události opakování (jednou za týden, 14 dní, ...)
    4) hledat události podle názvu a/nebo místa konání
    5) hledat nejbližší možný termín a možnost přesouvat události
    6) exportování a importování událostí

##Specifikace zadání
Kalendář bude mít 3 režimy zobrazení mezi kterými si uživatel může přepínat. Jsou to režimy měsíc, týden, den. Každý z režimů bude jiným způsobem zobrazovat události (podrobnosti o událostech). Do kalendáře uživatel může přidávat události, buď nornální a nebo s opakováním.

Kalendář bude schopen vyhledávat události podle zadaného názvu události, popř. místa a vypíše seznam událostí, které se shodují. Nad tímto seznamem budou možny být provedeny operace remove, edit, move.
Události se budou dělit na běžné události a události s opakováním, kde uživatel při vytváření události s opakováním si zvolí kolikrát se bude opakovat a po kolika dnech se bude opakovat.

Kalendář bude mít i možnost importovat a exportovat všechny události do textového formátu.

##Polymorfismus:
1) Display Mode

   Režimy zobrazení jsou realizovány polymorfismem, kde mají rodičovskou třídu CDisplayMode a každý režim si zvlášť implementuje metody pro vykreslování kalendáře a překlopení kalendáře na další periodu (záleží na konkrétním zvoleném režimu) a styl zobrazení událostí v daném režimu.


2) Command

   Příkazy jsou realizované polymorfismem, kde rodičovskou třídou je CCommand, která je abstraktní a obsahuje abstraktní metodu execute. Kterou si definuje každý příkaz specificky podle potřeb. Příklady příkazů jsou např. ChangeDisplayMode, NextPeriod, PrevPeriod, Exit, atd.


3) Event

   Události budou realizované polymorfně, kde rodičovskou třídou je běžná událost, která bude mít virtuální metody pro přesouvání, úpravu a odstranění. Z této třídy bude dědit událost s opakováním, která bude mít vlastní implementaci těchto metod. Událost s opakováním si uchovává kolikrát se bude opakovat a po kolika dnech se bude opakovat


4) Operation

   Operace jsou realizovány nad výsledkem příkazu FindEvent. Kde si uživatel zvolí konkrétní událost a na ní může provést odstranění, přesunutí a nebo úpravu události.


5) Move Strategy

   Strategie přesunu událostí slouží k nalezení vhondého datumu pro přesun dle definované strategie. Rodičovská třída je abstraktní a její potomci jsou základní 2 strategie přesunu a to je přesun na nejbližší den, kde se zachovává čas události. 2. stragie je přesun události na konkrétní datum, kde se také zachovává čas události. Obě tyto strategie vyhledávají vhodné datum tak, aby nenastala časová kolize s ostatními událostmi.

##Příkazy
Kalendář se ovládá pomocí příkazů jejích jména se zadávají do konzole. Příkazy jsou následující:
- add - Přidání nové události do kalendáže, uživatel bude vyzván k vyplnění informací o události (název, datum, účastníci, ...). Uživatel bude vyzván jakou událost chce přidat. Jestli normální a nebo událost s opakováním.
- change - Změna režimu zobrazení. Uživatel bude vyzván, aby zadal jeden z nabízených režimů, které různým způsobem zobrazují info o události.
    - month - Režim, kde uživatel vidí celý měsíc a den, kdy se koná nějaká událost je označen *
    - week - Režim, ve kterém uživatel vidí konkrétní týden, dále uživatel vidí kolik událostí se koná v daný den
    - day - Režim, ve kterém uživatel vidí konkrétní den a je vypsán seznam události, který se v daný den koná

- draw - Vykreslí kalendář podle aktuálně zvoleného režimu
- exit - Opuštění kalendáře
- export - Export všech událostí v kalendáři do textového souboru
- find - Najde seznam událostí, které odpovídají zadanému jménu. Nad výsledkem tohoto seznamu lze provádět operace:
    - edit - Úprava události, kde lze upravit jméno, čas události a seznam účastníků
    - move - Přesunutí události podle zvolené strategie přesunu. Podle typu události se dle uživatele přesune jen samotná událost nebo i všechna jejich opakování.
        - day - Přesun na nejbližší den bez časové kolize
        - date - Přesun na specifické datum bez časové kolize
    - remove - Odstranění události z kalendáře. Podle typu události se dle uživatele odstraní jen samotná událost nebo i všechna jejich opakování.

- import - Importování událostí do kalendáře z textového souboru
- next - Překlopení kalendáře do další periody, záleží na konkrétním režimu zobrazení
- prev - Překlopení kalendáře do předchozí periody, záleží na konkrétním režimu zobrazení

# Kompresia TGA obrázka

Tento program umožňuje komprimovať a dekomprimovať TGA obrázky metódou JBK (jé-bé-ká), alebo Jednoduchou Blokovou Kompresiou.

## Kompilácia a spustenie

Pre kompiláciu programu použite nasledujúci príkaz:

`source make.sh`

### Kompresia

Program komprimuje obrázok tak, že ho rozdelí na bloky so zadaným rozmerom a v každom bloku hľadá postupnosti podobných pixelov. Tieto postupnosti potom nahradí sekvenciou obsahujúcou prvý pixel v postupnosti a počet pixelov v postupnosti.

Príklad použitia programu na kompresiu:

`./jbk compress --input <cesta k souboru> --output <cesta k souboru> --block-size <číslo> --max-diff <číslo>`


###  Dekompresia

Príklad použitia programu na dekompresiu:

`./jbk decompress --input <cesta k souboru> --output <cesta k souboru>`


Argumenty programu (okrem prvého compress/decompress) môžu byť zadávané v ľubovoľnom poradí!









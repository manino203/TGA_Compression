# Komprese TGA obrázku

Tento program umožňuje komprimovat a dekomprimovat TGA obrázky metodou JBK (jé-bé-ké), neboli Jednoduchou Blokovou Kompresí.

## Kompilace a spuštění

Pro kompilaci programu použijte následující příkaz:

`source make.sh`

### Komprese

Program komprimuje obrázek tak, že rozdělí obrázek na bloky se zadaným rozměrem a v každém bloku hledá posloupnosti podobných pixelů. Tyto posloupnosti poté nahradí dvojicí obsahující první pixel v posloupnosti a počet pixelů v posloupnosti. Tato metoda je známa jako RLE (run-length encoding) komprese.

Příklad použití programu pro kompresi:

`./jbk compress --input <cesta k souboru> --output <cesta k souboru> --block-size <číslo> --max-diff <číslo>`


###  Dekomprese

Příklad použití programu pro dekompresi:

`./jbk decompress --input <cesta k souboru> --output <cesta k souboru>`


Argumenty programu (kromě prvního compress/decompress) mohou být zadány v libovolném pořadí!









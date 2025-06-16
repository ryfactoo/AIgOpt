# Tabu search dla problemu CVRP
Projekt na zajęcia algorytmy optymalizacji.
## Uruchomienie
`./alg_opt.exe -e cvrp2 -i A-n32-k5.vrp -c tabuExample.json -n 32`
Gdzie A-n32-k5.vrp to instancja z [CVRPLIB](http://vrp.galgos.inf.puc-rio.br/index.php/en/), z podanymi koordynatami miast EUC_2D,
natomiast tabuExample.json to plik konfiguracyjny w formacie:
```json
{
  "type": "tabu",
  "iterations": 12400,
  "tabu_size": 62,
  "neighbours": {
    "type": "mutation",
    "size": 31,
    "mut": {
      "type": "inverse"
    }
  }
}
```
Dostępne typy mutacji: `inverse`, `swap`, `shuffle`.
Dodatkowe opcje programu `./alg_opt.exe --help`

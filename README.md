<!-- TOC --><a name="the-grand-prix-dokumentacja"></a>
# ‘The Grand Prix’ - dokumentacja

<!-- TOC start (generated with https://github.com/derlin/bitdowntoc) -->

- [‘The Grand Prix’ - dokumentacja](#the-grand-prix-dokumentacja)
- [Autorzy](#autorzy)
- [Opis projektu](#opis-projektu)
   * [Założenia projektu](#zaoenia-projektu)
      + [Założenia bazowe](#zaoenia-bazowe)
      + [Założenia rozbudowane](#zaoenia-rozbudowane)
- [Instrukcja użytkownika](#instrukcja-uytkownika)
   * [Main Menu](#main-menu)
   * [Play](#play)
   * [Session](#session)
   * [Leaderboard](#leaderboard)
   * [Instrukcja kompilowania](#instrukcja-kompilowania)
- [Warte uwagi](#warte-uwagi)
   * [Generowanie modeli torów](#generowanie-modeli-torów)
   * [Fizyka](#fizyka)
   * [Assets, config](#assets-config)
   * [Sessions](#sessions)
- [Założenia a wykonanie](#zaoenia-a-wykonanie)
      + [Połączenie z bazą danych](#poczenie-z-baz-danych)
      + [Boty, lokalna i sieciowa gra wieloosobowa](#boty-lokalna-i-sieciowa-gra-wieloosobowa)
      + [Pozostałe](#pozostae)
- [Potencjalna rozbudowa projektu](#potencjalna-rozbudowa-projektu)
- [Podsumowanie](#podsumowanie)

<!-- TOC end -->

<!-- TOC --><a name="autorzy"></a>
# Autorzy

- Marcel Bieńko
- Michał Kierzkowski

<!-- TOC --><a name="opis-projektu"></a>
# Opis projektu

Realizowanym projektem jest wyścigowa gra okienkowa ***The Grand Prix***, w której mamy możliwość pokonywania okrążeń na czas, wybierając jeden z aktualnych torów i bolidów F1.

Projekt został wykonany w języku C++ z wykorzystaniem programowania obiektowego, biblioteki SFML (wykorzystanej do tworzenia aplikacji okienkowej) oraz biblioteki nlohmann/json (wykorzystanej do pracy z modelem toru). Całość realizowana jest w Visual Studio Code i kompilowana za pomocą MinGW.

W projekcie wykorzystaliśmy alternatywne do dziedziczenia podejście - kompozycję, zainspirowane tym filmem:

[The Flaws of Inheritance](https://youtu.be/hxGOiiR9ZKg)

Do projektu wykorzystaliśmy również skrypt w języku Python, który pozwalał nam na generowanie pliku z modelem toru w formacie JSON.

<!-- TOC --><a name="zaoenia-projektu"></a>
## Założenia projektu

Poniżej znajduje się lista z założeniami projektu, niewykonane założenia są ~~przekreślone~~

<!-- TOC --><a name="zaoenia-bazowe"></a>
### Założenia bazowe

- pojazd poruszający się zgodnie z zasadami fizyki (moc silnika, przyczepność opon,
aerodynamika)
- sesja ~~o określonej długości~~, w trakcie której gracz ustala najlepszy czas okrążenia
- ~~najlepszy czas okrążenia przesyłany na serwer do leaderboardu~~
- wyświetlenie timerów sesji, aktualnego, poprzedniego i najlepszego okrążenia
- menu główne
- plik .exe gotowej gry

<!-- TOC --><a name="zaoenia-rozbudowane"></a>
### Założenia rozbudowane

- ~~local (WSAD + strzałki)/online multiplayer~~
- możliwość wyboru spośród wielu torów
- możliwość wyboru spośród wielu pojazdów
- ~~customizacja (kolorystyka pojazdu, inicjały gracza, numer wyścigowy w tabeli)~~
- walidacja limitów toru (wyjazd poza tor – anulowanie czasu okrążenia)
- ~~boty~~
- ~~dynamiczna praca kamery (zbliżenia, oddalenia)~~
- ~~pogoda wpływająca na zachowanie pojazdu~~
- ~~setupy (aerodynamika, ciśnienia opon, użycie energii)~~
- ~~zaawansowana fizyka (oversteer, understeer, wheelspin)~~

<!-- TOC --><a name="instrukcja-uytkownika"></a>
# Instrukcja użytkownika

<!-- TOC --><a name="main-menu"></a>
## Main Menu

Gdy uruchomimy aplikację znajdziemy się najpierw w menu głównym. Tam, poruszając się strzałkami (góra, dół) możemy wybrać za pomocą Entera:

- grę (Play)
- listę z 10 najlepszymi czasami na każdym torze (Leaderboard)
- wyjście z gry (Exit)

<!-- TOC --><a name="play"></a>
## Play

Po wybraniu gry, znajdziemy się w menu wyboru toru i samochodu. Tor wybieramy za pomocą W i S, samochód za pomocą strzałek (góra, dół) a wybór zatwierdzamy Enterem, co przeniesie nas do sesji.

<!-- TOC --><a name="session"></a>
## Session

Po wybraniu sesji, znajdziemy się na wybranym torze i w wybranym samochodzie tuż przed linią startu-mety (czerwona linia). Samochodem poruszamy się za pomocą WSAD. Zadaniem gracza jest przejechanie całej nitki toru w jak najkrótszym czasie bez jego opuszczania.

Na środku górnej części ekranu znajduje się czas aktualnego okrążenia, gdy gracz opuści tor całym samochodem, ten czas zmieni kolor na czerwony. Oznacza to, że czas aktualnego okrążenia został anulowany (invalidated) i nie zostanie zapisany do Leaderboardu. Po ponownym przejechaniu przez linię startu-mety czas i anulowanie czasu zostaną zresetowane.

W prawym górnym rogu ekranu znajduje się czas ostatniego nieanulowanego okrążenia w danej sesji, a poniżej czasy poszczególnych sektorów (sektory kończą się czarnymi liniami na torze).

W prawym dolnym rogu znajduje się aktualna prędkość pojazdu.

W trakcie sesji, po wciśnięciu przycisku Esc pojawi się menu pauzy, w którym za pomocą strzałek (góra, dół) możemy wybrać:

- reset, który przywróci samochód do punktu startowego
- zapisanie i wyjście z sesji do głównego menu (Save & Exit)

Zapisanie sesji polega na zapisaniu wszystkich nieanulowanych czasów uzyskanych w trakcie sesji do pliku:

`logs/sessions/[id_toru]`

<!-- TOC --><a name="leaderboard"></a>
## Leaderboard

Po wybraniu leaderboardu, znajdziemy najlepsze 10 czasów zczytanych z pliku dla każdego toru. Wyświetlane są kolejno:

- czas całego okrążenia
- czas pierwszego sektora S1
- czas drugiego sektora S2
- czas trzeciego sektora S3
- tekstura auta, którym osiągnięty został czas

Możemy poruszać się między torami za pomocą strzałek (lewo, prawo) lub wyjść do menu głównego za pomocą Esc.

<!-- TOC --><a name="instrukcja-kompilowania"></a>
## Instrukcja kompilowania

Aby samemu skompilować projekt w Visual Studio Code należy zainstalować MinGW 32-bit, dodać do zmiennej PATH w systemie Windows oraz w edytorze kodu zmienić wartość `Include Path` w ustawieniach C_Cpp na `${workspaceFolder}/**`.

Następnie w konsoli należy wpisać polecenie:

`mingw32-make -f MakeFile`

I uruchomić program:

`main.exe`

<!-- TOC --><a name="warte-uwagi"></a>
# Warte uwagi

<!-- TOC --><a name="generowanie-modeli-torów"></a>
## Generowanie modeli torów

Do pomocy przy generowaniu modeli torów wykorzystaliśmy skrypt w języku Python, który zmieniał wybrane przez nas pliki .jpg z kształtem torów na plik JSON (model). Model zawierał położenie każdego z pikseli na obrazie, według których generowane są obiekty toru (segmenty). Takie podejście pozwalało nam w łatwy sposób sprawdzić, czy pojazd znajduje się poza torem.

```python
import cv2
import numpy as np
import json
from google.colab.patches import cv2_imshow
from google.colab import files

def downscale_image(image, scale_percent=40):
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    dim = (width, height)
    resized = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)
    return resized

def find_black_pixels(image):
    black_pixels = np.argwhere(image == 0)

    shapes = []
    for pixel in black_pixels:
        x, y = pixel[1], pixel[0]
        shapes.append({
            "x": int(x),
            "y": int(y),
            "width": 1,
            "height": 1,
            "rotation": 0
        })

    return shapes

def create_json(shapes, sectors):
    track_data = {
        "shapes": shapes,
        "sectors": sectors
    }

    with open("file.json", "w") as json_file:
        json.dump(track_data, json_file, indent=4)

def main(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    downscaled_image = downscale_image(image)
    cv2_imshow(downscaled_image)
    shapes = find_black_pixels(downscaled_image)

    print("Shapes detected:", shapes)

    create_json(shapes)

if __name__ == "__main__":
    main('file.jpg')
```

Najpierw plik jest skalowany do 40% dla zwiększenia wydajności, potem znajdywane są czarne piksele i zapisywane w pożądanym formacie do pliku.

<!-- TOC --><a name="fizyka"></a>
## Fizyka

Główną częścią projektu, która spędzała sen z powiek była fizyka. Zajęła zdecydowanie najwięcej czasu zarówno przy samej implementacji jak i znajdywaniu materiałów, dzięki którym mogliśmy zbudować odpowiednie funkcje.

Dzięki temu powstała fizyka (działająca na 32-tickach niezależnie od wyświetlanych klatek na ekranie), która biorąc realne wartości współczynników, mas, mocy, daje osiągi zbliżone do prawdziwych bolidów F1.

Oczywiście zabrakło zaawansowanych symulacji opon, zawieszenia, transferu masy, obrotów silnika, wykorzystania energii, czy uwzględnienia sztywności elementów samochodu.

<!-- TOC --><a name="assets-config"></a>
## Assets, config

Wewnątrz folderu z grą znajduje się folder `assets`, w którym definuje się czcionka i tekstury samochodów. Te można dowolnie edytować, również dodawać własne. Wystarczy jedynie odpowiednio zmienić plik `config/carlist` zgodnie ze wzorem:

`id_samochodu, nazwa, ścieżka_do_tekstury, moc_silnika_w_kW`

Można również stworzyć własne tory, które jednak wymagają nieco więcej konfiguracji. Najpierw należy wygenerować plik JSON za pomocą skryptu udokumentowanego wyżej. Następnie należy ustawić punkt startowy samochodu dodając:

```json
"spawn": {
        "x": x,
        "y": y,
        "angle": kat_rotacji
    }
```

ustawić wszystkie linie sektorów dodając:

```json
"sectors": [
        {
            "num": 1,
            "x": x,
            "y": y,
            "width": szerokosc_linii,
            "height": wysokosc_linii
            "rotation": kat_rotacji,
            "isFinishLine": true
        },
        {
            "num": 2,
            "x": x,
            "y": y,
            "width": szerokosc_linii,
            "height": wysokosc_linii,
            "rotation": kat_rotacji,
            "isFinishLine": false
        },
        {
            "num": 3,
            "x": x,
            "y": y,
            "width": szerokosc_linii,
            "height": wysokosc_linii,
            "rotation": kat_rotacji,
            "isFinishLine": false
        }
    ]
```

oraz zmienić plik `config/tracklist` zgodnie ze wzorem:

`id_toru, nazwa_toru`

<!-- TOC --><a name="sessions"></a>
## Sessions

Wszystkie okrążenia, które nie zostały anulowane zapisywane są w pliku `logs/sessions/id_toru` i aktualizowane za każdym razem, gdy zapiszemy kolejną sesję na tym torze. Dane zapisane są zgodnie ze wzorem:

`id_okrążenia_w_sesji, id_samochodu, czas_w_ms, czas_w_ms_s1, czas_w_ms_s2, czas_w_ms_s3`

<!-- TOC --><a name="zaoenia-a-wykonanie"></a>
# Założenia a wykonanie

Zgodnie z założeniami udało nam się stworzyć:

- fizykę, zgodnie z którą pojazd porusza się po torze
- sesję, w której gracz ustala jak najlepszy czas okrążenia
- wyświetlanie timerów
- menu główne, menu pauzy
- możliwość wyboru toru i samochodu
- walidację limitów toru
- kompletną, działającą grę

Nie udało nam się wykonać:

- połączenia z bazą danych
- pełnej customizacji (zrezygnowaliśmy z racji możliwości dołożenia własnych plików)
- lokalnej ani sieciowej gry wieloosobowej
- botów, z którymi gracz mógłby się ścigać
- dynamicznej pracy kamery
- dynamicznej pogody zmieniającej zachowanie pojazdu
- setupów będących w rękach gracza
- bardziej zaawansowanej fizyki

<!-- TOC --><a name="poczenie-z-baz-danych"></a>
### Połączenie z bazą danych

W trakcie realizacji projektu z powodu wykorzystania niepospolitego dla Windowsa narzędzia do programowania w języku C++ (VSCode i MinGW) natrafiliśmy na problemy przy instalacji **każdej** biblioteki. Próbowaliśmy instalacji bibliotek zarówno dla MongoDB, MySQL, MariaDB, PostgreSQL i każda z nich kończyła się niepowodzeniem kompilacji, a nawet linkowania, mimo ścisłego podążania za dokumentacją (nawet StackOverflow ani ChatGPT nie dał rady pomóc). Nie pomogły również package managery pokroju vcpkg. Niestety za późno już było na przeniesienie projektu do Visual Studio i próby dołączenia tam bibliotek. Dlatego zrezygnowaliśmy z połączenia projektu z bazą danych.

<!-- TOC --><a name="boty-lokalna-i-sieciowa-gra-wieloosobowa"></a>
### Boty, lokalna i sieciowa gra wieloosobowa

Lokalna gra wieloosobowa wymagałaby zmiany pracy kamery tak, aby mieściła obu graczy, a z racji że skupiliśmy się na time trialu (pokonywaniu okrążeń na czas) a nie wyścigach, na ten moment zrezygnowaliśmy z pomysłu. Tak samo postąpiliśmy z botami.

Sieciowa gra wieloosobowa wymagałaby połączenia z bazą danych, serwera lub możliwości hostowania na własnym sprzęcie, socketów i wielu innych bardziej zaawansowanych elementów.

<!-- TOC --><a name="pozostae"></a>
### Pozostałe

Na realizację reszty założeń nie wystarczyło nam pomysłów lub spadły na bardzo niski poziom naszego priorytetu.

<!-- TOC --><a name="potencjalna-rozbudowa-projektu"></a>
# Potencjalna rozbudowa projektu

Zgodnie z listą wyżej, priorytetem w rozbudowie projektu byłoby połączenie z bazą danych, które umożliwiłoby graczom porównywać swoje czasy online.

Następnymi krokami na pewno byłyby gra multiplayer, zarówno lokalna jak i sieciowa.

Nie mogłoby też zabraknąć minimapy, która ułatwiłaby poruszanie się po torze, a wszystkie tory musiałyby przejść proces optymalizacji. Tu szczególnie optymalizacja składowych segmentów toru (z reprezentowania pojedynczych pikseli na połączenie ich w jak największe prostokąty - zmniejszenie ilości elementów do renderowania) oraz optymalizacja walidacji limitów toru (aktualnie sprawdzane jest nakładanie się bolidu na każdy segment toru przy każdej wyrenderowanej klatce - algorytm quad tree na znajdywanie najbliższych segmentów).

Do tego rozwinięcie fizyki, wprowadzenie trybu gry z realistycznymi osiągami zespołów F1 (aktualnie każdy bolid ma równe osiągi) oraz umożliwienie zmiany ustawień bolidu (ciśnienie opon, kąty nachylenia skrzydeł, ustawienia zawieszenia).

Jednak wtedy lepszym podejściem mogłoby się okazać przeniesienie projektu do Visual Studio lub nawet do silnika Unreal Engine i tylko samodzielna implementacja fizyki.

<!-- TOC --><a name="podsumowanie"></a>
# Podsumowanie

Słowem zakończenia, projekt uważamy za udany i przyjemny w realizacji. Szczególnie biorąc pod uwagę nasze kilkumiesięczne doświadczenie z C++ i pierwszy większy projekt nad którym pracowaliśmy w grupie. Poszerzyliśmy dzięki niemu swoją wiedzę dotyczącą nie tylko samego języka C++, ale również całego jego ekosystemu i dobrych praktyk. Wykorzystanie MinGW i pliku konfiguracyjnego kompilatora Makefile pozwoliło nam lepiej zrozumieć jak działa cały proces tworzenia aplikacji od podszewki.

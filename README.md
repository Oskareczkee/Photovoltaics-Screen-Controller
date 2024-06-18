# Photovoltaics Screen
Goal of this project was to produce working screen based on screen with esp32 board. Project was cancelled after some time as the contact has been lost.   
All comments in README files are original in polish, as contractor was from Poland and did not want to write them in english.   
Comments in the code are in english.

## Code usage
It is strictly forbidden to copy any code from this repository except from Utility folder.   
You can freely look at the implementation, look at it as reference. If you want to use some part of this code please contact me at ```osniedz@gmail.com``` for permission. If you want me to develop this project for your specialized purposes  contact me using previously mentioned email.

## Features
This project features: 
+ 2 Servers
   - AP (Access Point) for logging to the network and logging to the solarman services
   - STA To get resources from the network via WiFi
+ HTML website (not finished completely) running on AP Server
 -  Logging works, but there was plan to add more, to create website where you would be able to see all the data from solarman website
+ Screen drawing library
  - Basic components have been implemented for image and text drawing
  - Components can be placed inside other components and are placed relative to their parent component   
  Sadly the screen we used was "paper screen" and its refresh rate was pretty slow
+ Many Utilites including:
  - Utility for easy HTTPS requests
  - Logger
  - Many more smaller

### Original project readme is below

# Panel do Fotowoltaiki
Projekt ten ma za zadanie napisanie softwaru do panelu kontroli systemów fotowoltaicznych. System ten ma pozwolić nam na zbieranie informacji z odpowiednich stron, wyfiltrowanie interesujących nas
informacji oraz ich poprawne wyświetlenie.  
Software jest pisany pod platformę ESP przy użyciu bibliotek Arduino

## Cele
- Umożliwienie podłączenia się do sieci WiFi użytkownika
    + Stworzenie serwera, który będzie transmitował stronę łączenia się z siecią
    + Ta sama strona, po połączeniu z siecią powinna dawać opcje wyboru z jakiego źródła chcemy mieć dane
- Stworzenie interfejsu graficznego dla użytkownika, za pomocą ekranu typu e-paper
- (Opcjonalnie, jeśli będzie wykonalne) dynamiczna aktualizacja softwaru

## Do poprawki
- Zmienić serwer DNS ESP, ten podstawowy jest zbyt kłopotliwy
- Dodać zaawansowane odświeżanie ekranu
- Rozważyć tryb oszczędzania energii w ekranie

## API stron z których będą używane dane
 - Solarman - main
 - Luxpowertek
 - (Opcjonalnie) można dodać więcej w razie potrzeby

## Poradnik krok po kroku co potrzebujemy do odpalenia projektu:  
- visual studio code
- platformio
    + espressif32 zainstalowane na platformio
- github
### Konfiguracja
- Ogólnie wszystko powinno być gotowe do działania, jednak do folderu .platformio (C:\Users\'nazwa użytkownika'\.platformio)\platforms\espressif32) wrzucamy zawartość folderu boards
- Projekt można od razu pobrać przy użyciu platformio (po lewej mamy ikonkę platformio, klikamy na nią) Miscellaneous -> Clone Git project, dajemy link do tego gita
- Ta sama zakładka PIO Home -> Open, opcjonalnie ctrl + shift + P -> piohome: open
- Wchodzimy w dowolny plik projektu
- `Ctrl + Shift + P` -> build - buduje binarkę projektu
- `Ctrl + Shift + P` -> upload - uploaduje kod na płytkę za pomocą portu COM (usb w naszym przypadku)
- `Ctrl + Shift + P` -> Serial Monitor - Serial, nasza konsolka z komunikatami 

## Uwagi
Narazie nie ma żadnych uwag

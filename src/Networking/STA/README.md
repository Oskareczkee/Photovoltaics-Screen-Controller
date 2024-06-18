## STA
Przy programowaniu funkcji sieci statycznej należy pamiętać żeby dane przy post nie były za długie. Przesłanie np. całej odpowiedzi przy pobieraniu tokenu wywołuje błędy.
Błędy te są spowodowane przez implementację serwera, w razie przesyłania dużych danych można spróbować zastosować techniki defragmentacji danych na mniejsze przy użyciu np. wielu POST requestów, każdy z takich requestów będzie zapisywał część danych. Przy pisaniu stron należy pamiętać, żeby w razie błędów dokonywać defragmentacji i brać tylko
potrzebne dane, np. przy pobieraniu tokenu jest robiona defragmentacja i jest pobierany tylko token. Token waży całe 848 bajtów!  

Maksymalna długość danych zakodowanych wynosi ok 2kB, należy pamiętać przy tym, że wliczają się w to także nazwy danych oraz znaki specjalne (&,=)
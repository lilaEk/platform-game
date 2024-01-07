todo  
- dodać audio  
- parallax background   
- możliwość zmiany bohatera w menu
- usunąć niepotrzebne assety  
- instrukcja poruszania (menu)  
- zmiana – wyliczanie liczby klatek animacji zamiast w konstruktorze
- sensowniejsza fizyka
- poprawić includy z "" na <>
- pawnstate.cpp do debuggingu - czyli do wywalenia na koniec
- opanować lepiej biblioteki - pousuwać co nie trzeba
- różne skille postaci
- funkcje fizyczne przy skoku i spadku


kod:
- dodać destruktory
- metody wirtualne
- konstruktory na początek
- inicjalizacja wszystkie pola
- refactor generowania struktur np:
    ```js
  const struktura = [	
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,1,1,1,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [0,0,0,0,0,0,0,0,0],
                    [1,1,1,1,1,1,1,1,1],
                ]
				
    for (i) {
      for (j) {
          switch(struktura[i][j]){
              case (1){
                  cell == CELLTYPE.GRASS
              }
              case (0){
                  cell == CELLTYPE.BLANK
              }
          }
      }
    }
  ```
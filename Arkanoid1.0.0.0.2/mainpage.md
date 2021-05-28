
! \mainpage Projekt Gra Arkanoid 


 \section gra_sec 1. Gra Arkanoid
Jest to gra komputerowa, w ktorej gracz porusza platforma i za jej pomoca odbija pileczke, ktora musi zbijac klocki rozstawione na planszy.
Za zniszczenie klocka gracz otrzymuje punkty oraz czasem moga z nich wypadac bonusy do zebrania, ktore np. powiekszaja paletke.
Gracz ma okreslona ilosc zyc, ktore traci, kiedy nie uda mu sie odbic pileczki. Celem gry jest zniszczenie wszystkich klockow.

![](arkanoid.png)


 \section drzewo_sec 2. Drzewo czworkowe
Drzewo czworkowe to jeden z podtypow drzewa, ktore jest struktura dynamiczna. Kazdy element zawiera 4 potomkow. 
Drzewo czworkowe znalazlo swoje zastosowanie, przy wykrywaniu kolizji w przestrzeni 2D. 
Ekran jest dzielony na 4 cwiartki i jesli zajdzie potrzeba to te cwiartki dzielone sa na kolejne cwiartki. 
Sposob ten umozliwia ograniczenie  sprawdzania kolizji elementow bardzo odleglych od siebie.

  ![](drzewo.png) 

\section drzewo2_sec 3. Kolizja w drzewie czworkowym
Drzewo czworkowe dzieli nasz ekran maksymalnie czterokrotnie, aby ograniczyc obszar sprawdzania kolizji. Obszar ten ogranicza sie do miejsca w ktorym znajduje sie pilka, 
a wlasciwie jej zasieg detekcji. Wykrycie kolizji jest sprawdzane poprzez uzycie przez nas Twierdzenia Pitagorasa. Nasza sprawdzana odlegloscia jest przeciwprostokatna w trojkacie prostokatnym. 
W przypadku, kiedy kolizja zaszlaby pod katem 90, z powyzszego Twierdzenia wynikaloby, ze nasza odleglosc, czyli szukana przeciwprostokatna pokryje sie z dluzsza przyprostokatna, natomiast druga bedzie rowna 0, 
czyli zamiast trojkata prostokatnego, bedziemy mieli po prostu odcinek. Jezeli odleglosc srodka pilki od krawedzi bloczku badz platformy jest rowna promieniowi pileczki to wykonywana jest kolizja.

 \section zapis_sec 4. Dynamiczna tablica dwuwymiarowa
W naszym projekcie, do przechowywania danych o bloczkach na planszy uzylismy dynamicznej dwuwymiarowej macierzy 8x8. 
Tworzone sa w niej prostokatne bloczki o wymiarach bedacych w stosunki 1:2. 
W taki sposob utworzylismy bloczki, ktore zajmuja maksymalnie powierzchnie polowy calej planszy. 
Utworzylismy tez kilka wariantow poziomow, ktore inicjuja nasza tablice dynamiczna zaleznie od wzoru matematycznego (pomijane sa wtedy niektore miejsca w tablicy, zaleznie od indeksow).

 ![](bloczki.png)
 
 \section bonusy_sec 5. Bonusy
Dodalismy do naszej gry 7 bonusow, na ktore jest mala szansa podczas rozbicia klocka. Podczas zbijania losowana jest wartosc od 0 do 100, 
jesli wylosowana wartosc bedzie wieksza od 70 to bedzie losowany numer 1-7, ktory bedzie odpowiadal danemu bonusowi. Mozna trafic nastepujace bonusy:

![](bonus1.png)
Wieksza platforma - powieksza podstawowy rozmiar platformy o 25 pikseli (standardowo platforma ma szerokosc 75 pikseli)

![](bonus2.png)
Mniejsza platforma - pomniejsza podstawowy rozmiar platformy o 25 pikseli 

![](bonus3.png)
Szybsza pilka - pilka porusza sie szybciej

![](bonus4.png)
Wolniejsza pilka - pilka porusza sie wolniej

![](bonus5.png)
Przenikanie - pilka przestaje sie odbijac od klockow, tylko zbija je i przechodzi przez nie dalej

![](bonus6.png)
Dodatkowe zycie - dodaje zycie, jezeli mamy ich mniej niz 3.

![](bonus7.png)
Podwojne punkty - punkty przy zbijaniu bloczkow sa podwajane

\section punktacja_sec 6. Punktacja
Standardowo za zbicie jednego bloczku gracz otrzymuje 100 punktow. Jesli natomiast, uda mu sie zbic kilka bloczkow, bez odbicia od platformy, kazdy nastepny bloczek bedzie zwiekszal mnoznik punktow o 1 
(standardowo jest on ustawiany na 1, wiec przy np. zbiciu 4 klockow po jednym odbiciu od platformy uzyskamy 1- 100, 2 - 2*100, 3 - 3*100, 4 - 4*100, czyli lacznie 1000 punktow). 
Jesli graczowi nie uda odbic sie pileczki i spadnie ona ponizej platformy straci on zycie oraz 100 punktow. Na koniec gry zycia ktore pozostaly zamieniane sa na dodatkowe 100 punktow za kazde.  
 
\section podsumowanie_sec 7. Podsumowanie i podzial pracy
Udalo nam sie zrobic wszystko co zaplanowalismy na nasz projekt. Jestesmy zadowoleni z efektu jaki udalo nam sie uzyskac. Z reguly wszyscy pracowalismy wspolnie nad projektem, kiedy nie moglismy znalezc rozwiazania, robilismy
"burze mozgow" jak za dany problem sie zabrac. Uwazamy, ze wszyscy wlozylismy do projektu cale nasze serca i nikt nie odstaje w udziale wykonanej pracy.
Nasz podzial pracy w formie procentowej:
Piotr Dziewiecki -33,(3)%
Jan Dyrdul - 33,(3)%
Figura Filip - 33,(3)%
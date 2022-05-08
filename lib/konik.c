#include "../include/konik.h"
#include <allegro.h>
/** \brief Alokacja obszaru pamięci dla dwuwymiarowej macierzy przechowującej zmienne typu int o wymiarach n na n
*@param n Rozmiar planszy 
*@return Wskaźnik na utworzoną macierz
*/
int ** utworz_tablice(int n){
     int **tab=(int **)malloc(sizeof(int*)*n);
     int i=0;
     while(i<n)
     {
         tab[i]=(int *)malloc(sizeof(int)*n);
         i++;
     }

     return tab;
 }
 /** \brief Zainicjowanie każdego elementu macierzy określoną wartością
*@param **tab Wskaźnik na macierz 
*@param n Rozmiar planszy 
*@param wartosc Liczba która zostanie umieszczona w każdym elemencie macierzy 
*/
 void zainicjuj_wartoscia(int **tab,int n,int wartosc)
 {
     int i=0;
     while(i<n)
     {
         int j=0;
         while(j<n)
         {
             tab[i][j]=wartosc;
             j++;
         }
         i++;
     }

 }
  /** \brief Wyświetlenie zawartości macierzy
*@param **wynik Wskaźnik na macierz 
*@param n Rozmiar planszy 
*/
 void pokaz_tablice(int **wynik,int n)
 {
     int i=0;
     while(i<n)
     {
         int j=0;
         while(j<n)
         {
             printf("%7.1d ",wynik[i][j]);
             j++;
         }
        printf("\n");
         i++;
     }

 }
  /** \brief Wyznaczenie ilości możliwych ruchów z zadanej pozycji
*
* Funkcja przegląda wszystkie pola na które skoczek mógłby się przesunąć z pozycji opisanej przez x i y. 
Jeżeli pole które aktualnie sprawdza jest nieodwiedzone i znajduje się w obrębie planszy to zlicza je.
Dodatkowo w sytuacji gdy do wykonania został tylko jeden ruch funkcja warunkowo zwraca wartość 1 aby konik mógł odwiedzić ostatnie pole.
*@param x pozycja na osi X dla której jest sprawdzana ilość możliwych ruchów
*@param y pozycja na osi Y dla której jest sprawdzana ilość możliwych ruchów
*@param **wynik Wskaźnik na macierz 
*@param n Rozmiar planszy 
*@param numer_ruchu Numer aktualnie wykonywanego ruchu
*@return Sume ilości pól na które może przesunąć się skoczek
*/
 int ilosc_ruchow(int x,int y,int **wynik,int n,int numer_ruchu)
 {
     int suma=0;
     int tablica_poruszania[8][2]={{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};     //tablica zawieraj�ca mo�liwe ruchy skoczka(Po literze "L")
     int i=0;
     while(i<8)
     {
         if((x+tablica_poruszania[i][0]>=0)&&(x+tablica_poruszania[i][0]<n)&&
            (y+tablica_poruszania[i][1]>=0)&&(y+tablica_poruszania[i][1]<n))                     //sprawdza czy przewidywany ruch jest w obrebi� planszy
         {
             if(wynik[x+tablica_poruszania[i][0]][y+tablica_poruszania[i][1]]==-1)               //sprawdza czy pole jest nieodwiedzone
             {
                 suma++;
             }
         }
         i++;
     }
     if(numer_ruchu==n*n-1)                                                                      //je�eli zosta�o ostatnie pole to konik rusza sie pomimo i� ostatni ruch nie ma wolnych ruch�w
     {
         return 1;
     }
     return suma;
 }
  /** \brief Szuka trasy dla konika
*
* Funkcja w pierwszej kolejności zapisuje numer akutalnego ruchu w odpowiednim miejscu macierzy. Następnie, jeżeli został wybrany tryb graficzny wywołuje funkcje
update i render odpowiedzialne za aktualizaje i wyświetlanie sposobu poruszania się konika. W tym momencie dla każdego pola na które mogłby się ruszyć konik jest obliczane
ile następnie będzie miał możliwości poruszenia. Z pośród tych wyników jest wybierane to pole na którym jest najmniej możliwości z pominięciem pól z których nie można dalej się ruszać.
Jeżeli konik ma pole na które może się poruszyć jest po raz kolejny wywoływana funkcja konik ze zmnienionymi niektórymi parametrami, w przeciwnym razie funkcja kończy swoje działanie.  
*@param **wynik Wskaźnik na macierz 
*@param x pozycja na osi X na której obecnie znajduje się konik
*@param y pozycja na osi Y na której obecnie znajduje się konik
*@param n Rozmiar planszy 
*@param *numer_ruchu Wskaźnik na zmienną zawierająca numer aktualnego ruchu
*@param tryb Informuje który tryb aplikacji jest aktywny(konsolowy=0,graficzny=1)
*@param *buffer Wskaźnik na obszar pamięci przeznaczony na bufor obrazu ekranu
*@param pop_x pozycja na osi X na której poprzednio znajdował się konik
*@param pop_y pozycja na osi Y na której poprzednio znajdował się konik
*@param wybor_oznaczenia Informacja o tym czy mają zostać wyświetlone numery pól czy pola mają być połączone liniami

*@return Jeżeli konik przejdzie przez każde pole planszy zwraca TRUE,a w przeciwnym razie zwraca FALSE
*/
 bool konik(int **wynik,int x,int y,int n,int *numer_ruchu,int tryb,BITMAP *buffer,int pop_x,int pop_y,int wybor_oznaczenia)
 {
     wynik[x][y]=*numer_ruchu;
     if(tryb==1)
     {
            update();

            render(n,pos_x_top[x][y],pos_y_top[x][y],wynik,pos_x_top[pop_x][pop_y],pos_y_top[pop_x][pop_y],wybor_oznaczenia);
     }
     int tablica_poruszania[8][2]={{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,+1},{-2,-1},{-1,-2}};    //tablica zawierająca możliwe ruchy skoczka(Po literze "L")
     int mozliwe_ruchy[8]={0,0,0,0,0,0,0,0};                                                     //tablica przechowujśca sumę możliwych ruchów skoczka z danego miejsca
     int min=-1;                                                                                 //indeks najmniejszego elementu tablicy możliwych ruchów
     if(*numer_ruchu==n*n)                                                                       //sprawdza czy algorytm znalazł rozwiązanie
     {
         return true;
     }
     int i=0;
     while(i<8)
     {

         if((x+tablica_poruszania[i][0]>=0)&&(x+tablica_poruszania[i][0]<n)&&
            (y+tablica_poruszania[i][1]>=0)&&(y+tablica_poruszania[i][1]<n))                     //sprawdza czy ruch z aktualnego miejsca jest w obrębie planszy
         {
             mozliwe_ruchy[i]=ilosc_ruchow(x+tablica_poruszania[i][0],
                                           y+tablica_poruszania[i][1],wynik,n,*numer_ruchu);     //ustalanie wartości ilości możliwych ruchów z przewidzianych ruchów
             if(wynik[x+tablica_poruszania[i][0]][y+tablica_poruszania[i][1]]!=-1)               //jeżeli pole było już odwiedzone, wyzeruj dalsze możliwe ruchy z tego pola
             {
                 mozliwe_ruchy[i]=0;
             }
         }
         i++;
     }
    i=0;
    while(i<8)
    {
        if(mozliwe_ruchy[i]!=0)                                                                 //pominięcie zerowych elementów
         {
             if(min==-1)                                                                        //sprawdza czy zmienna min ma ustaloną wartość(-1 to wartość nieustalona)
             {
                 min=i;                                                                         //przypisuje indeks pierwszego niezerowego elementu
             }
             else
             {
                 if(mozliwe_ruchy[i]<mozliwe_ruchy[min])                                        // poszukiwanie indeksu elementu o najmniejszej wartości
                 {
                     min=i;
                 }
             }
         }
        i++;
    }

     if(min==-1)                                                                                 //wykrywa czy konik może wykonać ruch
     {
         return false;
     }
     else
     {
         *numer_ruchu+=1;
         return konik(wynik,x+tablica_poruszania[min][0],y+tablica_poruszania[min][1],n,numer_ruchu,tryb,buffer,x,y,wybor_oznaczenia);
     }

 }
 /** \brief Wyświetla numery ruchów na każdym polu planszy które zostało odwiedzone
*@param n Rozmiar planszy 
*@param **wynik Wskaźnik na macierz 
*/
void pokaz_numery(int n,int **wynik)
{
    char napis[7];
    BITMAP *btm;
    int i=0;
    int licznik=0;
    while(i<n)
    {
        licznik=i;
        int j=0;
        while(j<n)
        {

            if(wynik[i][j]!=-1)
            {
                sprintf(napis,"%d",wynik[i][j]);
                btm=create_bitmap(text_length(font,napis),text_height(font));
                if(licznik%2==1)
                {
                    clear_to_color(btm,dark_color);
                }
                else
                {
                    clear_to_color(btm,bright_color);
                }

                textout_ex(btm,font,napis,0,0,makecol(255,100,100),-1);
                stretch_blit(btm,buffer,0,0,btm->w,btm->h,pos_x_top[i][j]+720/n*0.25,pos_y_top[i][j]+720/n*0.25,720/n*0.5,(720/n*0.5));
                destroy_bitmap(btm);
            }
            licznik++;
            j++;
        }
        licznik++;
        i++;
    }


}
 /** \brief Załadowanie tekstury konika i ustalenie prędkości działania programu 
*/
void init_konik()
{
    konik_texture=load_bitmap("konik.bmp",default_palette);
    predkosc_konika=2500;
}
 /** \brief Rysowanie punktu na pozycji "X" i "Y" o danym promieniu i kolorze na podanej bitmapie
*@param *btm Wskaźnik na bitmape na której ma zostać narysowany punkt
*@param x Pozycja na osi X gdzie ma pojawić się punkt 
*@param y Pozycja na osi Y gdzie ma pojawić się punkt 
*@param n Rozmiar planszy  
*/
void rysuj_punkt(BITMAP *bmp,int x,int y,int n)
{
    circlefill( bmp, x, y, (width/n)*0.06, makecol( 0, 255,0) );
}

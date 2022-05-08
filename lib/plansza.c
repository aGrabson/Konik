#include "../include/plansza.h"
/** \brief Inicjowanie zmiennych na potrzeby działania programu
*
*W pierwszej kolejności są tworzone macierze które będą przechowywały współrzędne pól szachowych, a następnie ustala ich współrzędne. Dzięki tym danym zostaje 
narysowana plansza na specjalnym buforze.
*@param n Rozmiar planszy 
*@param wysokosc Wysokość okna aplikacji
*@param szerokosc Szerokość okna aplikacji
*/
void init_plansza(int n,int wysokosc,int szerokosc)
{
    pos_x_top=utworz_tablice(n);
    pos_y_top=utworz_tablice(n);

    pos_x_bot=utworz_tablice(n);
    pos_y_bot=utworz_tablice(n);

    ustal_pos(n,wysokosc,szerokosc);
    bright_color=makecol(228, 238, 238);
    dark_color=makecol(51,51,51);
    plansza_buffer=create_bitmap(wysokosc,szerokosc);
    rysuj_plansze(n,plansza_buffer);
}
/** \brief Obliczanie pozycji pól planszy
*@param n Rozmiar planszy 
*@param wysokosc Wysokość okna aplikacji
*@param szerokosc Szerokość okna aplikacji
*/
void ustal_pos(int n,int wysokosc,int szerokosc)
{
    int i=0;
    while(i<n)
    {
        int j=0;
        while(j<n)
        {
            pos_x_top[i][j]=j*(szerokosc/n);
            pos_y_top[i][j]=i*(wysokosc/n);

            pos_x_bot[i][j]=(j+1)*(szerokosc/n);
            pos_y_bot[i][j]=(i+1)*(wysokosc/n);
            j++;
        }
        i++;
    }
}
/** \brief Rysowanie naprzemiennie jasnych i ciemnych pól reprezentujących plansze na buforze 
*@param n Rozmiar planszy 
*@param *buffer Wskaźnik na bitmape na której zostanie narysowana plansza
*/
void rysuj_plansze(int n,BITMAP *buffer)
{
    int licznik=0;
    int i=0;
    while(i<n)
    {
        licznik=i;
        int j=0;
        while(j<n)
        {
            if(licznik%2==0)
            {
                rectfill(buffer,pos_x_top[i][j],pos_y_top[i][j],pos_x_bot[i][j],pos_y_bot[i][j],bright_color);
            }
            else
            {
                rectfill(buffer,pos_x_top[i][j],pos_y_top[i][j],pos_x_bot[i][j],pos_y_bot[i][j],dark_color);
            }
            licznik++;
            j++;
        }
        i++;
    }
}

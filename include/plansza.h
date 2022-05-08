#ifndef PLANSZA_H
#define PLANSZA_H
#include <allegro.h>
#include "konik.h"
int **pos_x_top;/**< Wskaźnik na macierz zawierającą współrzędne X lewego górnego rogu każdego pola planszy*/
int **pos_y_top;/**< Wskaźnik na macierz zawierającą współrzędne Y lewego górnego rogu każdego pola planszy*/

int **pos_x_bot;/**< Wskaźnik na macierz zawierającą współrzędne X prawego dolnego rogu każdego pola planszy*/
int **pos_y_bot;/**< Wskaźnik na macierz zawierającą współrzędne Y prawego dolnego rogu każdego pola planszy*/

int bright_color;/**< Kolor jasnych pól planszy*/
int dark_color;/**< Kolor ciemnych pól planszy*/
BITMAP *plansza_buffer;/**<Wskaźnik na obszar pamięci przechowujący bitmapę z planszą*/

extern void init_plansza(int,int,int);
extern void ustal_pos(int,int,int);
extern void rysuj_plansze(int,BITMAP*);
#endif // PLANSZA_H

#ifndef KONIK_H
#define KONIK_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include "plansza.h"
#include "engine.h"

int predkosc_konika;/**< Prędkość działania programu*/
BITMAP *konik_texture;/**< Wskaźnik na bitmape przechowującą teksture konika*/


extern int ** utworz_tablice(int);
extern void zainicjuj_wartoscia(int**,int,int);
extern void pokaz_tablice(int**,int);
extern int ilosc_ruchow(int,int,int**,int,int);
extern void pokaz_numery(int,int**);
extern void pokaz_linie();
extern void rysuj_punkt();
extern bool konik(int**,int,int,int,int*,int,BITMAP*,int,int,int);
extern void init_konik();
#endif // KONIK_H

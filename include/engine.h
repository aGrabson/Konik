#ifndef ENGINE_H
#define ENGINE_H
#include <allegro.h>
#include "konik.h"
#include "plansza.h"
#include <stdbool.h>

int width;/**< Szerokość okna aplikacji*/
int height;/**< Wysokość okna aplikacji*/
bool space_button;/**< Stan przycisku spacji*/ 

BITMAP *buffer; /**<Wskaźnik na obszar pamięci przechowujący bufor*/
bool close_button; /**< Stan przycisku ESC*/  
extern void update();
extern void render(int,int,int,int**,int,int,int);
extern void init_engine(int);
extern void start_allegro(int);
#endif // ENGINE_H

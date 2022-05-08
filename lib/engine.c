#include "../include/engine.h"
#include <allegro.h>
/** \brief Ustalenie podstawowych wartości zmiennych biblioteki engine
*@param n Rozmiar planszy 
*/
extern void init_engine(int n)                                        
{                                                                     
     width=720;                                                       
     height=720;                                                      
     close_button=false;                                              
     space_button=true;                                               
}
/** \brief Zainicjowanie podstawowych elementów biblioteki Allegro oraz wywołanie pozostałych funkcji inicjujących.
*@param n Rozmiar planszy 
*/                                                                     
void start_allegro(int n)
{
     init_engine(n);
     allegro_init();                                                 // Uruchomienie środowiska Allegro
     set_color_depth( 32 );                                          // Ustawienie głębi kolorów na 32 bity
     set_gfx_mode( GFX_AUTODETECT_WINDOWED, width, height, 0, 0);    // Aktywacja trybu graficznego w oknie z ustawioną rozdzielczoscią
     set_window_title("Algorytm Konika Szachowego");                 // Ustalenie tytułu okna gry
     clear_bitmap(screen);                                           // Wyczyszczenie zawartości ekranu
     install_keyboard();                                             // Dodanie obsługi klawiatury
     buffer=create_bitmap((width/n)*n,(height/n)*n);                 // Utworzenie pliku buforowego o podanej rozdzielczosci
     clear_bitmap(buffer);
     init_plansza(n,height,width);
     init_konik();
}
/** \brief Sprawdzanie czy został wciśnięty klawisz ESC, jeśli tak zakończenie działania programu
*/
void update()
{
    if(key[KEY_ESC])
    {
        close_button=true;
        allegro_exit();
        exit(0);
    }
}
/** \brief Wyświetlenie aktualnego stanu okna aplikacji w trybie graficznym
*
* Jeżeli został wybrany tryb z liniami to zostają one narysowane na bitmapie zawierającą plansze, a następnie plansza zostaje przekopiowana do bufora 
*na którym następnie zostaje wyświetlona ikonka konika w odpowiednim miejscu. Tak przygotowany obraz zostaje wyświetlony na ekranie.
*W przypadku, gdy został wybrany tryb z numeracją pól, linie nie są rysowane, natomiast są wyświetlane numery skoków po przekopiowaniu obrazu planszy na bufor.
*@param n Rozmiar planszy
*@param x1 Pozycja aktualnie zajmowana przez konika na osi X
*@param y1 Pozycja aktualnie zajmowana przez konika na osi Y
*@param **wynik Wskaźnik na macierz 
*@param x_last Pozycja którą poprzednio zajmował konik na osi X
*@param y_last Pozycja którą poprzednio zajmował konik na osi Y
*@param wybor_oznaczenia Informacja o tym czy mają zostać wyświetlane numery czy linie(numer=1,linie=2)
*/
void render(int n,int x1,int y1,int **wynik,int x_last,int y_last,int wybor_oznaczenia)
{
    if(wybor_oznaczenia==2)
    {
        do_line(plansza_buffer,x_last+(width/n*0.5),y_last+(width/n*0.5),x1+(width/n*0.5),y1+(width/n*0.5),n,rysuj_punkt);
        circlefill(plansza_buffer, x1+(width/n*0.5), y1+(width/n*0.5),(width/n)*0.15, makecol( 255, 0, 0 ) );
    }

    blit(plansza_buffer,buffer,0,0,0,0,width,height);
    if(wybor_oznaczenia==1)
    {
        pokaz_numery(n,wynik);
    }
    stretch_blit(konik_texture,buffer,0,0,konik_texture->w,konik_texture->h,x1,y1,width/n,height/n);

    stretch_blit(buffer,screen,0,0,buffer->w,buffer->h,0,0,width,height);
    rest((predkosc_konika)/(n));

    while(key[KEY_SPACE])
    {
        update();
    }
}

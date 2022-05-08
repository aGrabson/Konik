#include <allegro.h>
#include "include/engine.h"
#include <stdio.h>

int main()
{
    int x,y,n,wybor,wybor_oznaczenia;
    int ilosc_odwiedzonych_pol=1;
    int **wynik;
    do
    {
        printf("Podaj rozmiar planszy: ");
        scanf("%d",&n);
        printf("\nPodaj pozycje x: ");
        scanf("%d",&x);
        printf("Podaj pozycje y: ");
        scanf("%d",&y);
        system("cls");
    }
    while(n<0||x<0||y<0||x>=n||y>=n);
    wynik=utworz_tablice(n);
    zainicjuj_wartoscia(wynik,n,-1);
    do
    {
        printf("Wybierz tryb wyswietlania: \n");
        printf("1.konsolowy\n");
        printf("2.graficzny\n");
        printf("Podaj liczbe: ");
        scanf("%d",&wybor);
        system("cls");
    }
    while(wybor!=1&&wybor!=2);

    if(wybor==2)
    {
        do
        {
            printf("Wybierz tryb oznaczenia: \n");
            printf("1.numeracja pol\n");
            printf("2.pola polaczone liniami\n");
            printf("Podaj liczbe: ");
            scanf("%d",&wybor_oznaczenia);
            system("cls");
        }
        while(wybor_oznaczenia!=1&&wybor_oznaczenia!=2);
    }


    if(wybor==1)
    {
        if(konik(wynik,x,y,n,&ilosc_odwiedzonych_pol,0,buffer,x,y,wybor_oznaczenia))
        {
            printf("\n\nKonik odwiedzil wszystkie pola\n\n");
        }
        else
        {
            printf("Konik odwiedzil %d z %d mozliwych pol\n\n",ilosc_odwiedzonych_pol,n*n);
        }
        pokaz_tablice(wynik,n);
    }
    else
    {
        start_allegro(n);
        if(konik(wynik,x,y,n,&ilosc_odwiedzonych_pol,1,buffer,x,y,wybor_oznaczenia))
        {
            allegro_message("Konik odwiedzil wszystkie pola");
        }
        else
        {
            allegro_message("Konik odwiedzil %d z %d mozliwych pol\n",ilosc_odwiedzonych_pol,n*n);
        }

        pokaz_tablice(wynik,n);
        while(!close_button)
        {
            update();
        }

    }
	system("pause");
return 0;
}
END_OF_MAIN();

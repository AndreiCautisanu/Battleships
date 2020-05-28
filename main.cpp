#include <iostream>
#include <winbgim.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cstring>
#include <cstdio>
#include <stack>
#include <fstream>

#define FUNDAL WHITE
#define MAX 20
#define hit 333
#define miss 444
#define onStack 444
#define Careu TablaDeJoc

using namespace std;

int stanga, sus, width, height, latura, numar, stanga2, sus2;
int culori[5] = {0, 0, CYAN, RED, LIGHTBLUE};

struct buton
{
    char text[MAX];
    int marime;
    int x,y;
    int x1,y1,x2,y2;
};


int nava4P = 4, nava3P = 3, nava21P = 21, nava22P = 22;
int nava4C = 4, nava3C = 3, nava21C = 21, nava22C = 22;
int prevNava4P, prevNava3P, prevNava21P, prevNava22P;

bool pusDejaNavaDe2 = false, apasaReturn = false;

int TablaDeJoc[MAX][MAX], TablaDeJocComputer[MAX][MAX];
int copieTablaDeJoc[11][11];

void CareuA()
{
    int i,j;
    numar=10;
    width=350;
    height=350;
    latura=width/numar;
    sus=150;
    stanga=50;
    setbkcolor(FUNDAL);
    setcolor(BLUE);
    for(i=1; i<=numar; i++)
        for(j=1; j<=numar; j++)
        {
            TablaDeJoc[i][j] = 0;
            delay( 3.5 );
            rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
        }
    delay( 50 );
}

void CareuB()
{
    int i,j;
    numar=10;
    width=350;
    height=350;
    latura=width/numar;
    sus=150;
    stanga=500;
    sus2 = sus;
    stanga2 = stanga;
    setbkcolor(FUNDAL);
    clearviewport();
    setcolor(BLUE);
    for(i=1; i<=numar; i++)
        for(j=1; j<=numar; j++)
        {
            TablaDeJocComputer[i][j] = 0;
            delay( 3.5 );
            rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
        }
    delay( 50 );
}

void ScoreBoard()
{
    int i;
    numar=11;
    width=50;
    height=350;
    latura=height/numar;
    sus=125;
    stanga=900;
    setcolor(BLUE);
    for(i=1; i<=numar; i++)
    {
        delay( 3.5 );
        rectangle( stanga, sus+latura*i, stanga+latura, sus+latura*(i+1) );
    }

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE );
    delay( 10 );
    bar( stanga, sus + latura * 5-3, stanga + latura, sus + latura * 5+3 );
    delay( 10 );
    bar( stanga, sus + latura * 8-3, stanga + latura, sus + latura * 8+3 );
    delay( 10 );
    bar( stanga, sus + latura * 10-3, stanga + latura, sus + latura * 10+3 );
}

int counterNave2 = 4;
void PiesaDupaLinieSiColoana(int color, int linia, int coloana, int marime)
{
    int x1, x2, y1, y2;

    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;

    if (TablaDeJoc[linia][coloana]==0)
    {
        TablaDeJoc[linia][coloana]=marime;
        if( marime == 2 )
        {
            if( counterNave2 > 2 )
                TablaDeJoc[linia][coloana] = 21;
            else
                TablaDeJoc[linia][coloana] = 22;
            counterNave2--;
        }
        setcolor(FUNDAL);
        setfillstyle(SOLID_FILL,FUNDAL);
        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        bar(x1+1, y1+1, x2, y2);
    }
}

void PunePiesaTablaComputer(int linia, int coloana, int marime, int valoare, int color)
{
    //int x1, x2, y1, y2;

    TablaDeJocComputer[linia][coloana]=valoare;
    /*
        setcolor(FUNDAL);
        setfillstyle(SOLID_FILL,FUNDAL);
        x1=stanga2+latura*(coloana-1);
        y1=sus2+latura*(linia-1);
        x2=x1+latura;
        y2=y1+latura;
        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        bar(x1+1, y1+1, x2, y2);
        */
}

void Piesa2(int color, int x, int y, int xPrev, int yPrev, int marime)
{
    int liniaPrev = (yPrev - sus) / latura + 1;
    int coloanaPrev = (xPrev - stanga) / latura + 1;

    int linia = (y - sus) / latura + 1;
    int coloana = (x - stanga) / latura + 1;

    int clickX, clickY;

    bool sePoate = true;

    if (coloana == coloanaPrev && abs(linia - liniaPrev) == marime - 1)
    {
        if (linia > liniaPrev)
            for (int i = liniaPrev + 1; i <= linia; i++)
            {
                if (TablaDeJoc[i][coloana] != 0)
                    sePoate = false;
            }
        else
            for (int i = linia; i < liniaPrev; i++)
            {
                if (TablaDeJoc[i][coloana] != 0)
                    sePoate = false;
            }
    }

    else if (linia == liniaPrev && abs(coloana - coloanaPrev) == marime - 1)
    {
        if (coloana > coloanaPrev)
            for (int i = coloanaPrev + 1; i <= coloana; i++)
            {
                if (TablaDeJoc[linia][i] != 0)
                    sePoate = false;
            }
        else
            for (int i = coloana; i < coloanaPrev; i++)
            {
                if (TablaDeJoc[linia][i] != 0)
                    sePoate = false;
            }
    }

    else if ((linia + coloana == liniaPrev + coloanaPrev || abs(linia-coloana) == abs(liniaPrev - coloanaPrev))
             && abs(coloana - coloanaPrev) == marime - 1)
    {
        if (linia > liniaPrev && coloana > coloanaPrev)
            for (int i = liniaPrev + 1, j = coloanaPrev + 1; i <= linia, j <= coloana; i++, j++)
            {
                if (TablaDeJoc[i][j] != 0)
                    sePoate = false;
            }

        else if (linia > liniaPrev && coloana < coloanaPrev)
            for (int i = liniaPrev + 1, j = coloanaPrev - 1; i <= linia, j >= coloana; i++, j--)
            {
                if (TablaDeJoc[i][j] != 0)
                    sePoate = false;
            }

        else if (linia < liniaPrev && coloana > coloanaPrev)
            for (int i = liniaPrev - 1, j = coloanaPrev + 1; i >= linia, j <= coloana; i--, j++)
            {
                if (TablaDeJoc[i][j] != 0)
                    sePoate = false;
            }

        else if (linia < liniaPrev && coloana < coloanaPrev)
            for (int i = liniaPrev - 1, j = coloanaPrev - 1; i >= linia, j >= coloana; i--, j--)
            {
                if (TablaDeJoc[i][j] != 0)
                    sePoate = false;
            }
    }

    if (TablaDeJoc[linia][coloana] == 0 && sePoate == true)
    {
        ///DACA PUNCTELE SUNT PE ACEEASI COLOANA
        if (coloana == coloanaPrev && abs(linia - liniaPrev) == marime - 1)
        {
            if (linia > liniaPrev)
                for (int i = liniaPrev + 1; i <= linia; i++)
                    PiesaDupaLinieSiColoana(color, i, coloana, marime);
            else
                for (int i = linia; i < liniaPrev; i++)
                    PiesaDupaLinieSiColoana(color, i, coloana, marime);
        }
        ///DACA PUNCTELE SUNT PE ACEEASI LINIE
        else if (linia == liniaPrev && abs(coloana - coloanaPrev) == marime - 1)
        {
            if (coloana > coloanaPrev)
                for (int i = coloanaPrev + 1; i <= coloana; i++)
                    PiesaDupaLinieSiColoana(color, linia, i, marime);
            else
                for (int i = coloana; i < coloanaPrev; i++)
                    PiesaDupaLinieSiColoana(color, linia, i, marime);
        }

        ///DACA PUNCTELE SUNT PE DIAGONALA
        else if ((linia + coloana == liniaPrev + coloanaPrev || abs(linia-coloana) == abs(liniaPrev - coloanaPrev))
                 && abs(coloana - coloanaPrev) == marime - 1)
        {
            ///DACA MERGE SPRE DREAPTA JOS
            if (linia > liniaPrev && coloana > coloanaPrev)
                for (int i = liniaPrev + 1, j = coloanaPrev + 1; i <= linia, j <= coloana; i++, j++)
                    PiesaDupaLinieSiColoana(color, i, j, marime);

            ///DACA MERGE SPRE STANGA JOS
            else if (linia > liniaPrev && coloana < coloanaPrev)
                for (int i = liniaPrev + 1, j = coloanaPrev - 1; i <= linia, j >= coloana; i++, j--)
                    PiesaDupaLinieSiColoana(color, i, j, marime);

            ///DACA MERGE SPRE DREAPTA SUS
            else if (linia < liniaPrev && coloana > coloanaPrev)
                for (int i = liniaPrev - 1, j = coloanaPrev + 1; i >= linia, j <= coloana; i--, j++)
                    PiesaDupaLinieSiColoana(color, i, j, marime);

            ///DACA MERGE SPRE STANGA SUS
            else if (linia < liniaPrev && coloana < coloanaPrev)
                for (int i = liniaPrev - 1, j = coloanaPrev - 1; i >= linia, j >= coloana; i--, j--)
                    PiesaDupaLinieSiColoana(color, i, j, marime);
        }

        else
        {
            do
            {
                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                    clearmouseclick(WM_LBUTTONDOWN);
                    Piesa2(color, clickX, clickY, xPrev, yPrev, marime);
                    break;
                }
            }
            while (1);
        }
    }

    else
    {
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);
                Piesa2(color, clickX, clickY, xPrev, yPrev, marime);
                break;
            }
        }
        while (1);
    }
}

void Piesa2Normal(int color, int x, int y, int xPrev, int yPrev, int marime)
{
    int liniaPrev = (yPrev - sus) / latura + 1;
    int coloanaPrev = (xPrev - stanga) / latura + 1;

    int linia = (y - sus) / latura + 1;
    int coloana = (x - stanga) / latura + 1;

    int clickX, clickY;

    bool sePoate = true;

    if (coloana == coloanaPrev && abs(linia - liniaPrev) == marime - 1)
    {
        if (linia > liniaPrev)
            for (int i = liniaPrev + 1; i <= linia; i++)
            {
                if (TablaDeJoc[i][coloana] != 0)
                    sePoate = false;
            }
        else
            for (int i = linia; i < liniaPrev; i++)
            {
                if (TablaDeJoc[i][coloana] != 0)
                    sePoate = false;
            }
    }

    else if (linia == liniaPrev && abs(coloana - coloanaPrev) == marime - 1)
    {
        if (coloana > coloanaPrev)
            for (int i = coloanaPrev + 1; i <= coloana; i++)
            {
                if (TablaDeJoc[linia][i] != 0)
                    sePoate = false;
            }
        else
            for (int i = coloana; i < coloanaPrev; i++)
            {
                if (TablaDeJoc[linia][i] != 0)
                    sePoate = false;
            }
    }

    else
        sePoate = false;

    if (TablaDeJoc[linia][coloana] == 0 && sePoate == true)
    {
        ///DACA PUNCTELE SUNT PE ACEEASI COLOANA
        if (coloana == coloanaPrev && abs(linia - liniaPrev) == marime - 1)
        {
            if (linia > liniaPrev)
                for (int i = liniaPrev + 1; i <= linia; i++)
                    PiesaDupaLinieSiColoana(color, i, coloana, marime);
            else
                for (int i = linia; i < liniaPrev; i++)
                    PiesaDupaLinieSiColoana(color, i, coloana, marime);
        }
        ///DACA PUNCTELE SUNT PE ACEEASI LINIE
        else if (linia == liniaPrev && abs(coloana - coloanaPrev) == marime - 1)
        {
            if (coloana > coloanaPrev)
                for (int i = coloanaPrev + 1; i <= coloana; i++)
                    PiesaDupaLinieSiColoana(color, linia, i, marime);
            else
                for (int i = coloana; i < coloanaPrev; i++)
                    PiesaDupaLinieSiColoana(color, linia, i, marime);
        }

        else
        {
            do
            {
                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                    clearmouseclick(WM_LBUTTONDOWN);
                    Piesa2(color, clickX, clickY, xPrev, yPrev, marime);
                    break;
                }
            }
            while (1);
        }
    }

    else
    {
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);
                Piesa2Normal(color, clickX, clickY, xPrev, yPrev, marime);
                break;
            }
        }
        while (1);
    }
}

void genereazaNavaComputer(int linia, int coloana, int marime)
{
    int randLin, randCol;
    int directii[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8}, directieSelectata = 0;


    //PunePiesaTablaComputer(linia, coloana, marime, BLUE);
    if (coloana < marime)
        directii[4] = 0;
    else if (coloana > 11 - marime)
        directii[2] = 0;

    if (linia < marime)
        directii[1] = 0;
    else if (linia > 11 - marime)
        directii[3] = 0;

    if (linia - marime < 0 || coloana + marime > 11)
        directii[5] = 0;
    if (linia + marime > 11 || coloana + marime > 11)
        directii[6] = 0;
    if (linia + marime > 11 || coloana - marime < 0)
        directii[7] = 0;
    if (linia - marime < 0 || coloana - marime < 0)
        directii[8] = 0;

    while (directii[directieSelectata] == 0)
        directieSelectata = 1 + rand() % 8;

    bool sePoate = true;

    switch (directieSelectata)
    {
    case 1:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia - i][coloana] != 0)
                sePoate = false;
        break;

    case 2:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia][coloana + i] != 0)
                sePoate = false;
        break;

    case 3:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia + i][coloana] != 0)
                sePoate = false;
        break;

    case 4:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia][coloana - i] != 0)
                sePoate = false;
        break;

    case 5:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia - i][coloana + i] != 0)
                sePoate = false;
        break;

    case 6:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia + i][coloana + i] != 0)
                sePoate = false;
        break;

    case 7:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia + i][coloana - i] != 0)
                sePoate = false;
        break;

    case 8:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia - i][coloana -i] != 0)
                sePoate = false;
        break;
    }

    if (sePoate == false || TablaDeJocComputer[linia][coloana] != 0)
    {
        srand(time(NULL));
        randLin = rand() % 10 + 1;
        randCol = rand() % 10 + 1;

        genereazaNavaComputer(randLin, randCol, marime);
    }

    else
    {
        int valoare = marime;

        if (marime == 2)
        {
            if (pusDejaNavaDe2 == false)
            {
                valoare = 21;
                pusDejaNavaDe2 = true;
            }
            else
                valoare = 22;
        }

        switch (directieSelectata)
        {
        case 1:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia - i, coloana, marime, valoare, culori[marime]);
            break;

        case 2:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia, coloana + i, marime, valoare, culori[marime]);
            break;

        case 3:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia + i, coloana, marime, valoare, culori[marime]);
            break;

        case 4:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia, coloana - i, marime, valoare, culori[marime]);
            break;

        case 5:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia - i, coloana + i, marime, valoare, culori[marime]);
            break;

        case 6:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia + i, coloana + i, marime, valoare, culori[marime]);
            break;

        case 7:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia + i, coloana - i, marime, valoare, culori[marime]);
            break;

        case 8:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia - i, coloana - i, marime, valoare, culori[marime]);
            break;
        }
    }

}

void genereazaNavaComputerNormal(int linia, int coloana, int marime)
{
    int randLin, randCol;
    int directii[5] = {0, 1, 2, 3, 4}, directieSelectata = 0;


    //PunePiesaTablaComputer(linia, coloana, marime, BLUE);
    if (coloana < marime)
        directii[4] = 0;
    else if (coloana > 11 - marime)
        directii[2] = 0;

    if (linia < marime)
        directii[1] = 0;
    else if (linia > 11 - marime)
        directii[3] = 0;

    while (directii[directieSelectata] == 0)
        directieSelectata = 1 + rand() % 4;

    bool sePoate = true;

    switch (directieSelectata)
    {
    case 1:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia - i][coloana] != 0)
                sePoate = false;
        break;

    case 2:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia][coloana + i] != 0)
                sePoate = false;
        break;

    case 3:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia + i][coloana] != 0)
                sePoate = false;
        break;

    case 4:
        for (int i = 0; i < marime; i++)
            if (TablaDeJocComputer[linia][coloana - i] != 0)
                sePoate = false;
        break;
    }


    if (sePoate == false || TablaDeJocComputer[linia][coloana] != 0)
    {
        srand(time(NULL));
        randLin = rand() % 10 + 1;
        randCol = rand() % 10 + 1;

        genereazaNavaComputer(randLin, randCol, marime);
    }

    else
    {
        int valoare = marime;

        if (marime == 2)
        {
            if (pusDejaNavaDe2 == false)
            {
                valoare = 21;
                pusDejaNavaDe2 = true;
            }
            else
                valoare = 22;
        }

        switch (directieSelectata)
        {
        case 1:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia - i, coloana, marime, valoare, culori[marime]);
            break;

        case 2:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia, coloana + i, marime, valoare, culori[marime]);
            break;

        case 3:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia + i, coloana, marime, valoare, culori[marime]);
            break;

        case 4:
            for (int i = 0; i < marime; i++)
                PunePiesaTablaComputer(linia, coloana - i, marime, valoare, culori[marime]);
            break;
        }
    }

}

void salvePlayer( int k )
{
    int Sus, Stanga, linia, coloana;
    int x, y, x1, y1, x2, y2;
    int widthScoreB, heightScoreB, laturaScoreB, susScoreB, stangaScoreB;
    int navaCp;

    int bars[7][4], counter = 0;

    Sus = 150;
    Stanga = 500;
    width=350;
    height=350;

    apasaReturn = false;

    while( k )
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if( x < 993 && x > 847 && y < 695 && y > 665)
                apasaReturn = true;
            if( apasaReturn )
            {
                goto return_clicked;
            }
            if (x>=Stanga && x<=Stanga+width && y>=Sus&&y<=Sus+height)
            {
                linia=(y-Sus)/latura+1;
                coloana=(x-Stanga)/latura+1;
                if ( TablaDeJocComputer[linia][coloana] != hit)
                {
                    //verifica daca patratul respectiv a mai fost lovit sau nu
                    setcolor(FUNDAL);
                    setfillstyle(SOLID_FILL,FUNDAL);
                    x1=Stanga+latura*(coloana-1);
                    y1=Sus+latura*(linia-1);
                    x2=x1+latura;
                    y2=y1+latura;
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    line( x1+1, y1+1, x2, y2 );
                    line( x1+1, y1+latura, x2, y2-latura );
                    k--;
                    if( TablaDeJocComputer[linia][coloana] != 0 )
                    {
                        // daca nu a fost lovit { adica diferit de hit } si este si diferit de 0, inseamna ca a lovit o nava
                        navaCp = TablaDeJocComputer[linia][coloana];
                        widthScoreB=50;
                        heightScoreB=350;
                        laturaScoreB=height/11;
                        susScoreB=125;
                        stangaScoreB=900;

                        if( navaCp == 4 )
                        {
                            nava4C--;
                            bars[counter][0] = stangaScoreB + 1;
                            bars[counter][1] = susScoreB + laturaScoreB * (nava4C + 1 ) + 1;
                            bars[counter][2] = stangaScoreB + laturaScoreB;
                            bars[counter][3] = Sus + laturaScoreB * ( nava4C + 2 );
                            //bar( stangaScoreB, susScoreB + laturaScoreB * (nava4C + 1 ) + 1, stangaScoreB + laturaScoreB, Sus + laturaScoreB * ( nava4C + 2 ) );
                        }
                        if( navaCp == 3 )
                        {
                            nava3C--;
                            bars[counter][0] = stangaScoreB + 1;
                            bars[counter][1] = susScoreB + laturaScoreB * (nava3C + 5 ) + 1;
                            bars[counter][2] = stangaScoreB + laturaScoreB;
                            bars[counter][3] = Sus + laturaScoreB * ( nava3C + 6 );
                            //bar( stangaScoreB, susScoreB + laturaScoreB * (nava3C + 5 ) + 1, stangaScoreB + laturaScoreB, Sus + laturaScoreB * ( nava3C + 6 ) );
                        }
                        if( navaCp == 21 )
                        {
                            nava21C--;
                            bars[counter][0] = stangaScoreB + 1;
                            bars[counter][1] = susScoreB + laturaScoreB * (nava21C - 11 ) + 1;
                            bars[counter][2] = stangaScoreB + laturaScoreB;
                            bars[counter][3] = Sus + laturaScoreB * ( nava21C - 10 );
                            //bar( stangaScoreB, susScoreB + laturaScoreB * (nava21C - 11 ) + 1, stangaScoreB + laturaScoreB, Sus + laturaScoreB * ( nava21C - 10 ) );
                        }
                        if( navaCp == 22 )
                        {
                            nava22C--;
                            bars[counter][0] = stangaScoreB + 1;
                            bars[counter][1] = susScoreB + laturaScoreB * (nava22C - 10 ) + 1;
                            bars[counter][2] = stangaScoreB + laturaScoreB;
                            bars[counter][3] = Sus + laturaScoreB * ( nava22C - 9 );
                            //bar( stangaScoreB, susScoreB + laturaScoreB * (nava22C - 10 ) + 1, stangaScoreB + laturaScoreB, Sus + laturaScoreB * ( nava22C - 9 ) );
                        }

                        counter++;

                    }
                    TablaDeJocComputer[linia][coloana] = hit;
                }
            }
        }
    }

    counter--;

    if (counter != -1)
    {
        widthScoreB=50;
        heightScoreB=350;
        laturaScoreB=height/11;
        susScoreB=125;
        stangaScoreB=900;

        setcolor(FUNDAL);
        setfillstyle(SOLID_FILL,FUNDAL);
        setcolor( BLACK );
        setfillstyle( SOLID_FILL, LIGHTGRAY );

        for (int i = 0; i <= counter; i++)
        {
            bar(bars[i][0], bars[i][1], bars[i][2], bars[i][3] - 25);
        }

        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE );
        bar( stangaScoreB, susScoreB + 31 * 5-3, stangaScoreB + 31, susScoreB + 31 * 5 + 3 );
        bar( stangaScoreB, susScoreB + 31 * 8-3, stangaScoreB + 31, susScoreB + 31 * 8 + 3 );
        bar( stangaScoreB, susScoreB + 31 * 10-3, stangaScoreB + 31, susScoreB + 31 * 10 + 3 );

        // verifica care nava a fost lovita

        /*
               setcolor(FUNDAL);
               setfillstyle(SOLID_FILL,FUNDAL);
               setcolor( RED );
               setfillstyle( SOLID_FILL, RED );
               bar( stangaScoreB, susScoreB + laturaScoreB * navaCp + 1, stangaScoreB + laturaScoreB, sus + laturaScoreB * ( navaCp + 1 ) );
            */
        // coloreaza patratele din ScoreBoard

    }
return_clicked:
    ;
}

int NrOfHits = 0;
int nrH = 7, nrpieseAnt;
int C4 = 1, C3 = 1, C21 = 1, C22 = 1;
int lComp, cComp, directiaComp, counterSchimbare = 0, lAnt, cAnt;
int gotopHit = 1, gobotHit = 1, goleftHit = 1, gorightHit = 1, overHit = 0;
bool adevSchimbare, hitOver = false, atacAnt;
// NrOfHits tine cont de numarul de nave lovite in atacurile precedente
// Va scadea din nou la 0 daca va scufunda o nava, inca va creste iar daca a fost lovita si o alta nava in acel atac
// deoarece NrOfHit poate creste peste 2, in decursul a mai multor atacuri, overHit tine cont daca au fost lovite doua sau mai multe nave intr-un singur atac
// gotopHit, gobotHIt, goleftHit si gorightHit sunt counter care, in functie de valoare lor, 1 sau 0, trimit la sau interzic intrarea in functiile respective topHi, ...
// nrH, destul de evident sper eu, tine cont de numarul de hit-uri valabile
void salveCalculator(   )
{
    int sus, stanga, linia, coloana;
    int x, y, x1, y1, x2, y2;
    int directia;
    int counterD, counterP = 0;
    int nrPiese = 0;
    sus = 150;
    stanga = 50;
    width=350;
    height=350;

    // verifica starea navelor computer-ului
    if( nava4C < 1 && C4 )
    {
        nrH = nrH - 3;
        C4--;
    }
    if( nava3C < 1 && C3 )
    {
        nrH = nrH - 2;
        C3--;
    }
    if( nava21C < 20 && C21 )
    {
        nrH = nrH - 1;
        C21--;
    }
    if( nava22C < 21 && C22 )
    {
        nrH = nrH - 1;
        C22--;
    }
    // intra in if daca e primul atac sau daca atacul precedent nu a lovit nimic
    // este in principiu aceeasi chestie cu elemente din alte functii, nu e prea mult de explicat aici
outside:
    if( !NrOfHits )
    {
        atacAnt = false;
        adevSchimbare = false;
        int poz_ramase = 100;
        for( int i = 1; i <= 10; i++ )
            for( int t = 1; t <= 10; t++ )
                if( Careu[i][t] == hit )
                    poz_ramase--;
        gotopHit = 1;
        gobotHit = 1;
        goleftHit = 1;
        gorightHit = 1;
        counterSchimbare = 0;
        srand( time( NULL ) );
jump:
        counterD = 0;
        linia = rand() % 10 + 1;
        coloana = rand() % 10 + 1;
        counterP++;
        int liniaB = linia, coloanaB = coloana;

        // de verificat in caz de probleme aici in relatie cu else-ul, atunci cand piesele nu sunt cap in cap

        lComp = linia;
        cComp = coloana;
        if( Careu[linia][coloana] == hit )
            goto jump;
        if( counterP > ( poz_ramase - nrPiese ) * 3 || nrH > poz_ramase)
            goto jump3;

        directia = rand() % 8 + 1; // 8 directii posibile, incepand cu diagonala stanga sus( 1 ) si incheind cu orizontala stanga ( 8 )
jump2:
        {
            directia++;
            if( directia == 9 )
                directia = 1;
            counterD++;
        }
        if( counterD > 9 )
            goto jump;
        directiaComp = directia;
        if( ( directia == 1 && ( linia - nrH + nrPiese < 0 || coloana - nrH + nrPiese < 0 ) )
                || ( directia == 2 &&  linia - nrH + nrPiese < 0 )
                || ( directia == 3 && ( linia - nrH + nrPiese < 0 || coloana + nrH - nrPiese > 10 ) )
                || ( directia == 4 &&  coloana + nrH - nrPiese > 10 )
                || ( directia == 5 && ( linia + nrH - nrPiese > 10 || coloana + nrH - nrPiese > 10 ) )
                || ( directia == 6 &&  linia + nrH - nrPiese > 10 )
                || ( directia == 7 && ( linia + nrH -nrPiese > 10 || coloana - nrH + nrPiese < 0 ) )
                || ( directia == 8 &&  coloana - nrH + nrPiese < 0 ) )
            goto jump2;

        //int liniaB = linia, coloanaB = coloana;
        for( int i = nrPiese; i < nrH; i++ )
        {
            if( directia == 1 )
            {
                liniaB -= 1;
                coloanaB -= 1;
            }
            if( directia == 2 )
                liniaB -= 1;
            if( directia == 3 )
            {
                liniaB -= 1;
                coloanaB += 1;
            }
            if( directia == 4 )
                coloanaB += 1;
            if( directia == 5 )
            {
                liniaB += 1;
                coloanaB += 1;
            }
            if( directia == 6 )
                liniaB += 1;
            if( directia == 7 )
            {
                liniaB += 1;
                coloanaB -= 1;
            }
            if( directia == 8 )
                coloanaB -= 1;

            if( Careu[liniaB][coloanaB] == hit )
                goto jump2;
        }

jump3:
        if( linia > 0 && linia < 11 && coloana > 0 && coloana < 11 )
        {
            if( Careu[linia][coloana] != 0 && Careu[linia][coloana] != hit )
            {
                if( Careu[linia][coloana] == 4 )
                {
                    nava4P--;
                    NrOfHits++;
                    if( nava4P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 3 )
                {
                    nava3P--;
                    NrOfHits++;
                    if( nava3P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 21 )
                {
                    nava21P--;
                    NrOfHits++;
                    if( nava21P < 20  )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 22 )
                {
                    nava22P--;
                    NrOfHits++;
                    if( nava22P < 21 )
                        NrOfHits = 0;
                }
            }
            Careu[linia][coloana] = hit;
            setcolor(FUNDAL);
            setfillstyle(SOLID_FILL,FUNDAL);
            x1=stanga+latura*(coloana-1);
            y1=sus+latura*(linia-1);
            x2=x1+latura;
            y2=y1+latura;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
            line( x1+1, y1+1, x2, y2 );
            line( x1+1, y1+latura, x2, y2-latura );
            nrPiese++;
        }
        for( int i = nrPiese; i < nrH; i++ )
        {
            if( directia == 1 )
            {
                linia -= 1;
                coloana -= 1;
            }
            if( directia == 2 )
            {
                linia -= 1;
            }
            if( directia == 3 )
            {
                linia -= 1;
                coloana += 1;
            }
            if( directia == 4 )
            {
                coloana += 1;
            }
            if( directia == 5 )
            {
                linia += 1;
                coloana += 1;
            }
            if( directia == 6 )
            {
                linia += 1;
            }
            if( directia == 7 )
            {
                linia += 1;
                coloana -= 1;
            }
            if( directia == 8 )
            {
                coloana -= 1;
            }
            if( Careu[linia][coloana] == hit || linia < 1 || linia > 10 || coloana < 1 || coloana > 10 )
                goto jump_inFor;

            if( Careu[linia][coloana] != 0 )
            {
                if( Careu[linia][coloana] == 4 )
                {
                    nava4P--;
                    NrOfHits++;
                    if( nava4P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 3 )
                {
                    nava3P--;
                    NrOfHits++;
                    if( nava3P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 21 )
                {
                    nava21P--;
                    NrOfHits++;
                    if( nava21P < 20  )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 22 )
                {
                    nava22P--;
                    NrOfHits++;
                    if( nava22P < 21 )
                        NrOfHits = 0;
                }
            }
            Careu[linia][coloana] = hit;
            setcolor(FUNDAL);
            setfillstyle(SOLID_FILL,FUNDAL);
            x1=stanga+latura*(coloana-1);
            y1=sus+latura*(linia-1);
            x2=x1+latura;
            y2=y1+latura;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
            line( x1+1, y1+1, x2, y2 );
            line( x1+1, y1+latura, x2, y2-latura );
            delay( 200 );
            nrPiese++;
jump_inFor:
            ;
        }
        int liniaFin = linia, coloanaFin = coloana, liniaInc, coloanaInc;
        if( directia == 1 )
        {
            liniaInc = linia + nrPiese - 1;
            coloanaInc = coloana + nrPiese - 1;
        }
        if( directia == 2 )
        {
            liniaInc = linia + nrPiese - 1;
            coloanaInc = coloana + nrPiese - 1;
        }
        if( directia == 3 )
        {
            liniaInc = linia + nrPiese - 1;
            coloanaInc = coloana - nrPiese + 1;
        }
        if( directia == 4 )
        {
            liniaInc = linia;
            coloanaInc = coloana - nrPiese + 1;
        }
        if( directia == 5 )
        {
            liniaInc = linia - nrPiese + 1;
            coloanaInc = coloana - nrPiese + 1;
        }
        if( directia == 6 )
        {
            liniaInc = linia - nrPiese + 1;
            coloanaInc = coloana;
        }
        if( directia == 7 )
        {
            liniaInc = linia - nrPiese + 1;
            coloanaInc = coloana + nrPiese - 1;
        }
        if( directia == 8 )
        {
            liniaInc = linia;
            coloanaInc = coloana + nrPiese - 1;
        }

        int counterWhile = 0;
        while( nrPiese < nrH && counterWhile < 9 )
        {
            if( directia == 1 )
            {
                liniaFin -= 1;
                coloanaFin -= 1;
                liniaInc += 1;
                coloanaInc +=1;
            }
            if( directia == 2 )
            {
                liniaFin -= 1;
                liniaInc += 1;
            }
            if( directia == 3 )
            {
                liniaFin -= 1;
                coloanaFin += 1;
                liniaInc += 1;
                coloanaInc -= 1;
            }
            if( directia == 4 )
            {
                coloanaFin += 1;
                coloanaInc -= 1;
            }
            if( directia == 5 )
            {
                liniaFin += 1;
                coloanaFin += 1;
                liniaInc -= 1;
                coloanaInc -= 1;
            }
            if( directia == 6 )
            {
                liniaFin += 1;
                liniaInc -= 1;
            }
            if( directia == 7 )
            {
                liniaFin += 1;
                coloanaFin -= 1;
                liniaInc -= 1;
                coloanaInc += 1;
            }
            if( directia == 8 )
            {
                coloanaFin -= 1;
                coloanaInc += 1;
            }
            if( Careu[liniaFin][coloanaFin] != hit && liniaFin > 0 && liniaFin < 11 && coloanaFin < 11 && coloanaFin > 0 && nrPiese < nrH )
            {
                if( Careu[liniaFin][coloanaFin] != 0 )
                {
                    if( Careu[liniaFin][coloanaFin] == 4 )
                    {
                        nava4P--;
                        NrOfHits++;
                        if( nava4P < 1 )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaFin][coloanaFin] == 3 )
                    {
                        nava3P--;
                        NrOfHits++;
                        if( nava3P < 1 )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaFin][coloanaFin] == 21 )
                    {
                        nava21P--;
                        NrOfHits++;
                        if( nava21P < 20  )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaFin][coloanaFin] == 22 )
                    {
                        nava22P--;
                        NrOfHits++;
                        if( nava22P < 21 )
                            NrOfHits = 0;
                    }
                }
                Careu[liniaFin][coloanaFin] = hit;
                setcolor(FUNDAL);
                setfillstyle(SOLID_FILL,FUNDAL);
                x1=stanga+latura*(coloanaFin-1);
                y1=sus+latura*(liniaFin-1);
                x2=x1+latura;
                y2=y1+latura;
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,BLACK);
                line( x1+1, y1+1, x2, y2 );
                line( x1+1, y1+latura, x2, y2-latura );
                delay( 200 );
                nrPiese++;
            }
            if( Careu[liniaInc][coloanaInc] != hit && liniaInc > 0 && liniaInc < 11 && coloanaInc < 11 && coloanaInc > 0 && nrPiese < nrH )
            {
                if( Careu[liniaInc][coloanaInc] != 0 )
                {
                    if( Careu[liniaInc][coloanaInc] == 4 )
                    {
                        nava4P--;
                        NrOfHits++;
                        if( nava4P < 1 )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaInc][coloanaInc] == 3 )
                    {
                        nava3P--;
                        NrOfHits++;
                        if( nava3P < 1 )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaInc][coloanaInc] == 21 )
                    {
                        nava21P--;
                        NrOfHits++;
                        if( nava21P < 20  )
                            NrOfHits = 0;
                    }
                    if( Careu[liniaInc][coloanaInc] == 22 )
                    {
                        nava22P--;
                        NrOfHits++;
                        if( nava22P < 21 )
                            NrOfHits = 0;
                    }
                }
                Careu[liniaInc][coloanaInc] = hit;
                setcolor(FUNDAL);
                setfillstyle(SOLID_FILL,FUNDAL);
                x1=stanga+latura*(coloanaInc-1);
                y1=sus+latura*(liniaInc-1);
                x2=x1+latura;
                y2=y1+latura;
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,BLACK);
                line( x1+1, y1+1, x2, y2 );
                line( x1+1, y1+latura, x2, y2-latura );
                delay( 200 );
                nrPiese++;
            }
            counterWhile++;
        }
        if( nrPiese < nrH )
            goto jump;
        if( NrOfHits >= 2 )
            overHit++;
        nrpieseAnt = nrPiese;
    }
    // aici intra daca in atacul anterior a lovit macar una dintre navele player-ului


    else
    {
        int nrhitsAnt = nava4P + nava3P + nava21P + nava22P;
        int counterTraiectorie, counterMutare = 0, counterCapete, counterinside_loop1 = 0, counterSchimb = 0, counter_loop1 = 0;
        bool Mutare5visited = false;
        //int l2 = l, c2 = c;
        nrPiese = 0;
        directia = directiaComp;
        if( atacAnt )
        {
            linia = lAnt;
            coloana = cAnt;
            lAnt = linia;
            cAnt = coloana;
        }
        else
        {
            linia = lComp;
            coloana = cComp;
            lAnt = linia;
            cAnt = coloana;
        }
        // intra aici si trimite la salturile respective daca a lovit doua sau mai multe nave intr-un singur atac
        if( ( NrOfHits >= 2 && overHit ) || hitOver)
        {
pre_jump:
            counterCapete++;
            if( directia == 4 || directia == 8 )
            {
                if( goleftHit )
                    goto leftHit;
                else if( gorightHit )
                    goto rightHit;
            }
            else
            {
                if( gotopHit )
                    goto topHit;
                else if( gobotHit )
                    goto botHit;
            }
            hitOver = false;
        }
        if( counterMutare == 8 && counterCapete == 2 )
        {
            NrOfHits = 0;
            goto outside;
        }
        //atribuie o noua valoare liniei, respectiv coloanei, in functie de coordonatele ultimului atac
schimb:
        counterSchimb++;
        if( counterSchimb > 20 )
        {
            NrOfHits = 0;
            goto outside;
        }

        // schimba pozitia, " de la dreapta la stanga " , in caz ca nu a lovit nimic in atacul trecut - adica a intrat in else si nu a lovit nimic
        if( counterSchimbare )
        {
            if( directia == 1 )
            {
                linia = lComp + 1;
            }
            if( directia == 2 )
            {
                coloana = cComp - 1;
            }
            if( directia == 3 )
            {
                linia = lComp - 1;
            }
            if( directia == 4 )
            {
                linia = lComp - 1;
            }
            if( directia == 5 )
            {
                linia = lComp + 1;
            }
            if( directia == 6 )
            {
                coloana = cComp - 1;
            }
            if( directia == 7 )
            {
                linia = lComp - 1;
            }
            if( directia == 8 )
            {
                linia = lComp - 1;
            }
        }


        while( coloana < 1 )
            coloana++;
        while( coloana > 10 )
            coloana--;
        while( linia < 1 )
            linia++;
        while( linia > 10 )
            linia--;

loop1:
        counterTraiectorie = 1;
        // directia e stabilita, iar daca casuta de langa cea de unde a inceput atacul anterior e ocupata, atunci  va merge la urmatoare casuta, pastrand directia
        // daca toate casutele de pe directia respectiva,tinand cont de numarul de lovituri posibile, sunt ocupate, se trece la casuta la doua spatii distana de cea initiala
loop1_ins:
        counter_loop1++;
        if( counter_loop1 > 20 )
        {
            NrOfHits = 0;
            goto outside;
        }
        if( counterMutare == 5 )
        {
            if( Mutare5visited )
            {
                NrOfHits = 0;
                goto outside;
            }
            counterSchimbare++;
            Mutare5visited = true;
            goto schimb;
        }
        if( counterMutare == 8 )
            goto pre_jump;
        while( Careu[linia][coloana] == hit )
        {
            if( directia == 1 )
            {
                linia--;
                coloana--;
            }
            if( directia == 2 )
            {
                linia--;
            }
            if( directia == 3 )
            {
                linia--;
                coloana++;
            }
            if( directia == 4 )
            {
                coloana++;
            }
            if( directia == 5 )
            {
                linia++;
                coloana++;
            }
            if( directia == 6 )
            {
                linia++;
            }
            if( directia == 7 )
            {
                linia++;
                coloana--;
            }
            if( directia == 8 )
            {
                coloana--;
            }
            counterTraiectorie++;
        }


        if( counterTraiectorie > nrpieseAnt )
        {
inside_loop1:
            counterinside_loop1++;
            if( counterinside_loop1 > 20 )
            {
                NrOfHits = 0;
                goto outside;
            }
            if( !counterSchimbare )
            {
                if( directia == 1 )
                {
                    linia += nrpieseAnt;
                    coloana += ( nrpieseAnt - 1 );
                }
                if( directia == 2 )
                {
                    coloana++;
                    linia += nrpieseAnt;
                }
                if( directia == 3 )
                {
                    linia += nrpieseAnt;
                    coloana -= ( nrpieseAnt - 1 );
                }
                if( directia == 4 )
                {
                    linia++;
                    coloana -= nrpieseAnt;//6
                }
                if( directia == 5 )
                {
                    linia -= nrpieseAnt;
                    coloana -= ( nrpieseAnt - 1 );
                }
                if( directia == 6 )
                {
                    coloana++;
                    linia -= nrpieseAnt;//6
                }
                if( directia == 7 )
                {
                    linia -= nrpieseAnt;//5
                    coloana += ( nrpieseAnt - 1 );
                }
                if( directia == 8 )
                {
                    linia++;
                    coloana += nrpieseAnt;//6
                }
            }

            if( counterSchimbare )
            {
                if( directia == 1 )
                {
                    linia += nrpieseAnt;// 5
                    coloana += ( nrpieseAnt - 1 );
                }
                if( directia == 2 )
                {
                    coloana--;
                    linia += nrpieseAnt;//6
                }
                if( directia == 3 )
                {
                    linia += nrpieseAnt;//5
                    coloana -= ( nrpieseAnt - 1 );
                }
                if( directia == 4 )
                {
                    linia--;
                    coloana -= ( nrpieseAnt - 1 );
                }
                if( directia == 5 )
                {
                    linia -= nrpieseAnt;//5
                    coloana -= ( nrpieseAnt - 1 );
                }
                if( directia == 6 )
                {
                    coloana--;
                    linia -= nrpieseAnt;//6
                }
                if( directia == 7 )
                {
                    linia -= nrpieseAnt;
                    coloana += ( nrpieseAnt - 1 );
                }
                if( directia == 8 )
                {
                    linia--;
                    coloana += nrpieseAnt;//6
                }
            }
            counterMutare++;
            goto loop1;
        }

        // aici incepe computer-ul atacul propriu zis
        // ataca toate casutele disponibile( care nu au mai fost atacate ) de pe directia stabilita
        // daca a ajuns la sfarsitului "drumului" pe care trebuia sa il parcurga, insa i-au mai ramas lovituri ( de exemplu: ai 7 lovituri, deci ar trebui
        // sa lovesti de 7 ori in paralel cu atacul precedent, insa deoarece erau marcate, ai sarit peste niste casute ), atunci se va intoarce la inside_loop1,
        // unde va trece la o casuta alaturata
        if( linia < 1 || linia > 10 || coloana < 1 || coloana > 10 )
        {
            if( !adevSchimbare )
            {
                if( !counterSchimbare )
                    counterSchimbare++;
                else
                    counterSchimbare = 0;
                goto schimb;
                adevSchimbare = true;
            }
            else
            {
                goto pre_jump;
            }
        }
        if( nrPiese < nrH )
        {
            if( linia > 0 && linia < 11 && coloana > 11 && coloana > 0 )
            {
                if( Careu[linia][coloana] != hit )
                {
                    if( Careu[linia][coloana] != 0 )
                    {
                        if( Careu[linia][coloana] == 4 )
                        {
                            nava4P--;
                            NrOfHits++;
                            if( nava4P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[linia][coloana] == 3 )
                        {
                            nava3P--;
                            NrOfHits++;
                            if( nava3P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[linia][coloana] == 21 )
                        {
                            nava21P--;
                            NrOfHits++;
                            if( nava21P < 20  )
                                NrOfHits = 0;
                        }
                        if( Careu[linia][coloana] == 22 )
                        {
                            nava22P--;
                            NrOfHits++;
                            if( nava22P < 21 )
                                NrOfHits = 0;
                        }
                    }
                    Careu[linia][coloana] = hit;
                    setcolor(FUNDAL);
                    setfillstyle(SOLID_FILL,FUNDAL);
                    x1=stanga+latura*(coloana-1);
                    y1=sus+latura*(linia-1);
                    x2=x1+latura;
                    y2=y1+latura;
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    line( x1+1, y1+1, x2, y2 );
                    line( x1+1, y1+latura, x2, y2-latura );
                    nrPiese++;
                }
            }
        }
        for( int i = nrPiese; i < nrH; i++ )
        {
            if( directia == 1 )
            {
                linia -= 1;
                coloana -= 1;
            }
            if( directia == 2 )
            {
                linia -= 1;
            }
            if( directia == 3 )
            {
                linia -= 1;
                coloana += 1;
            }
            if( directia == 4 )
            {
                coloana += 1;
            }
            if( directia == 5 )
            {
                linia += 1;
                coloana += 1;
            }
            if( directia == 6 )
            {
                linia += 1;
            }
            if( directia == 7 )
            {
                linia += 1;
                coloana -= 1;
            }
            if( directia == 8 )
            {
                coloana -= 1;
            }
            if( Careu[linia][coloana] == hit || linia < 1 || linia > 10 || coloana > 10 || coloana < 1 )
                goto jump_ins;
            if( Careu[linia][coloana] != 0 )
            {
                if( Careu[linia][coloana] == 4 )
                {
                    nava4P--;
                    NrOfHits++;
                    if( nava4P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 3 )
                {
                    nava3P--;
                    NrOfHits++;
                    if( nava3P < 1 )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 21 )
                {
                    nava21P--;
                    NrOfHits++;
                    if( nava21P < 20  )
                        NrOfHits = 0;
                }
                if( Careu[linia][coloana] == 22 )
                {
                    nava22P--;
                    NrOfHits++;
                    if( nava22P < 21 )
                        NrOfHits = 0;
                }
            }
            Careu[linia][coloana] = hit;
            setcolor(FUNDAL);
            setfillstyle(SOLID_FILL,FUNDAL);
            x1=stanga+latura*(coloana-1);
            y1=sus+latura*(linia-1);
            x2=x1+latura;
            y2=y1+latura;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
            line( x1+1, y1+1, x2, y2 );
            line( x1+1, y1+latura, x2, y2-latura );
            delay( 200 );
            nrPiese++;
jump_ins:
            counterTraiectorie++;
            if( counterTraiectorie > nrpieseAnt )
                goto inside_loop1;
        }
        if( nrPiese < nrH )
            goto inside_loop1;
        // verifica daca a lovit macar o nava
        if( nrhitsAnt == ( nava4P + nava3P + nava21P + nava22P ) )
        {
            if( counterTraiectorie < nrpieseAnt )
            {
                lAnt = linia;
                cAnt = coloana;
            }
            else if( !adevSchimbare )
            {
                if( !counterSchimbare )
                    counterSchimbare++;
                else
                    counterSchimbare = 0;
                adevSchimbare = true;
            }
            else
            {
                hitOver = true;
            }
            atacAnt = false;
        }
        else
            atacAnt = true;
        if( nrhitsAnt - 2 >= nava4P + nava3P + nava21P + nava22P )
            overHit++;
        else
            overHit = 0;


        // pentru directiile 1, 2, 3, 5, 6, 7, loveste pozitiile valabile de la " capatul " de sus al atacului precedent
        // acelasi principiu se aplica si pentru capatul de jos, botHit, in cazul in care nu a gasit nimic in cel de sus
        // acelasi lucru ca si pentru capetele de sus si de jos, doar ca aplicat pentru laterale, este in leftHit si rightHit
        // functiile astea sunt mai simple deci ai putea sa te uiti peste ele intai ca sa intelegi
        if( gotopHit == 10 )
        {
topHit:
            {
                if( directia == 1 )
                {
                    linia = lAnt - nrpieseAnt;
                    coloana = cAnt - nrpieseAnt + 1;
                }
                if( directia == 2 )
                {
                    linia = lAnt - nrpieseAnt;
                    coloana = cAnt;
                }
                if( directia == 3 )
                {
                    linia = lAnt - nrpieseAnt;
                    coloana = cAnt + nrpieseAnt - 1;
                }
                if( directia == 5 )
                {
                    linia = lAnt - 1;
                    coloana = cAnt;
                }
                if( directia == 6 )
                {
                    linia = lAnt - 1;
                    coloana = cAnt;
                }
                if( directia == 7 )
                {
                    linia = lAnt - 1;
                    coloana = cAnt;
                }
                if( linia < 1 || linia > 10 || coloana < 1 || coloana > 10  || ( Careu[linia][coloana - 1] + Careu[linia][coloana] + Careu[linia][coloana + 1] == 3 * hit ) )
                {
                    gotopHit--;
                    goto pre_jump;
                }
                int i, k;
                for( i = linia - 1; i <= linia; i++ )
                    for( k = coloana - 1; k <= coloana + 1; k++ )
                    {
                        if( i > 0 && i < 11 && k > 0 && k < 11 )
                            if( Careu[i][k] != hit )
                            {
                                if( Careu[i][k] != 0 )
                                {
                                    if( Careu[i][k] == 4 )
                                    {
                                        nava4P--;
                                        NrOfHits++;
                                        if( nava4P < 1 )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 3 )
                                    {
                                        nava3P--;
                                        NrOfHits++;
                                        if( nava3P < 1 )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 21 )
                                    {
                                        nava21P--;
                                        NrOfHits++;
                                        if( nava21P < 20  )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 22 )
                                    {
                                        nava22P--;
                                        NrOfHits++;
                                        if( nava22P < 21 )
                                            NrOfHits = 0;
                                    }
                                }
                                Careu[i][k] = hit;
                                setcolor(FUNDAL);
                                setfillstyle(SOLID_FILL,FUNDAL);
                                x1=stanga+latura*(k-1);
                                y1=sus+latura*(i-1);
                                x2=x1+latura;
                                y2=y1+latura;
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL,BLACK);
                                line( x1+1, y1+1, x2, y2 );
                                line( x1+1, y1+latura, x2, y2-latura );
                                delay( 200 );
                                nrPiese++;
                            }
                    }
                int iSt = 1, kSt = 1, iiSt = 1, kkSt = 1;
                int iDr = 1, kDr = 1, iiDr = 1, kkDr = 1;
                while( nrPiese < nrH )
                {
                    if( Careu[linia + iSt][coloana - kSt] != hit && linia + iSt > 0 && linia + iSt < 11 && coloana - kSt < 11 && coloana - kSt > 0 && nrPiese < nrH )
                    {
                        if( Careu[linia + iSt][coloana - kSt] != 0 )
                        {
                            if( Careu[linia + iSt][coloana - kSt] == 4 )
                            {
                                nava4P--;
                                NrOfHits++;
                                if( nava4P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iSt][coloana - kSt] == 3 )
                            {
                                nava3P--;
                                NrOfHits++;
                                if( nava3P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iSt][coloana - kSt] == 21 )
                            {
                                nava21P--;
                                NrOfHits++;
                                if( nava21P < 20  )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iSt][coloana - kSt] == 22 )
                            {
                                nava22P--;
                                NrOfHits++;
                                if( nava22P < 21 )
                                    NrOfHits = 0;
                            }
                        }
                        Careu[linia + iSt][coloana - kSt] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(coloana - kSt - 1 );
                        y1=sus+latura*(linia + iSt - 1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( Careu[linia + iDr][coloana + kDr] != hit && linia + iDr > 0 && linia + iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0  && nrPiese < nrH )
                    {
                        if( Careu[linia + iDr][coloana + kDr] != 0 )
                        {
                            if( Careu[linia + iDr][coloana + kDr] == 4 )
                            {
                                nava4P--;
                                NrOfHits++;
                                if( nava4P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iDr][coloana + kDr] == 3 )
                            {
                                nava3P--;
                                NrOfHits++;
                                if( nava3P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iDr][coloana + kDr] == 21 )
                            {
                                nava21P--;
                                NrOfHits++;
                                if( nava21P < 20  )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia + iDr][coloana + kDr] == 22 )
                            {
                                nava22P--;
                                NrOfHits++;
                                if( nava22P < 21 )
                                    NrOfHits = 0;
                            }
                        }
                        Careu[linia + iDr][coloana + kDr] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(coloana + kDr - 1 );
                        y1=sus+latura*(linia + iDr - 1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( directia == 1 || directia == 5)
                    {
                        iSt = iiSt + 1;
                        kSt = kkSt + 1;
                        iiSt = iSt;
                        kkSt = kSt;
                        while( Careu[linia + iSt][coloana - kSt] == hit && linia + iSt > 0 && linia + iSt < 11 && coloana - kSt < 11 && coloana + kSt > 0 )
                            kSt--;
                        iDr = iiDr + 1;
                        kDr = kkDr - 1;
                        iiDr = iDr;
                        kkDr = kDr;
                        while( Careu[linia + iDr][coloana + kDr] == hit && linia + iDr > 0 && linia + iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 )
                            kDr++;
                    }
                    if( directia == 2 || directia == 6 )
                    {
                        iSt = iiSt + 1;
                        kSt = kkSt;
                        iiSt = iSt;
                        while( Careu[linia + iSt][coloana - kSt] == hit && linia + iSt > 0 && linia + iSt < 11 && coloana - kSt < 11 && coloana + kSt > 0 )
                            kSt++;
                        iDr = iiDr + 1;
                        kDr = kkDr;
                        iiDr = iDr;
                        while( Careu[linia + iDr][coloana + kDr] == hit && linia + iDr > 0 && linia + iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 )
                            kDr++;
                    }
                    if( directia == 3 || directia == 7)
                    {
                        iSt = iiSt + 1;
                        kSt = kkSt + 1;
                        iiSt = iSt;
                        kkSt = kSt;
                        while( Careu[linia + iSt][coloana - kSt] == hit && linia + iSt > 0 && linia + iSt < 11 && coloana - kSt < 11 && coloana + kSt > 0 )
                            kSt++;
                        iDr = iiDr + 1;
                        kDr = kkDr - 1;
                        iiDr = iDr;
                        kkDr = kDr;
                        while( Careu[linia + iDr][coloana + kDr] == hit && linia + iDr > 0 && linia + iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 )
                            kDr++;
                    }

                }
                gotopHit--;
            }//topHit end
        }
        if( gobotHit == 10 )
        {
botHit:
            {
                if( directia == 1 )
                {
                    linia = lAnt + 1;
                    coloana = cAnt;
                }
                if( directia == 2 )
                {
                    linia = lAnt + 1;
                    coloana = cAnt;
                }
                if( directia == 3 )
                {
                    linia = lAnt + 1;
                    coloana = cAnt;
                }
                if( directia == 5 )
                {
                    linia = lAnt + nrpieseAnt;
                    coloana = cAnt + nrpieseAnt - 1;
                }
                if( directia == 6 )
                {
                    linia = lAnt + nrpieseAnt;
                    coloana = cAnt;
                }
                if( directia == 7 )
                {
                    linia = lAnt + nrpieseAnt;
                    coloana = cAnt - nrpieseAnt + 1;
                }
                if( linia < 1 || linia > 10 || coloana < 1 || coloana > 10 || ( Careu[linia][coloana - 1] + Careu[linia][coloana] + Careu[linia+1][coloana + 1] == 3 * hit) )
                {
                    gobotHit--;
                    goto pre_jump;
                }
                int i, k;
                for( i = linia + 1; i >= linia; i-- )
                    for( k = coloana - 1; k <= coloana + 1; k++ )
                    {
                        if( i > 0 && i < 11 && k > 0 && k < 11 )
                            if( Careu[i][k] != hit )
                            {
                                if( Careu[i][k] != 0 )
                                {
                                    if( Careu[i][k] == 4 )
                                    {
                                        nava4P--;
                                        NrOfHits++;
                                        if( nava4P < 1 )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 3 )
                                    {
                                        nava3P--;
                                        NrOfHits++;
                                        if( nava3P < 1 )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 21 )
                                    {
                                        nava21P--;
                                        NrOfHits++;
                                        if( nava21P < 20  )
                                            NrOfHits = 0;
                                    }
                                    if( Careu[i][k] == 22 )
                                    {
                                        nava22P--;
                                        NrOfHits++;
                                        if( nava22P < 21 )
                                            NrOfHits = 0;
                                    }
                                }
                                Careu[i][k] = hit;
                                setcolor(FUNDAL);
                                setfillstyle(SOLID_FILL,FUNDAL);
                                x1=stanga+latura*(k-1);
                                y1=sus+latura*(i-1);
                                x2=x1+latura;
                                y2=y1+latura;
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL,BLACK);
                                line( x1+1, y1+1, x2, y2 );
                                line( x1+1, y1+latura, x2, y2-latura );
                                delay( 200 );
                                nrPiese++;
                            }
                    }
                int iSt = 1, kSt = 1, iiSt = 1, kkSt = 1;
                int iDr = 1, kDr = 1, iiDr = 1, kkDr = 1;
                while( nrPiese < nrH )
                {
                    if( Careu[linia - iSt][coloana - kSt] != hit && linia - iSt > 0 && linia - iSt < 11 && coloana - kSt < 11 && coloana - kSt > 0 && nrPiese < nrH )
                    {
                        if( Careu[linia - iSt][coloana - kSt] != 0 )
                        {
                            if( Careu[linia - iSt][coloana - kSt] == 4 )
                            {
                                nava4P--;
                                NrOfHits++;
                                if( nava4P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iSt][coloana - kSt] == 3 )
                            {
                                nava3P--;
                                NrOfHits++;
                                if( nava3P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iSt][coloana - kSt] == 21 )
                            {
                                nava21P--;
                                NrOfHits++;
                                if( nava21P < 20  )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iSt][coloana - kSt] == 22 )
                            {
                                nava22P--;
                                NrOfHits++;
                                if( nava22P < 21 )
                                    NrOfHits = 0;
                            }
                        }
                        Careu[linia - iSt][coloana - kSt] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(coloana - kSt - 1 );
                        y1=sus+latura*(linia - iSt - 1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( Careu[linia - iDr][coloana + kDr] != hit && linia - iDr > 0 && linia - iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 && nrPiese < nrH )
                    {
                        if( Careu[linia - iDr][coloana + kDr] != 0 )
                        {
                            if( Careu[linia - iDr][coloana + kDr] == 4 )
                            {
                                nava4P--;
                                NrOfHits++;
                                if( nava4P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iDr][coloana + kDr] == 3 )
                            {
                                nava3P--;
                                NrOfHits++;
                                if( nava3P < 1 )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iDr][coloana + kDr] == 21 )
                            {
                                nava21P--;
                                NrOfHits++;
                                if( nava21P < 20  )
                                    NrOfHits = 0;
                            }
                            if( Careu[linia - iDr][coloana + kDr] == 22 )
                            {
                                nava22P--;
                                NrOfHits++;
                                if( nava22P < 21 )
                                    NrOfHits = 0;
                            }
                        }
                        Careu[linia - iDr][coloana + kDr] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(coloana + kDr - 1 );
                        y1=sus+latura*(linia - iDr - 1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( directia == 5 || directia == 1 )
                    {
                        iSt = iiSt - 1;
                        kSt = kkSt + 1;
                        iiSt = iSt;
                        kkSt = kSt;
                        while( Careu[linia - iSt][coloana - kSt] == hit && linia - iSt> 0 && linia - iSt < 11 && coloana - kSt < 11 && coloana - kSt > 0 )
                            kSt--;
                        iDr = iiDr - 1;
                        kDr = kkDr - 1;
                        iiDr = iDr;
                        kkDr = kDr;
                        while( Careu[linia - iDr][coloana + kDr] == hit && linia - iDr > 0 && linia - iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 )
                            kDr++;
                    }
                    if( directia == 6 || directia == 2)
                    {
                        iSt = iiSt - 1;
                        iiSt = iSt;
                        kSt = kkSt;
                        while( Careu[linia - iSt][coloana - kSt] == hit && linia - iSt> 0 && linia - iSt < 11 && coloana - kSt < 11 && coloana - kSt > 0 )
                            kSt++;
                        iDr = iiDr - 1;
                        iiDr = iDr;
                        kDr = kkDr;
                        while( Careu[linia - iDr][coloana + kDr] == hit && linia - iDr > 0 && linia - iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0)
                            kDr++;
                    }
                    if( directia == 7 || directia == 3)
                    {
                        iSt = iiSt - 1;
                        kSt = kkSt - 1;
                        iiSt = iSt;
                        kkSt = kSt;
                        while( Careu[linia - iSt][coloana - kSt] == hit && linia - iSt > 0 && linia - iSt < 11 && coloana - kSt < 11 && coloana - kSt > 0)
                            kSt++;
                        iDr = iiDr - 1;
                        kDr = kkDr + 1;
                        iiDr = iDr;
                        kkDr = kDr;
                        while( Careu[linia - iDr][coloana + kDr] == hit && linia - iDr > 0 && linia - iDr < 11 && coloana + kDr < 11 && coloana + kDr > 0 )
                            kDr++;
                    }

                }
                gobotHit--;
            }//botHit end
        }
        if( goleftHit == 10 )
        {
leftHit:
            {
                // seteaza coordonatele de baza pentru inceput - la capatul liniei atacului precedent
                // daca se afla in afara, atunci se va intoarce si va intra in cealalta functie - rightHit
                if( directia == 4 )
                {
                    linia = lAnt;
                    coloana = cAnt - 1;
                }
                if( directia == 8 )
                {
                    linia = lAnt;
                    coloana = cAnt - nrpieseAnt;
                }
                if( linia < 1 || linia > 10 || coloana < 1 || coloana > 10 || ( Careu[linia-1][coloana] + Careu[linia][coloana] + Careu[linia+1][coloana] == 3 * hit) )
                {
                    goleftHit--;
                    goto pre_jump;
                }
                // incepand din stanga sus, intr-un dreptunghi pe 3 linii si 2 coloane, ataca toate casutele nemarcate
                int i, k;
                for( i = linia - 1; i <= linia + 1; i++ )
                    for( k = coloana - 1; k <= coloana; k++ )
                    {
                        if( i > 0 && i < 11 && k > 0 && k < 11 )
                            if( Careu[i][k] != hit )
                            {
                                if( Careu[i][k] == 4 )
                                {
                                    nava4P--;
                                    NrOfHits++;
                                    if( nava4P < 1 )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 3 )
                                {
                                    nava3P--;
                                    NrOfHits++;
                                    if( nava3P < 1 )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 21 )
                                {
                                    nava21P--;
                                    NrOfHits++;
                                    if( nava21P < 20  )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 22 )
                                {
                                    nava22P--;
                                    NrOfHits++;
                                    if( nava22P < 21 )
                                        NrOfHits = 0;
                                }
                                Careu[i][k] = hit;
                                setcolor(FUNDAL);
                                setfillstyle(SOLID_FILL,FUNDAL);
                                x1=stanga+latura*(k-1);
                                y1=sus+latura*(i-1);
                                x2=x1+latura;
                                y2=y1+latura;
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL,BLACK);
                                line( x1+1, y1+1, x2, y2 );
                                line( x1+1, y1+latura, x2, y2-latura );
                                delay( 200 );
                                nrPiese++;
                            }
                    }
                // cu atacurile ramase, daca sunt, va incepe sa mearga pe casutele alaturate, disponibile, liniei atacului precedent
                // aici sunt indici folositi pentru a tine cont de pozitia curenta si pozitia precedenta a ultimei casute atacate
                // de asemeni sunt folositi pentru a stabili urmatoarea tina
                int iTp = linia - 1, kTp = coloana + 1, iiTp = iTp, kkTp = kTp;
                int iBt = linia + 1, kBt = coloana + 1, iiBt = iBt, kkBt = kBt;
                while( nrPiese < nrH )
                {
                    if( Careu[iTp][kTp] != hit && iTp >0 && iTp < 11 && kTp > 0 && kTp < 11 && nrPiese<nrH )
                    {
                        if( Careu[iTp][kTp] == 4 )
                        {
                            nava4P--;
                            NrOfHits++;
                            if( nava4P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 3 )
                        {
                            nava3P--;
                            NrOfHits++;
                            if( nava3P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 21 )
                        {
                            nava21P--;
                            NrOfHits++;
                            if( nava21P < 20  )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 22 )
                        {
                            nava22P--;
                            NrOfHits++;
                            if( nava22P < 21 )
                                NrOfHits = 0;
                        }
                        Careu[iTp][kTp] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(kTp-1);
                        y1=sus+latura*(iTp-1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( Careu[iBt][kBt] != hit && iBt > 0 && iBt < 11 && kBt < 11 && kBt > 0 && nrPiese < nrH )
                    {
                        if( Careu[iBt][kBt] == 4 )
                        {
                            nava4P--;
                            NrOfHits++;
                            if( nava4P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 3 )
                        {
                            nava3P--;
                            NrOfHits++;
                            if( nava3P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 21 )
                        {
                            nava21P--;
                            NrOfHits++;
                            if( nava21P < 20  )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 22 )
                        {
                            nava22P--;
                            NrOfHits++;
                            if( nava22P < 21 )
                                NrOfHits = 0;
                        }
                        Careu[iBt][kBt] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(kBt-1);
                        y1=sus+latura*(iBt-1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    iTp = iiTp;
                    kTp = kkTp + 1;
                    kkTp = kTp;
                    while( Careu[iTp][kTp] == hit && iTp > 0 && iTp < 11 && kTp < 11 && kTp > 0 )
                        iTp--;
                    iBt = iiBt;
                    kBt = kkBt + 1;
                    kkBt = kBt;
                    while( Careu[iBt][kBt] == hit && iBt > 0 && iBt < 11 && kBt < 11 && kBt > 0 )
                        iBt++;
                }
                goleftHit--;
            }// leftHit end
        }
        if( gorightHit == 10 )
        {
rightHit:
            {
                if( directia == 4 )
                {
                    linia = lAnt;
                    coloana = cComp + nrpieseAnt;
                }
                if( directia == 8 )
                {
                    linia = lAnt;
                    coloana = cAnt +1;
                }
                if( linia < 1 || linia > 10 || coloana < 1 || coloana > 10 || ( Careu[linia-1][coloana] + Careu[linia][coloana] + Careu[linia+1][coloana] == 3 * hit) )
                {
                    gorightHit--;
                    goto pre_jump;
                }
                int i, k;
                for( i = linia - 1; i <= linia + 1; i++ )
                    for( k = coloana; k <= coloana + 1; k++ )
                    {
                        if( i > 0 && i < 11 && k > 0 && k < 11 )
                            if( Careu[i][k] != hit )
                            {
                                if( Careu[i][k] == 4 )
                                {
                                    nava4P--;
                                    NrOfHits++;
                                    if( nava4P < 1 )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 3 )
                                {
                                    nava3P--;
                                    NrOfHits++;
                                    if( nava3P < 1 )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 21 )
                                {
                                    nava21P--;
                                    NrOfHits++;
                                    if( nava21P < 20  )
                                        NrOfHits = 0;
                                }
                                if( Careu[i][k] == 22 )
                                {
                                    nava22P--;
                                    NrOfHits++;
                                    if( nava22P < 21 )
                                        NrOfHits = 0;
                                }
                                Careu[i][k] = hit;
                                setcolor(FUNDAL);
                                setfillstyle(SOLID_FILL,FUNDAL);
                                x1=stanga+latura*(k-1);
                                y1=sus+latura*(i-1);
                                x2=x1+latura;
                                y2=y1+latura;
                                setcolor(BLACK);
                                setfillstyle(SOLID_FILL,BLACK);
                                line( x1+1, y1+1, x2, y2 );
                                line( x1+1, y1+latura, x2, y2-latura );
                                delay( 200 );
                                nrPiese++;
                            }
                    }
                int iTp = linia - 1, kTp = coloana - 1, iiTp = iTp, kkTp = kTp;
                int iBt = linia + 1, kBt = coloana - 1, iiBt = iBt, kkBt = kBt;
                while( nrPiese < nrH )
                {
                    if( Careu[iTp][kTp] != hit && iTp >0 && iTp < 11 && kTp > 0 && kTp < 11 && nrPiese<nrH )
                    {
                        if( Careu[iTp][kTp] == 4 )
                        {
                            nava4P--;
                            NrOfHits++;
                            if( nava4P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 3 )
                        {
                            nava3P--;
                            NrOfHits++;
                            if( nava3P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 21 )
                        {
                            nava21P--;
                            NrOfHits++;
                            if( nava21P < 20  )
                                NrOfHits = 0;
                        }
                        if( Careu[iTp][kTp] == 22 )
                        {
                            nava22P--;
                            NrOfHits++;
                            if( nava22P < 21 )
                                NrOfHits = 0;
                        }
                        Careu[iTp][kTp] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(kTp-1);
                        y1=sus+latura*(iTp-1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    if( Careu[iBt][kBt] != hit && iBt > 0 && iBt < 11 && kBt < 11 && kBt > 0 && nrPiese < nrH )
                    {
                        if( Careu[iBt][kBt] == 4 )
                        {
                            nava4P--;
                            NrOfHits++;
                            if( nava4P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 3 )
                        {
                            nava3P--;
                            NrOfHits++;
                            if( nava3P < 1 )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 21 )
                        {
                            nava21P--;
                            NrOfHits++;
                            if( nava21P < 20  )
                                NrOfHits = 0;
                        }
                        if( Careu[iBt][kBt] == 22 )
                        {
                            nava22P--;
                            NrOfHits++;
                            if( nava22P < 21 )
                                NrOfHits = 0;
                        }
                        Careu[iBt][kBt] = hit;
                        setcolor(FUNDAL);
                        setfillstyle(SOLID_FILL,FUNDAL);
                        x1=stanga+latura*(kBt-1);
                        y1=sus+latura*(iBt-1);
                        x2=x1+latura;
                        y2=y1+latura;
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,BLACK);
                        line( x1+1, y1+1, x2, y2 );
                        line( x1+1, y1+latura, x2, y2-latura );
                        delay( 200 );
                        nrPiese++;
                    }
                    iTp = iiTp;
                    kTp = kkTp - 1;
                    kkTp = kTp;
                    while( Careu[iTp][kTp] == hit && iBt > 0 && iBt < 11 && kBt < 11 && kBt > 0 )
                        iTp--;
                    iBt = iiBt;
                    kBt = kkBt - 1;
                    kkBt = kBt;
                    while( Careu[iBt][kBt] == hit && iBt > 0 && iBt < 11 && kBt < 11 && kBt > 0 )
                        iBt++;
                }
                gorightHit--;
            }//rightHit end
        }
    }
    //nrpieseAnt = nrPiese;
}

void pushDirectionsToStack(stack<pair<int, int>> &s, int linia, int coloana)
{
    ///sus
    if (linia > 1 && TablaDeJoc[linia - 1][coloana] != hit)
        s.push(make_pair(linia - 1, coloana));

    ///dreapta
    if (coloana < 10 && TablaDeJoc[linia][coloana + 1] != hit)
        s.push(make_pair(linia, coloana + 1));

    ///jos
    if (linia < 10 && TablaDeJoc[linia + 1][coloana] != hit)
        s.push(make_pair(linia + 1, coloana));

    ///stanga
    if (coloana > 1 && TablaDeJoc[linia][coloana - 1] != hit)
        s.push(make_pair(linia, coloana - 1));
}

stack<pair<int, int>> lovituri;

int matriceProbabilitati[11][11];

void initializeazaMatriceProbabilitati()
{
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            matriceProbabilitati[i][j] = 0;
}

void genereazaMatriceProbabilitati()
{
    initializeazaMatriceProbabilitati();

    if (nava4P != 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                if (TablaDeJoc[i][j] != miss && TablaDeJoc[i][j+1] != miss && TablaDeJoc[i][j+2] != miss && TablaDeJoc[i][j+3] != miss)
                {
                    if (TablaDeJoc[i][j] != hit)
                    {
                        matriceProbabilitati[i][j]++;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j] += 20;

                        if (TablaDeJoc[i][j+2] == hit)
                            matriceProbabilitati[i][j] += 20;

                        if (TablaDeJoc[i][j+3] == hit)
                            matriceProbabilitati[i][j] += 20;
                    }

                    if (TablaDeJoc[i][j+1] != hit)
                    {
                        matriceProbabilitati[i][j+1]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+1] += 20;

                        if (TablaDeJoc[i][j+2] == hit)
                            matriceProbabilitati[i][j+1] += 20;

                        if (TablaDeJoc[i][j+3] == hit)
                            matriceProbabilitati[i][j+1] += 20;
                    }

                    if (TablaDeJoc[i][j+2] != hit)
                    {
                        matriceProbabilitati[i][j+2]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+2] += 20;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j+2] += 20;

                        if (TablaDeJoc[i][j+3] == hit)
                            matriceProbabilitati[i][j+2] += 20;

                    }

                    if (TablaDeJoc[i][j+3] != hit)
                    {
                        matriceProbabilitati[i][j+3]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+3] += 20;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j+3] += 20;

                        if (TablaDeJoc[i][j+2] == hit)
                            matriceProbabilitati[i][j+3] += 20;
                    }
                }

                if (TablaDeJoc[j][i] != miss && TablaDeJoc[j+1][i] != miss && TablaDeJoc[j+2][i] != miss && TablaDeJoc[j+3][i] != miss)
                {
                    if (TablaDeJoc[j][i] != hit)
                    {
                        matriceProbabilitati[j][i]++;

                        if (TablaDeJoc[j][i+1] == hit)
                            matriceProbabilitati[j][i] += 20;

                        if (TablaDeJoc[j][i+2] == hit)
                            matriceProbabilitati[j][i] += 20;

                        if (TablaDeJoc[j][i+3] == hit)
                            matriceProbabilitati[j][i] += 20;
                    }

                    if (TablaDeJoc[j+1][i] != hit)
                    {
                        matriceProbabilitati[j+1][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+1][i] += 20;

                        if (TablaDeJoc[j][i+2] == hit)
                            matriceProbabilitati[j+1][i] += 20;

                        if (TablaDeJoc[j][i+3] == hit)
                            matriceProbabilitati[j+1][i] += 20;
                    }

                    if (TablaDeJoc[j+2][i] != hit)
                    {
                        matriceProbabilitati[j+2][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+2][i] += 20;

                        if (TablaDeJoc[j][i+1] == hit)
                            matriceProbabilitati[j+2][i] += 20;

                        if (TablaDeJoc[j][i+3] == hit)
                            matriceProbabilitati[j+2][i] += 20;
                    }

                    if (TablaDeJoc[j+3][i] != hit)
                    {
                        matriceProbabilitati[j+3][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+3][i] += 20;

                        if (TablaDeJoc[j][i+1] == hit)
                            matriceProbabilitati[j+3][i] += 20;

                        if (TablaDeJoc[j][i+2] == hit)
                            matriceProbabilitati[j+3][i] += 20;
                    }
                }
            }
        }
    }

    if (nava3P != 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 8; j++)
            {
                if (TablaDeJoc[i][j] != miss && TablaDeJoc[i][j+1] != miss && TablaDeJoc[i][j+2] != miss)
                {
                    if (TablaDeJoc[i][j] != hit)
                    {
                        matriceProbabilitati[i][j]++;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j] += 20;

                        if (TablaDeJoc[i][j+2] == hit)
                            matriceProbabilitati[i][j] += 20;
                    }

                    if (TablaDeJoc[i][j+1] != hit)
                    {
                        matriceProbabilitati[i][j+1]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+1] += 20;

                        if (TablaDeJoc[i][j+2] == hit)
                            matriceProbabilitati[i][j+1] += 20;
                    }

                    if (TablaDeJoc[i][j+2] != hit)
                    {
                        matriceProbabilitati[i][j+2]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+2] += 20;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j+2] += 20;
                    }
                }

                if (TablaDeJoc[j][i] != miss && TablaDeJoc[j+1][i] != miss && TablaDeJoc[j+2][i] != miss)
                {
                    if (TablaDeJoc[j][i] != hit)
                    {
                        matriceProbabilitati[j][i]++;

                        if (TablaDeJoc[j+1][i] == hit)
                            matriceProbabilitati[j][i] += 20;

                        if (TablaDeJoc[j+2][i] == hit)
                            matriceProbabilitati[j][i] += 20;
                    }

                    if (TablaDeJoc[j+1][i] != hit)
                    {
                        matriceProbabilitati[j+1][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+1][i] += 20;

                        if (TablaDeJoc[j+2][i] == hit)
                            matriceProbabilitati[j+2][i] += 20;
                    }

                    if (TablaDeJoc[j+2][i] != hit)
                    {
                        matriceProbabilitati[j+2][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+2][i] += 20;

                        if (TablaDeJoc[j+1][i] == hit)
                            matriceProbabilitati[j+2][i] += 20;
                    }
                }
            }
        }
    }

    if (nava21P >19 || nava22P > 20 )
    {
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (TablaDeJoc[i][j] != miss && TablaDeJoc[i][j+1] != miss)
                {
                    if (TablaDeJoc[i][j] != hit)
                    {
                        matriceProbabilitati[i][j]++;

                        if (TablaDeJoc[i][j+1] == hit)
                            matriceProbabilitati[i][j] += 20;
                    }

                    if (TablaDeJoc[i][j+1] != hit)
                    {
                        matriceProbabilitati[i][j+1]++;

                        if (TablaDeJoc[i][j] == hit)
                            matriceProbabilitati[i][j+1] += 20;
                    }
                }

                if (TablaDeJoc[j][i] != miss && TablaDeJoc[j+1][i] != miss)
                {
                    if (TablaDeJoc[j][i] != hit)
                    {
                        matriceProbabilitati[j][i]++;

                        if (TablaDeJoc[j+1][i] == hit)
                            matriceProbabilitati[j][i] += 20;
                    }

                    if (TablaDeJoc[j+1][i] != hit)
                    {
                        matriceProbabilitati[j+1][i]++;

                        if (TablaDeJoc[j][i] == hit)
                            matriceProbabilitati[j+1][i] += 20;
                    }
                }
            }
        }
    }
}

int probabilitateMaxima()
{
    int maxim = 0;

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (matriceProbabilitati[i][j] > maxim)
                maxim = matriceProbabilitati[i][j];

    return maxim;
}

pair<int, int> randomProbMax(int val)
{
    pair<int, int> arrayToPick[100];
    int n = 0;

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (matriceProbabilitati[i][j] == val)
                arrayToPick[++n] = make_pair(i, j);

    srand(time(NULL));

    int pick = rand() % n + 1;

    return arrayToPick[pick];
}

stack<pair<int, int>> lovituriBackup;

void salveCalculator1()
{
    genereazaMatriceProbabilitati();

    pair<int, int> hits = randomProbMax(probabilitateMaxima());

    int hitI = hits.first;
    int hitJ = hits.second;

    if (TablaDeJoc[hitI][hitJ] != 0)
    {
        if (TablaDeJoc[hitI][hitJ] == 4)
            nava4P--;
        if (TablaDeJoc[hitI][hitJ] == 3)
            nava3P--;
        if (TablaDeJoc[hitI][hitJ] == 21)
            nava21P--;
        if (TablaDeJoc[hitI][hitJ] == 22)
            nava22P--;

        TablaDeJoc[hitI][hitJ] = hit;

        lovituri.push(make_pair(hitI, hitJ));
    }
    else
        TablaDeJoc[hitI][hitJ] = miss;

    if (prevNava4P != 0 && nava4P == 0)
    {
        while (!lovituri.empty())
        {
            if (copieTablaDeJoc[lovituri.top().first][lovituri.top().second] == 4)
                TablaDeJoc[lovituri.top().first][lovituri.top().second] = miss;
            else
                lovituriBackup.push(lovituri.top());

            lovituri.pop();
        }
        while (!lovituriBackup.empty())
        {
            lovituri.push(lovituriBackup.top());
            lovituriBackup.pop();
        }
    }

    if (prevNava3P != 0 && nava3P == 0)
    {
        while (!lovituri.empty())
        {
            if (copieTablaDeJoc[lovituri.top().first][lovituri.top().second] == 3)
                TablaDeJoc[lovituri.top().first][lovituri.top().second] = miss;
            else
                lovituriBackup.push(lovituri.top());

            lovituri.pop();
        }
        while (!lovituriBackup.empty())
        {
            lovituri.push(lovituriBackup.top());
            lovituriBackup.pop();
        }
    }

    if (prevNava21P != 19 && nava21P == 19)
    {
        while (!lovituri.empty())
        {
            if (copieTablaDeJoc[lovituri.top().first][lovituri.top().second] == 21)
                TablaDeJoc[lovituri.top().first][lovituri.top().second] = miss;
            else
                lovituriBackup.push(lovituri.top());

            lovituri.pop();
        }
        while (!lovituriBackup.empty())
        {
            lovituri.push(lovituriBackup.top());
            lovituriBackup.pop();
        }
    }

    if (prevNava22P != 20 && nava22P == 20)
    {
        while (!lovituri.empty())
        {
            if (copieTablaDeJoc[lovituri.top().first][lovituri.top().second] == 22)
                TablaDeJoc[lovituri.top().first][lovituri.top().second] = miss;
            else
                lovituriBackup.push(lovituri.top());

            lovituri.pop();
        }
        while (!lovituriBackup.empty())
        {
            lovituri.push(lovituriBackup.top());
            lovituriBackup.pop();
        }
    }

    int x1=stanga+latura*(hitJ-1);
    int y1=sus+latura*(hitI-1);
    line (x1, y1, x1 + latura, y1 + latura);
    line (x1 + latura, y1, x1, y1 + latura);
}

void initButon(buton& b, char text0[MAX], int x0, int y0, int m0)
{
    strcpy(b.text,text0);
    b.x=x0;
    b.y=y0;
    b.marime=m0;
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,b.marime);
    b.x1=x0-textwidth(b.text)/2-5;
    b.x2=x0+textwidth(b.text)/2+5;
    b.y1=y0-textheight(b.text)/2-5;;
    b.y2=y0+textheight(b.text)/2+5;
}

void deseneazaButon(buton b)
{
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, b.marime);
    setcolor(RED);
    setfillstyle(SOLID_FILL,RED);
    bar(b.x1,b.y1,b.x2,b.y2);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setbkcolor(RED);
    setcolor(BLACK);
    outtextxy((b.x1+b.x2)/2,(b.y1+b.y2)/2 + 10,b.text);
    setcolor(WHITE);
    line(b.x1-1,b.y1-1,b.x2-1,b.y1-1);
    line(b.x1-1,b.y1-1,b.x1-1,b.y2-1);
    setcolor(RED);
    line(b.x1+1,b.y2+1,b.x2+1,b.y2+1);
    line(b.x2+1,b.y1+1,b.x2+1,b.y2+1);
}

void titlescreen( int x1, int y1, int x2, int y2, char text[MAX], int m_text )
{
    setfillstyle(EMPTY_FILL, BLACK);
    bar( x1, y1, x2, y2 );
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if( m_text < 9 )
        setcolor(WHITE);
    else
    {
        setcolor(BLUE);
        m_text = 7;
    }
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, m_text);
    outtextxy( ( x1 + x2 ) / 2, ( y1 + y2 ) / 2, text);
}

void instructiuni( int x1, int y1, int x2, int y2, char text[1000], int m_text )
{
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, m_text );
    setfillstyle( EMPTY_FILL, BLACK );
    bar( x1, y1, x2, y2 );
    settextjustify( BOTTOM_TEXT, CENTER_TEXT );
    setcolor( WHITE );
    outtextxy( x1 + 10, y1 + 30, text );
    setlinestyle( SOLID_LINE, 0, 3 );
    setcolor( RED );
    line( x1, y1, x2 - 5, y1 );
    line( x1, y1, x1, y2 - 5 );
    setlinestyle( SOLID_LINE, 0, 3 );
    setcolor( WHITE );
    line( x1 + 5, y2, x2, y2 );
    line( x2, y2, x2, y1 + 5 );

}

int main()
{
    initwindow(1024, 720);
    buton buton1, buton7, butonStart, butonExit, butonReturn, butonHelp, butonModselect;
    int clickX, clickY, countnava22 = 20;
    bool apasaModselect = false;
paginaInceput:

    titlescreen( 400, 100, 600, 200, " V A P O A R E ", 8);

    initButon( butonStart, "START", 500, 300, 5 );
    initButon( butonHelp, "AJUTOR", 500, 400, 5);
    initButon( butonExit, "IESIRE", 500, 500, 5 );
    deseneazaButon( butonStart );
    deseneazaButon( butonHelp );
    deseneazaButon( butonExit );

    bool apasaStart = false, apasaExit = false, apasaHelp = false, winner;
    apasaReturn = false;

    do
    {
        if( ismouseclick(WM_LBUTTONDOWN) )
        {
            getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
            clearmouseclick(WM_LBUTTONDOWN);
            if ( clickX < 715 && clickX > 285 && clickY < 326 && clickY > 274 )
                apasaStart = true;
            else if ( clickX < 704 && clickX > 296 && clickY < 426 && clickY > 374 )
                apasaHelp = true;
            else if ( clickX< 704 && clickX > 296 && clickY < 526 && clickY > 474 )
                apasaExit = true;
        }

    }
    while ( apasaStart == false && apasaExit == false && apasaHelp == false);

    if( apasaStart )
    {
modeSelect:
        nava4C = 4, nava3C = 3, nava21C = 21, nava22C = 22;
        nava4P = 4, nava3P = 3, nava21P = 21, nava22P = 22;
        apasaReturn = false;
        setbkcolor(BLACK);
        clearviewport();
        delay( 300 );
        titlescreen( 400, 100, 600, 200, " SELECTATI MODUL DE JOC ", 5);
        initButon(buton1, "MOD CLASIC", 500, 300, 5);
        initButon(buton7, "MOD 7 SALVE", 500, 400, 5);
        initButon(butonReturn, " INAPOI ", 500, 500, 5 );


        deseneazaButon(buton1);
        deseneazaButon(buton7);
        deseneazaButon(butonReturn);

        ///buton 1: (285, 274  ;  715, 326)
        ///buton 7: (296, 374  ;  704, 426)


        ///am pastrat toate chestiile de desen pe care le-ai facut exact cum erau

        bool buton1Apasat = false, buton7Apasat = false;

        do
        {
            if (ismouseclick(WM_LBUTTONDOWN));
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);

                if (clickX < 704 && clickX > 296 && clickY < 326 && clickY > 274)
                    buton1Apasat = true;
                else if (clickX < 704 && clickX > 296 && clickY < 426 && clickY > 374)
                    buton7Apasat = true;
                else if( clickX < 704 && clickX > 296 && clickY < 526 && clickY > 474)
                    apasaReturn = true;
            }

        }
        while (buton1Apasat == false && buton7Apasat == false && apasaReturn == false);

        if( apasaReturn )
        {
            setbkcolor(BLACK);
            clearviewport();
            goto paginaInceput;
        }
        CareuB();
        ScoreBoard();
        CareuA();

        int xPrev, yPrev, marime = 4, linia, coloana;
        int counter = 0;

        bool capat = true;
        int randLin, randCol;
        bool piesaPusa = true;

        initButon(butonReturn, " INAPOI ", 920, 680, 2 );
        deseneazaButon(butonReturn);

        ///repeta loop-ul asta pana cand counter-ul de click-uri ajunge la 8 (4 nave x 2 click-uri = 8 click-uri)
        do
        {
            piesaPusa = false;
            setbkcolor(WHITE);
            setcolor(BLUE);
            char cMarime = '0' + marime;
            char charAfiseaza[50] = "Alegeti capetele vaporului de marime  .";
            charAfiseaza[37] = cMarime;

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(300, 600, charAfiseaza);

            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);

                if( clickX < 993 && clickX > 847 && clickY < 695 && clickY > 665)
                    apasaReturn = true;
                if( apasaReturn )
                {
                    setbkcolor(BLACK);
                    clearviewport();
                    goto modeSelect;
                }

                ///fac obtinerea de linie si coloana corespunzatoare aici si am facut functia ta de desen piesa cu piesa...
                ///...sa ia ca parametri linia si coloana instead (e mai usor de folosit din functia care face fill la restul navei
                int linia=(clickY - sus) / latura + 1;
                int coloana=(clickX - stanga) / latura + 1;

                ///counter e par cand pui prima piesa a unei nave
                if (counter % 2 == 0)
                {
                    if (linia <= 10 && coloana <= 10 && linia >= 1 && coloana >= 1)
                        ///pune prima piesa dintr-o nava si retine unde e
                    {
                        if (TablaDeJoc[linia][coloana] == 0)
                        {
                            PiesaDupaLinieSiColoana(culori[marime], linia, coloana, marime);
                            piesaPusa = true;
                        }
                    }

                    xPrev = clickX;
                    yPrev = clickY;
                }

                ///counter e impar cand pui a doua piesa din nava
                else
                {
                    ///marime + 1 pentru ca scad marime in acelasi timp tot aici
                    if (TablaDeJoc[linia][coloana] == 0)
                    {
                        if (buton1Apasat == true)
                            Piesa2Normal(culori[marime + 1], clickX, clickY, xPrev, yPrev, marime--);

                        else if (buton7Apasat == true)
                            Piesa2(culori[marime + 1], clickX, clickY, xPrev, yPrev, marime--);

                        piesaPusa = true;
                    }
                }

                if (piesaPusa == true)
                    counter++;

                ///trebuie doua nave de marime 2. nu prea eleganta chestia asta dar whatever se executa doar de 8 ori
                if (marime == 1)
                    marime = 2;
            }

        }
        while (counter < 8);

        setcolor(FUNDAL);
        setfillstyle(SOLID_FILL, FUNDAL);
        bar(10, 590, 630, 720);

        srand(time(NULL));

        marime = 2;

        for (counter = 1; counter <= 4; counter++)
        {
            randLin = rand() % 10 + 1;
            randCol = rand() % 10 + 1;

            if (buton7Apasat == true)
                genereazaNavaComputer(randLin, randCol, marime);

            else if (buton1Apasat == true)
                genereazaNavaComputerNormal(randLin, randCol, marime);

            if (counter >= 2)
                marime++;
        }

        if( apasaModselect )
            countnava22 = 18;
        //winner = true;
        if (buton1Apasat == true)
        {
            if( apasaModselect )
                nava21C = 19, nava21P = 19;
            while( ( nava4C > 0 || nava3C > 0 || nava21C > 19 || nava22C > countnava22 ) &&
                    (nava4P > 0 || nava3P > 0 || nava21P > 19 || nava22P > countnava22 ) )
            {
                salvePlayer(1);
                if( apasaReturn )
                    goto modeSelect;

                prevNava4P = nava4P;
                prevNava3P = nava3P;
                prevNava21P = nava21P;
                prevNava22P = nava22P;

                if( countnava22 == 18 )
                {
                    if( nava22P > 20 )
                        nava21P = 21;
                    if( nava22P == 19 )
                        nava21P = 20;
                    if( nava22C > 20 )
                        nava21C = 21;
                    if( nava22C == 19 )
                        nava21C = 20;
                    salveCalculator1();
                    nava21C = 19;
                    nava21P = 19;
                }
                else salveCalculator1();
            }
            if( nava4P < 1 && nava3P < 1 && nava21P < 20 && nava22P < countnava22 + 1 )
            {
                winner = false;
                goto winscreen;
            }
            if( nava4C < 1 && nava3C < 1 && nava21C < 20 && nava22C < countnava22 + 1 )
            {
                winner = true;
                goto winscreen;
            }
        }
        else if (buton7Apasat == true)
        {
            int nrLovituri = 0;
            if( apasaModselect )
                nava21P = 19;
            while( (nava4C > 0 || nava3C > 0 || nava21C > 19 || nava22C > countnava22 ) &&
                    (nava4P > 0 || nava3P > 0 || nava21P > 19 || nava22P > countnava22 ) )
            {
                nrLovituri = 0;

                if( nava4P > 0 )
                    nrLovituri += 3;
                if( nava3P > 0 )
                    nrLovituri += 2;
                if( nava21P > 19 )
                    nrLovituri += 1;
                if( nava22P > 20 )
                    nrLovituri += 1;
                if( countnava22 == 18 )
                    nrLovituri += 1;
                salvePlayer(nrLovituri);

                if( apasaReturn )
                    goto modeSelect;
                if( countnava22 == 18 )
                {
                    if( nava22P > 20 )
                        nava21P = 21;
                    if( nava22P == 19 )
                        nava21P = 20;
                    if( nava22C > 20 )
                        nava21C = 21;
                    if( nava22C == 19 )
                        nava21C = 20;
                    salveCalculator(    );
                    nava21C = 19;
                    nava21P = 19;
                }
                else salveCalculator(    );

                if( nava4P < 1 && nava3P < 1 && nava21P < 20 && nava22P < countnava22 + 1 )
                {
                    winner = false;
                    goto winscreen;
                }
                if( nava4C < 1 && nava3C < 1 && nava21C < 20 && nava22C < countnava22 + 1 )
                {
                    winner = true;
                    goto winscreen;
                }


                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                    clearmouseclick(WM_LBUTTONDOWN);
                    if( clickX < 984 && clickX > 856 && clickY < 695 && clickY > 665)
                        apasaReturn = true;
                }
                if( apasaReturn )
                {
                    setbkcolor(BLACK);
                    clearviewport();
                    goto paginaInceput;
                }
            }
        }
winscreen:
        for( int linia = 1; linia < 11; linia++ )
            for( int coloana = 1; coloana < 11; coloana++ )
            {
                int sus = 150, stanga, latura = 35, x1, x2, y1, y2;
                if( winner )
                    stanga = 500;
                else
                    stanga = 50;
                Careu[linia][coloana] = hit;
                setcolor(FUNDAL);
                setfillstyle(SOLID_FILL,FUNDAL);
                x1=stanga+latura*(coloana-1);
                y1=sus+latura*(linia-1);
                x2=x1+latura;
                y2=y1+latura;
                delay( 10 );
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,BLACK);
                line( x1+1, y1+1, x2, y2 );
                line( x1+1, y1+latura, x2, y2-latura );
            }
        delay( 600 );
        setbkcolor( FUNDAL );
        clearviewport();
        if( winner )
            titlescreen( 400, 350, 600, 450, "PLAYER WINS", 9);
        else if( !winner )
            titlescreen( 400, 350, 600, 450, "COMPUTER WINS", 9);

        initButon( butonReturn, " INAPOI ", 920, 680, 2 );
        deseneazaButon( butonReturn );
        initButon( butonModselect, " SELECTARE MOD ", 160, 680, 2);
        deseneazaButon( butonModselect);
        apasaReturn = false, apasaModselect = false;
        do
        {

            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);
                if( clickX < 984 && clickX > 856 && clickY < 695 && clickY > 665)
                    apasaReturn = true;
                if( clickX <  297 && clickX > 23 && clickY < 695 && clickY > 665)
                    apasaModselect = true;
            }
        }
        while( apasaReturn == false && apasaModselect == false );
        if( apasaReturn )
        {
            apasaModselect = true;
            setbkcolor(BLACK);
            clearviewport();
            goto paginaInceput;
        }
        if( apasaModselect )
        {
            setbkcolor(BLACK);
            clearviewport();
            goto modeSelect;
        }
        getch();
        closegraph();
    }

    else if( apasaHelp )
    {
        setbkcolor( BLACK );
        clearviewport();
        ifstream modClasic;
        modClasic.open ("modClasic.txt");
        string text1;
        getline( modClasic, text1 );
        char *txt = new char[text1.length() + 1 ];
        strcpy( txt, text1.c_str());
        instructiuni( 20, 20, 980, 300, txt, 3 );
        int yTxt = 90;
        settextstyle( SIMPLEX_FONT, HORIZ_DIR, 2 );
        setfillstyle( EMPTY_FILL, BLACK );
        while( getline( modClasic, text1 ) )
        {
            char *txt = new char[text1.length() + 1 ];
            strcpy( txt, text1.c_str());
            outtextxy( 40, yTxt, txt );
            yTxt += 30;
        }
        modClasic.close();
        ifstream mod7salve;
        string text2;
        mod7salve.open ("mod7salve.txt");
        getline( mod7salve, text2 );
        char *txt2 = new char[text2.length() + 1 ];
        strcpy( txt2, text2.c_str());
        instructiuni( 20, 320, 980, 650, txt2, 3  );
        yTxt = 390;
        settextstyle( SIMPLEX_FONT, HORIZ_DIR, 2 );
        setfillstyle( EMPTY_FILL, BLACK );
        while( getline( mod7salve, text2 ) )
        {
            char *txt2 = new char[text2.length() + 1 ];
            strcpy( txt2, text2.c_str());
            outtextxy( 40, yTxt, txt2 );
            yTxt += 30;
        }
        mod7salve.close();
        setlinestyle( SOLID_LINE, 0, 1 );
        initButon( butonReturn, " INAPOI ", 920, 680, 2 );
        deseneazaButon( butonReturn );
        do
        {

            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
                clearmouseclick(WM_LBUTTONDOWN);
                if( clickX < 984 && clickX > 856 && clickY < 695 && clickY > 665)
                    apasaReturn = true;

            }
        }
        while( apasaReturn == false );
        if( apasaReturn )
        {
            setbkcolor(BLACK);
            clearviewport();
            goto paginaInceput;
        }
        getch();
    }

    else
    {
        exit(1);
        getch();
        closegraph();
    }
    return 0;
}

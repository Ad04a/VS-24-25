/*
Направете структура за филм, в която има полета за име, година на издаване и жанр.
Направете структура за филмотека, в която има полета за рафтове и поле за масив за
остатъчни филми с дължина 10. Филмотеката трябва да има 5 рафта, като на всеки рафт
има място за 5 филма (вие изберете как ще организирате самата структура, като и 
това ще се оценява. За целта може да си служите и с допълнителни, измислени от вас, 
структури)

Направете функция, която добавя филм на рафта 
int add_film(struct Film_Library *fl, struct Film film). 
Трябва да се провери дали има място за поставяне, като всеки рафт трябва да 
съдържа филми от една и съща категория. Ако филмите на някой рафт станат повече 
от свободните места, започнете нов ред с тази категория. Ако няма достатъчно място 
да се създаде нова категория то филма отива в масива с остатъчни филми. Функцията 
трябва да връща 1, ако филма е добавен успешно и 0, ако не е добавен нито на рафт, 
нито в остатъчните филми.

Направете функция за принтиране на цялата филмотека.
*/

#include <stdio.h>
#include <string.h>
 
typedef struct 
{
    char name[30];
    int year;
    char genre[20];

} Movie;

typedef struct
{
    Movie Shelves[5][5];
    Movie other[10];

} Movie_Lib;

Movie empty = {"", -1, ""};

int add_movie(Movie_Lib* ml, Movie movie)
{
    for(int i=0; i<5; i++)
    {
        if(strcmp(ml->Shelves[i][0].genre, movie.genre) != 0)
        {
            continue;
        }

        for(int j=0; j<5; j++)
        {
            if(ml->Shelves[i][j].year != empty.year)
            {
                continue;
            }
            
            ml->Shelves[i][j] = movie;
            return 1;
        }
    }

    for(int i=0; i<5; i++)
    {
        if(ml->Shelves[i][0].year == empty.year)
        {
            ml->Shelves[i][0] = movie;
            return 1;
        }
    }

    for(int i=0; i<10; i++)
    {
        if(ml->other[i].year == empty.year)
        {
            ml->other[i] = movie;
            return 1;
        }
    }

    return 0;
}

void print_movie(Movie movie)
{
    printf("[ %s (%s): %d]", movie.name, movie.genre, movie.year);
}

void print_lib(Movie_Lib ml)
{
    printf(" -------- Movie Lib -------\n");
    for(int i=0; i<5; i++)
    {
        printf("- ");
        for(int j=0; j<5; j++)
        {
            if(ml.Shelves[i][j].year == empty.year)
            {
                printf( "[]");
            }else
            {
                print_movie(ml.Shelves[i][j]);
            }
            printf(", ");
        }
        printf("\n");
    }
    printf(" * Other: ");
    for(int i=0; i<10 ;i++)
    {
        if(ml.other[i].year == empty.year)
        {
            printf( "[]");
        }else
        {
            print_movie(ml.other[i]);
        }
        printf(", ");
    }
    printf("\n");
}

void clear_lib(Movie_Lib* ml)
{
    for(int i=0; i<5; i++)
    {
        
        for(int j=0; j<5; j++)
        {
            ml->Shelves[i][j] = empty;
        }
    }
    for(int i=0; i<10; i++)
    {
        ml->other[i] = empty;
    }
}

int main()
{
    Movie_Lib ml;
    clear_lib(&ml);
    print_lib(ml);

    Movie m1 = {"1", 1900, "Comedy"};
    Movie m2 = {"2", 1800, "Western"};
    Movie m3 = {"3", 2010, "Horror"};
    Movie m4 = {"4", 1700, "Action"};
    Movie m5 = {"5", 2020, "Sci-Fi"};

    for(int i=2; i>0; i--)
    {
        add_movie(&ml, m1);
        add_movie(&ml, m1);
        add_movie(&ml, m1);
        add_movie(&ml, m1);

        add_movie(&ml, m2);

        add_movie(&ml, m3);

        add_movie(&ml, m1);
        add_movie(&ml, m1);

        add_movie(&ml, m3);

        add_movie(&ml, m4);
        add_movie(&ml, m5);
    }
    print_lib(ml);

    return 0;
}
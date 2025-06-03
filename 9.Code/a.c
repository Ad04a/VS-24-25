/*
Направете структура за книга, в която има полета за име, автор, жанр и цена.
Направете структура за библиотека, в която има полета за рафтове и поле за масив
за остатъчни книги с дължина 7. Библиотеката трябва да има 4 рафта, като на всеки
рафт има място за 7 книги (вие изберете как ще организирате самата структура, 
като и това ще се оценява. За целта може да си служите и с допълнителни,
измислени от вас, структури)

Направете функция, която добавя книга в библиотеката 
int donate_book(struct Library *lib, struct Book book). 
Трябва да се провери дали има място за поставяне, като всеки рафт трябва да
съдържа книги само от един автор. Ако книгите на някой рафт станат повече от
свободните места, започнете нов ред с този автор. Ако няма достатъчно място да
се създаде нова ред то книгата отива в масива с остатъчни книги. Функцията трябва
да връща 1, ако книгата е добавена успешно и 0, ако не е добавена нито на рафт,
 нито в остатъчните книги. 

Направете функция, която да връща общата цена на остатъчните книги
*/


#include <stdio.h>
#include <string.h>

typedef struct 
{
    char name[30];
    char author[30];
    char genre[30];
    float price;
} Book;

typedef struct 
{
    char author[20];
    Book books[7];
    int book_count;
} Shelf;

typedef struct 
{
    Shelf shelves[4];
    Shelf other;
}Library;

int donate_book(Library* lib, Book book)
{
    int empty_shelf_index = -1;
    for(int i=0; i<4; i++)
    {
        if(empty_shelf_index!=-1 && strcmp(lib->shelves[i].author, "") ==0)
        {
            empty_shelf_index = i;
            continue;
        }
        if(strcmp(lib->shelves[i].author, book.author) !=0)
        {
            continue;
        }

        if(lib->shelves[i].book_count >= 7) continue;

        lib->shelves[i].books[lib->shelves[i].book_count++] = book;
        strcpy(lib->shelves[i].author, book.author);
        return 1;  
    }

    if(empty_shelf_index!=-1)
    {
        lib->shelves[empty_shelf_index].books[lib->shelves[empty_shelf_index].book_count++] = book;
        strcpy(lib->shelves[empty_shelf_index].author, book.author);
        return 1;
    }

    if(lib->other.book_count <=7)
    {
        lib->other.books[lib->other.book_count++] = book;
        return 1;
    }

    return 0;
}

float gtTotalPrice(Library lib)
{
    float sum = 0;
    for(int i=0; i<7; i++)
    {
        sum += lib.other.books[i].price;
    }
    return sum;
}

int main()
{
    Library lib;
    return 0;
}
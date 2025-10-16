#include <stdio.h>

#include <string.h>

typedef struct 
{
    char name[20];
    int price;
    char effect [50] ;
} Item;

typedef struct Player
{

    char hero[20];
    int money;
    Item inventory[6];

} Player;


Item generateItem(char* Name, int price)
{
    Item temp;
    temp.price = price;

    strcpy(temp.name, Name);

    return temp;
}

void printItem(Item i)
{
    printf(" - %s : %d\n", i.name, i.price);
}

void printPlayer(Player p)
{
    printf(" -------- %s -------\n", p.hero);
    for(int i=0; i< sizeof(p.inventory)/sizeof(Item) ;i++)
    {
        printItem(p.inventory[i]);
    }
    printf("Money: %d\n", p.money);
}

int buyItem(Player* p, Item item)
{
    if(p->money < item.price) {return -1;}

    for(int i=0; i<sizeof(p->inventory)/sizeof(Item); i++)
    {
        if(p->inventory[i].price != 0){ continue;}

        p->money -= item.price;
        p->inventory[i].price = item.price;
        strcpy(p->inventory[i].name, item.name);
        strcpy(p->inventory[i].effect, item.effect);

        return 0;
    }
    return -1;
}

int sellItem(Player* p, int i)
{
    if(p->inventory[i].price == 0 || i>=sizeof(p->inventory)/sizeof(Item) || i<0) return 0;

    p->money += p->inventory[i].price * 0.7;

    p->inventory[i].price = 0;
    *p->inventory[i].name = '\0';
    strcpy(p->inventory[i].effect, "");


    return -1;
}

int main()
{

    Item BF = generateItem("B.F. sword", 1300);
    Player p = {"Garen", 2950, {BF}};

    buyItem(&p, BF);
    buyItem(&p, BF);
    buyItem(&p, BF);

    printPlayer(p);

    sellItem(&p, 1);
    printPlayer(p);

    buyItem(&p, generateItem("Ruby Crystal", 400));
    buyItem(&p, generateItem("Saphire Crystal", 350));

    buyItem(&p, generateItem("Glowing Mote", 150));
    buyItem(&p, generateItem("Glowing Mote", 150));
    buyItem(&p, generateItem("Glowing Mote", 150));

    sellItem(&p, 0);

    buyItem(&p, generateItem("Glowing Mote", 150));

    printPlayer(p);

    return 0;
}
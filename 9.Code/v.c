#include <stdio.h>

#include <string.h>

#define BIG_MAX 64;
#define SMALL_MAX 16;
#define TOOL_MAX 1;


int getStackLimit(char type)
{
    switch(type)
    {
        case 's' : return SMALL_MAX;
        case 'b' : return BIG_MAX;
        case 't' : return TOOL_MAX;
    }

    return 0;
}

char getSmallType()
{
    return 's';
}

char getBigType()
{
    return 'b';
}

char getToolType()
{
    return 't';
}

typedef struct
{
    char name[20];
    int count;
    int price;

    char type;

} ItemSlot;

typedef struct
{
    char name[30];
    int money;
    ItemSlot inventory[36];

} Player;

void printItem(ItemSlot item)
{
    printf("- %s : %d/%d [%d]\n", item.name, item.count, getStackLimit(item.type), item.price);
}


void printPlayer(Player p)
{
    printf("%s [%d] : \n", p.name, p.money);

    int inventorySize = sizeof(p.inventory)/sizeof(ItemSlot);

    int used = 0;

    for(int i=0; i< inventorySize; i++)
    {
        if(p.inventory[i].count == 0) continue;
        printItem(p.inventory[i]);
        used++;
    }

    printf("{ %d / %d }", used, inventorySize);
}


int addItem(Player* p, ItemSlot item)
{

    if(item.count == 0 || item.count<0) return 0;

    int inventorySize = sizeof(p->inventory)/sizeof(ItemSlot);

    for(int i=0; i< inventorySize; i++)
    {
        if(strcmp(p->inventory[i].name,  item.name) != 0) continue; 

        int remaining = getStackLimit(p->inventory[i].type) - p->inventory[i].count;
        
        if(remaining == 0 ) continue;

        if(remaining > item.count)
        {
            printf("stack add\n");
            p->inventory[i].count += item.count;
            return 0;
        }
        
        printf("stack overflow\n");
        p->inventory[i].count = getStackLimit(p->inventory[i].type);
        item.count -= remaining;
        return addItem(p, item);
    }

    for(int i=0; i< inventorySize; i++)
    {
        if(p->inventory[i].count != 0) continue;

        printf("empty add\n");

        p->inventory[i].count = item.count;
        p->inventory[i].price = item.price;
        p->inventory[i].type = item.type;

        strcpy(p->inventory[i].name, item.name);

        if(p->inventory[i].count > getStackLimit(p->inventory[i].type))
        {
            item.count =  p->inventory[i].count - getStackLimit(p->inventory[i].type);
            p->inventory[i].count = getStackLimit(p->inventory[i].type);
            printf("empty overflow\n");
            return addItem(p, item);
        }

        return 0;   
    } 

    return 0;
}

ItemSlot generateItemSlot(char name[20], int count, int price, char type)
{
    ItemSlot tnt;
    
    tnt.count = count;
    tnt.price = price;
    tnt.type = type;

    strcpy(tnt.name, name);

    return tnt;
}

int main()
{

    ItemSlot tnt = {"tnt", 64, 5, getBigType()};

    //printItem(tnt);

    Player Steve = {"Steve", 0, {tnt}};

    addItem(&Steve, generateItemSlot("dirt", 65, 1, getBigType()));
    addItem(&Steve, generateItemSlot("dirt", 65, 1, getBigType()));

    printPlayer(Steve);

    return 0;
}
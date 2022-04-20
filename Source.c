#include <stdio.h>
#include <stdlib.h>

struct Wagon
{
    char svet;
    struct Wagon *prevWagon;
    struct Wagon *nextWagon;
};

struct Wagon *createWagon(struct Wagon *newWagon);

struct Wagon *Walloc(void);

int main()
{
    struct Wagon wg;
    wg.nextWagon = createWagon(wg.nextWagon);
    printf("%p\n", wg.nextWagon);

    wg.prevWagon = createWagon(wg.prevWagon);
    printf("%p\n", wg.prevWagon);
}

struct Wagon *createWagon(struct Wagon *newWagon)
{
    newWagon = Walloc();
    printf("%p\n", newWagon);
    newWagon->nextWagon = newWagon->prevWagon = NULL;
    return newWagon;
}

struct Wagon *Walloc(void)
{
    return (struct Wagon *)malloc(sizeof(struct Wagon));
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Wagon
{
    short int svet;
    struct Wagon *prevWagon;
    struct Wagon *nextWagon;
};

struct Wagon *Walloc(void);

struct Wagon *createWagon(struct Wagon *newWagon, struct Wagon *actWagon, char isNextWagonNew, unsigned long long *x);

struct Wagon *createNWagons(struct Wagon *actWagon, char isNextWagonNew, int N, unsigned long long *x);

void tieWagons(struct Wagon *leftestWagon, struct Wagon *rightestWagon);

short int getSvet(unsigned long long *x);

int trainSize(struct Wagon *tempWagon);

void trainInit(struct Wagon *lst_wagon, struct Wagon *rst_wagon, unsigned long long *x);

void clearscr ( void );

int main()
{
    srand(time(NULL));
	unsigned long long x = abs(rand());
    
    struct Wagon wg;
    wg.svet = 1;
    wg.nextWagon = NULL;
    wg.prevWagon = NULL;
    
    struct Wagon *rst_wagon = &wg;
    struct Wagon *lst_wagon = &wg;
    
    trainInit(lst_wagon, rst_wagon, &x);

    struct Wagon *tempWagon = &wg;
    int length_of_train = 1;

    length_of_train = trainSize(tempWagon);
    printf("%d - length of the train", length_of_train);
}

struct Wagon *Walloc(void)
{
    return (struct Wagon *)malloc(sizeof(struct Wagon));
}
struct Wagon *createWagon(struct Wagon *newWagon, struct Wagon *actWagon, char isNextWagonNew, unsigned long long *x)
{
    newWagon = Walloc();

    if(isNextWagonNew == 1)
    {
        newWagon->nextWagon = NULL;
        newWagon->prevWagon = actWagon;
    }else if(isNextWagonNew == 0)
    {
        newWagon->nextWagon = actWagon;
        newWagon->prevWagon = NULL;
    }
    newWagon->svet = getSvet(x);
    return newWagon;
}

struct Wagon *createNWagons(struct Wagon *actWagon, char isNextWagonNew, int N, unsigned long long *x)
{
    struct Wagon *temp_Wagon;
    temp_Wagon = actWagon;
    if(isNextWagonNew)
        for(int i = 0; i < N; i++)
        {
            temp_Wagon->nextWagon = createWagon(temp_Wagon->nextWagon, temp_Wagon, 1, x);
            temp_Wagon = temp_Wagon->nextWagon;
        }
    else
        for(int i = 0; i < N; i++)
        {
            temp_Wagon->prevWagon = createWagon(temp_Wagon->prevWagon, temp_Wagon, 0, x);
            temp_Wagon = temp_Wagon->prevWagon;
        }
    return temp_Wagon;
}

void tieWagons(struct Wagon *leftestWagon, struct Wagon *rightestWagon)
{
    leftestWagon->prevWagon = rightestWagon;
    rightestWagon->nextWagon = leftestWagon;
    //printf("%p == %p \n", leftestWagon->prevWagon, rightestWagon);
    //printf("%p == %p \nif the same - tied\n", leftestWagon, rightestWagon->nextWagon);  
}

short int getSvet(unsigned long long *x)
{
    unsigned long long m = 4294967296;
    unsigned long long c = 39027341287453;
    unsigned long long a = 2147483653;
    *x = (*x * a + c) % m;

    return ((*x >> 8) % 2); 
}

int trainSize(struct Wagon *tempWagon)
{
    int length_of_train = 1;
    short int found = 0;
    while(!found)
    {
        short int lightened_wagon = 0;
        while(!lightened_wagon)
        {
            tempWagon = tempWagon->nextWagon;
            if(tempWagon->svet == 1)
            {
                tempWagon->svet = 0;
                lightened_wagon = 1;
            }
            length_of_train++;
        }
        int temp = 1;
        while(temp < length_of_train)
        {
            tempWagon = tempWagon->prevWagon;
            temp++;
        }
        if(tempWagon->svet == 0)
        {
            found = 1;
            length_of_train--;
        }
        else
        {
            temp = 1;
            while(temp < length_of_train)
            {
                tempWagon = tempWagon->nextWagon;
                temp++;
            }
        }
    }
    return length_of_train;
}

void trainInit(struct Wagon *lst_wagon, struct Wagon *rst_wagon, unsigned long long *x)
{
    int n = 0;
    int isNextWagonCreate = -1;
    while(isNextWagonCreate != 2)
    {
        
        printf("0| Create new wags in left side \n\
1| Create new wags in right side \n\
2| Tie ends of the train and exit \n");
        scanf("%d", &isNextWagonCreate);
       
        if(isNextWagonCreate == 0 || isNextWagonCreate == 1)
        {
            printf("how many wagons wanna create?\n");
            scanf("%d", &n);
            if(isNextWagonCreate == 0)
            {
                lst_wagon = createNWagons(lst_wagon, isNextWagonCreate, n, x);
                clearscr();
                printf("Added %d wagons in the left side\n", n);
            }else
            {
                rst_wagon = createNWagons(rst_wagon, isNextWagonCreate, n, x);
                clearscr();
                printf("Added %d wagons in the right side\n", n);
            }
        }
        else if(isNextWagonCreate == 2)
        {
            tieWagons(lst_wagon, rst_wagon);
        }
    }
}

void clearscr ( void )
{
    printf("\033[2J\033[1;1H");
}

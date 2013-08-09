/*
 * =====================================================================================
 *
 *       Filename:  BeaconsOfGondor.cpp 
 *    Description:  This program illustrates the concept of a linked list 
 *    by simulating the Beacons of Gondor story from J. R. R. Tolkien's 
 *    Return of the King.
 *
 * =====================================================================================
 */
#include <iostream>
#include <string.h>
using namespace std;

/*
 * Type: Tower 
 * ------------
 * This structure contains the name of the tower and a link to the next tower
 */
struct  Tower {
    string name;
    Tower *link;
};

/* Function prototypes */
Tower *createBeaconsOfGondor();
Tower *createTower(string name, Tower *link);
void signal(Tower *start);

/*Main program */
int main() {
    Tower *list = createBeaconsOfGondor();
    signal(list);
    return 0;
}

/*
 * Function: createBeaconsOfGondor
 * Usage: Tower *list = createBeaconsOfGondor();
 * ------------------------------------------
 * Creates a linked list of the towers by Tolkien. The function builds 
 * the list backwards and returns a pointer to the first tower.
 */

Tower *createBeaconsOfGondor() {
    Tower *tp = createTower("Rohan", NULL);
    tp = createTower("Halifirien", tp);
    tp = createTower("Calenhad",tp);
    tp = createTower("Min-Rimmon",tp);
    tp = createTower("Erelas", tp);
    tp = createTower("Nardo1",tp);
    tp = createTower("Eilenach", tp);
    tp = createTower("Amon Din", tp);
    return createTower("Minas Tirith", tp);
}

/* 
 * Function: createTower
 * Usage: Tower *chain = createTower(name, link)
 * ------------------------------------------
 * creates a new Tower structure with the specified components 
 */
Tower *createTower(string name, Tower *link) 
{
    Tower *tp = new Tower;
    tp->name = name;
    tp->link = link;
    return tp;
}

/*
 * Function: signal
 * Usage: signal(start);
 * --------------------
 * Generates a signal starting at the current tower and processing
 * through the end of the chain
 */
void signal(Tower *start)
{
    for(Tower *tp = start; tp != NULL; tp = tp->link)
    {
        cout << "lighting " << tp->name << endl;
    }
}

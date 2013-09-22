/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  problemID: 1705
 *
 * =====================================================================================
 */
#include <stdio.h>

#define EPSILON 1e-8
#define WALK_SPEED 1.2
#define BIKE_SPEED 3.0
#define BIKE_START_TIME 27
#define BIKE_STOP_TIME 23

int main(void)
{
    int n;
    int distance;
    double walk_time;
    double bike_time;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d", &distance);
        walk_time = distance/1.2;
        bike_time = BIKE_START_TIME + BIKE_STOP_TIME + distance/BIKE_SPEED;
        if(walk_time - bike_time > EPSILON)
            printf("Bike\n");
        else if(bike_time - walk_time > EPSILON)
            printf("Walk\n");
        else 
            printf("All\n");
    }

    return 0;
}

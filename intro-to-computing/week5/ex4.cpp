/*
 * =====================================================================================
 *
 *       Filename:  ex4.cpp
 *
 *    Description:  count of Olympic medals
 *
 * =====================================================================================
 */

#include <cstdio>
using namespace std;

int main(void)
{
    int n;
    int total_gold = 0;
    int total_silver = 0;
    int total_copper = 0;
    int cur_gold, cur_silver, cur_copper;

    scanf("%d", &n);
    while(n-- > 0)
    {
        scanf("%d %d %d", &cur_gold, &cur_silver, &cur_copper);
        total_gold += cur_gold;
        total_silver += cur_silver;
        total_copper += cur_copper;
    }

    printf("%d %d %d %d\n", total_gold, total_silver, total_copper, 
                            total_gold + total_silver + total_copper);

    return 0;
}

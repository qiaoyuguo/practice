/*
 * =====================================================================================
 *
 *       Filename:  ex7.c
 *
 *    Description:  problemID 6180
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

struct fraction
{
    int nom;
    int denom;
};

int gcd(int n, int m)
{
    if(m == 0)
        return n;
    return gcd(m, n%m);
}

int add_fraction(struct fraction *target, struct fraction *src)
{
    int denom;
    int nom;
    int common_factor;
    if(target == NULL || src == NULL)
        return 0;

    denom = target->denom * src->denom;
    nom = target->nom * src->denom + target->denom * src->nom;
    common_factor = gcd(nom, denom);
    target->nom = nom/common_factor;
    target->denom = denom/common_factor;

    return 1;
}
int print_fraction(struct fraction *f)
{
    if(f == NULL)
        return 0;
    if(f->nom == 0)
        printf("%d\n", 0);
    else if(f->denom == 1)
        printf("%d\n", f->nom);
    else
        printf("%d/%d\n", f->nom, f->denom);

    return 1;
}
int main(void)
{
    int n,i;
    struct fraction *a;

    scanf("%d", &n);
    a = malloc((sizeof(struct fraction)));
    if(a == NULL)
        return -1;
    
    for(i = 0; i < n; i++)
        scanf("%d/%d", &a[i].nom, &a[i].denom);
    /*  
    for(i = 0; i < n; i++)
        print_fraction(&a[i]);*/
    for(i = 1; i < n; i++)
    {
        add_fraction(&a[0], &a[i]);
        //print_fraction(&a[0]);
    }
    print_fraction(&a[0]);

    return 0;
}

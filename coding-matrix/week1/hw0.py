# Please fill out this stencil and submit using the provided submission script.

## Problem 1
def myFilter(L, num): return [ x for x in L if x % num != 0]

## Problem 2
def myLists(L): return [ [ i for i in range(1,x+1)] for x in L] 


## Problem 3
def myFunctionComposition(f, g): return { k:g[f[k]] for k in f.keys()}
#print(myFunctionComposition({0:'a',1:'b'},{"a":"y",'b':'n'} ))


## Problem 4
# Please only enter your numerical solution.

complex_addition_a = (3+1j)+(2+2j)
complex_addition_b = (-1+2j)+(1-1j)
complex_addition_c = (2+0j) + (-3+.001j)
complex_addition_d = 4*(0+2j) + (.001+1j)

## Problem 5
GF2_sum_1 = (1+1+1+0)%2
GF2_sum_2 = (1*1+0*1+0*0+1*1)%2
GF2_sum_3 = (((1+1+1)%2) * ((1+1+1+1)%2))%2


## Problem 6
def mySum(L): 
    result = 0
    for x in L:
        result += x
    return result


## Problem 7
def myProduct(L): 
    result = 1
    for x in L:
        result *= x
    return result


## Problem 8
def myMin(L): 
    result = L[0]
    for x in L:
        if x < result:
            result = x
    return result



## Problem 9
def myConcat(L): 
    result = ""
    for x in L:
        result += x
    return result

## Problem 10
def myUnion(L): 
    result = set()
    for x in L:
        result.update(x) 
    return result
#print(myUnion([{1,2},{2,3},{3,4}]))

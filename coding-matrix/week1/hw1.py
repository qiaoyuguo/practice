# Please fill out this stencil and submit using the provided submission script.

from GF2 import one

## Problem 1
p1_u = [ 0, 4]
p1_v = [-1, 3]
p1_v_plus_u = [ p1_v[i] + p1_u[i] for i in range(len(p1_u))]
p1_v_minus_u = [ p1_v[i] - p1_u[i] for i in range(len(p1_u))]
p1_three_v_minus_two_u = [ 3*p1_v[i] - 2 * p1_u[i] for i in range(len(p1_u))]
#print(p1_v_plus_u, p1_v_minus_u, p1_three_v_minus_two_u)

## Problem 2
p2_u = [-1,  1, 1]
p2_v = [ 2, -1, 5]
p2_v_plus_u = [p2_v[i] + p2_u[i] for i in range(len(p2_u))]
p2_v_minus_u = [ p2_v[i] - p2_u[i] for i in range(len(p2_u))]
p2_two_v_minus_u = [ 2*p2_v[i] - p2_u[i] for i in range(len(p2_u))]
p2_v_plus_two_u = [ p2_v[i] +2* p2_u[i] for i in range(len(p2_u))]
#print(p2_v_plus_u, p2_v_minus_u, p2_two_v_minus_u, p2_v_plus_two_u)



## Problem 3
# Write your answer using GF2's one instead of the number 1
p3_u = [one, one, one]
p3_v = [0, one, one]
p3_vector_sum_1 = [ p3_u[i]+p3_v[i] for i in range(len(p3_u))] 
p3_vector_sum_2 = [ p3_v[i] + p3_u[i] + p3_u[i] for i in range(len(p3_u))]
#print(p3_vector_sum_1, p3_vector_sum_2)


## Problem 4
# Please express your solution as a set of the letters corresponding to the solutions.
# For example, {'a','b','c'} is the subset consisting of:
#   a (1100000), b (0110000), and c (0011000).
# Leave an empty set if it cannot be expressed in terms of the other vectors.
vec_lst = {'a':[one, one, 0, 0, 0, 0, 0], 'b':[0, one, one, 0, 0, 0, 0], 
        'c': [0, 0, one, one, 0, 0, 0], 'd':[0, 0, 0, one, one, 0, 0],
        'e':[0,0, 0, 0, one, one, 0], 'f':[0, 0, 0, 0, 0, one, one]}
p4_u0010010 = [0, 0, one, 0, 0, one, 0]
p4_u0100010 = [0, one, 0, 0, 0, one, 0]
def p4_get_all_subset(some_set):
    result = [[]]
    for x in some_set:
        result.extend([subset + [x] for subset in result])
    return result
#print(p4_get_all_subset(set(vec_lst.keys())))
def p4_get_result(vec):
    p4_all_subset = p4_get_all_subset(set(vec_lst.keys()))
    for tmp_set in p4_all_subset:
        total = [ 0 for i in range(len(vec)) ] 
        #print(total)
        for i in tmp_set:
            tmp_result = [ total[j] + vec_lst[j] for j in range(len(vec_lst[i]))] 
            total = tmp_result
            print(total)
        if(total == vec):
            print(tmp_set)
            return set(tmp_set)
    return set()
u_0010010 = {'c', 'd', 'e'}
u_0100010 = {'b', 'c', 'd', 'e'}
#print(u_0010010, u_0100010)



## Problem 5
# Use the same format as the previous problem

v_0010010 = {'c', 'd'}
v_0100010 = set()

## Problem 6
uv_a = 1 * 5 + 0 * 4321 #[[1,0][i] * [5, 4321][i] for i in range(2)]
uv_b = 0 * 12345 + 1 * 6 #[[0,1][i] * [12345, 6][i] for i in range(2)] 
uv_c = (-1) * 5 + 3 * 7 #[[-1,3][i] * [5,7][i] for i in range(2) ] 
uv_d = -1.0/2 + (-1.0/2)


## Problem 7
# use 'one' instead of '1'
x_gf2 = [one, 0, 0, 0]



## Problem 8
v1 = [2,3,-4,1]
v2 = [1,-5,2,0]
v3 = [4,1,-1,-1]


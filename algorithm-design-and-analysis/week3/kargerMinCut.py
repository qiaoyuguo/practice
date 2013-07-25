#!/usr/bin/env python
# Karger's min cut algorithm implementation
# http://upload.wikimedia.org/wikipedia/commons/thumb/e/e7/Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg/2000px-Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg.png 

import random
import copy

def read_txt(file_name):
    """ read  an undirected graph file(represented by adjacent-list) and return a dictionary 
    >>> read_txt("test-8v.txt")
    {1: [2, 3, 4], 2: [1, 3, 4], 3: [1, 2, 4, 5], 4: [1, 2, 3, 6], 5: [3, 6, 7, 8], 6: [4, 5, 7, 8], 7: [5, 6, 8], 8: [5, 6, 7]}
    >>> read_txt("8-loop.txt")
    {1: [2], 2: [3], 3: [4], 4: [5], 5: [6], 6: [7], 7: [8], 8: [1]}
    """
    f = open(file_name, "r")
    lines = f.readlines() 
    G = dict()
    for line in lines:
        tmp_lst = line.split()
        G[int(tmp_lst[0])] = [ int(i) for i in tmp_lst[1:]]
    return G

def find_min_cut(G):
    """ find Mininum cut in the graph G using karger's algorithm
    >>> find_min_cut({1: [2, 8], 2: [1, 3], 3: [2, 4], 4: [3, 5], 5: [4, 6], 6: [5, 7], 7: [6, 8], 8: [7, 1]})
    1
    >>> find_min_cut({1: [2, 3, 4], 2: [1, 3, 4], 3: [1, 2, 4, 5], 4: [1, 2, 3, 6], 5: [3, 6, 7, 8], 6: [4, 5, 7, 8], 7: [5, 6, 8], 8: [5, 6, 7]})
    3
    """
    while len(G) > 2:
        fst_vert = random.choice(G.keys())
        to_be_contract_vert = random.choice(G[fst_vert])
        contract(fst_vert, to_be_contract_vert, G)
    return len(G.popitem()[1])

def contract(fst_vertex, to_be_contract_vert, G):
    """ Contract two vertices from an edge in graph G to one single vertex
    >>> contract(1, 2, {1: [2, 8], 2: [1, 3], 3: [2, 4], 4: [3, 5], 5: [4, 6], 6: [5, 7], 7: [6, 8], 8: [7, 1]})
    {1: [8, 3], 3: [1, 4], 4: [3, 5], 5: [4, 6], 6: [5, 7], 7: [6, 8], 8: [7, 1]}
    """
    to_be_contract_lst = G[to_be_contract_vert]
    G[fst_vertex].extend(to_be_contract_lst)
    for cur_vert in to_be_contract_lst:
        lst = G[cur_vert]
        for i in range(len(lst)):
            if lst[i] == to_be_contract_vert:
                lst[i] = fst_vertex

    while fst_vertex in G[fst_vertex]:
        G[fst_vertex].remove(fst_vertex)
    del G[to_be_contract_vert]

    return G
def core_handle():
    G = read_txt("kargerMinCut.txt")
    min_cut= float("inf")
    for i in range(200):
        cur_min_cut = find_min_cut(copy.deepcopy(G))
        if cur_min_cut < min_cut:
            min_cut = cur_min_cut
    print("min cut is ", min_cut)


if __name__ == "__main__":
    import doctest
    doctest.testmod()


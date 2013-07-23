from random import randint
from dictutil import *

## Task 1
def movie_review(name):
    """
    Input: the name of a movie
    Output: a string (one of the review options), selected at random using randint
    """
    return ["See it!", "A gem!", "Ideological claptrap!"][randint(0,2)]
#print(movie_review("Titanic"))

## Tasks 2 and 3 are in dictutil.py

## Task 4    
def makeInverseIndex(strlist):
    """
    Input: a list of documents as strings
    Output: a dictionary that maps each word in any document to the set consisting of the
            document ids (ie, the index in the strlist) for all documents containing the word.

    Note that to test your function, you are welcome to use the files stories_small.txt
      or stories_big.txt included in the download.
    """
    #dct = list(enumerate(strlist))
    dct = dict()
    for tmpstr in enumerate(strlist):
        for word in tmpstr[1].split():
            if word in dct:
                dct[word].add(tmpstr[0])
            else:
                dct[word]={tmpstr[0]}
    return dct
    #return dict([(word,tmpstr[0]) for tmpstr in enumerate(strlist) for word in tmpstr[1].split()])
s=['string one','string two','one time','one week','second string one']
inv = makeInverseIndex(s)
#{'week': {3}, 'string': {0, 1, 4}, 'second': {4}, 'two': {1}, 'one': {0, 2, 3, 4}, 'time': {2}}

## Task 5
def orSearch(inverseIndex, query):
    """
    Input: an inverse index, as created by makeInverseIndex, and a list of words to query
    Output: the set of document ids that contain _any_ of the specified words
    """
    result = set()
    for elem in inverseIndex:
        for q in query:
            if q in elem:
                for x in inverseIndex[q]:
                    result.add(x)
    return result
    #return [x for dic in inverseIndex for q in query if q in dic for x in dic[q]]
    #return {x for dic in inverseIndex for q in query if q in dic for x in inverseIndex[dic]}
print(orSearch(inv, ["string", "one"]))
## Task 6
def andSearch(inverseIndex, query):
    """
    Input: an inverse index, as created by makeInverseIndex, and a list of words to query
    Output: the set of all document ids that contain _all_ of the specified words
    """
    result = inverseIndex[query[0]]
    for q in query:
        result.intersection_update(inverseIndex[q])
    return result

    #return [q for dic in inverseIndex for q in query if q in dic]
    #return [q for dic in inverseIndex for q in query if q in dic]
print(andSearch(inv, ["string", "one"]))

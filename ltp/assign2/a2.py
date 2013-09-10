def get_length(dna):
    """ (str) -> int

    Return the length of the DNA sequence dna.

    >>> get_length('ATCGAT')
    6
    >>> get_length('ATCG')
    4
    """
    return len(dna)


def is_longer(dna1, dna2):
    """ (str, str) -> bool

    Return True if and only if DNA sequence dna1 is longer than DNA sequence
    dna2.

    >>> is_longer('ATCG', 'AT')
    True
    >>> is_longer('ATCG', 'ATCGGA')
    False
    """
    return len(dna1) > len(dna2)


def count_nucleotides(dna, nucleotide):
    """ (str, str) -> int

    Return the number of occurrences of nucleotide in the DNA sequence dna.

    >>> count_nucleotides('ATCGGC', 'G')
    2
    >>> count_nucleotides('ATCTA', 'G')
    0
    """
    result = 0
    index = 0
    while index < len(dna):
        tmpIndex = dna.find(nucleotide, index)
        if tmpIndex < 0: 
            break
        result += 1
        index = tmpIndex + 1
    return result

def contains_sequence(dna1, dna2):
    """ (str, str) -> bool

    Return True if and only if DNA sequence dna2 occurs in the DNA sequence
    dna1.

    >>> contains_sequence('ATCGGC', 'GG')
    True
    >>> contains_sequence('ATCGGC', 'GT')
    False

    """
    return dna1.find(dna2) >=0

def is_valid_sequence(dna):
    """ (str) -> bool

    Return True if the DNA sequence dna has no characters other than "A","T"    "C","G"

    >>> is_valid_sequence("ATTG")
    True
    >>> is_valid_sequence("ABGT")
    False

    """
    for c in dna:
        if c not in "ATCG":
            return False
    return True

def insert_sequence(dna_target, dna_src, pos):
    """ (str, str, int) -> str
    Insert dna_src to dna_target at index pos

    >>> insert_sequence('CCGG', 'AT', 2)
    'CCATGG'
    """

    return dna_target[:pos] + dna_src + dna_target[pos:]

def get_complement(nucleotide):
    """ (str) -> str
    return complement of given nucleotide 

    >>> get_complement('A')
    'T'
    >>> get_complement('G')
    'C'
    """
    dct = {'A':'T', 'T':'A', 'C':'G', 'G':'C'}
    return dct[nucleotide]

def get_complementary_sequence(dna):
    """ (str) -> str
    Return complementary sequence of given dna sequence

    >>> get_complementary_sequence("ACGTACG")
    'TGCATGC'
    """
    result = ''
    for c in dna:
        result += get_complement(c)
    return result

if __name__ == "__main__":
    import doctest
    doctest.testmod()

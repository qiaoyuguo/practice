def create_dct(file_name):
    f = open(file_name, "r")
    lines = f.readlines()
    f.close()
    res = dict()
    for line in lines:
        l = long(line)
        res[l] = long(l)
    return res

def test_two_sum(dct, target):
    s = set()
    for k in dct:
        m = target - k
        if  m != k and dct.has_key(m):
            return True 
    return False 
def two_sum(dct):
    s = set()
    for k  in dct:
        for t in range(-10000, 10001):
            if t not in s and test_two_sum(dct,t):
                s.add(t)
    return s

if __name__ == "__main__":
    dct = create_dct("2sum.txt")
    s = two_sum(dct)
    print(len(s),s)
    #print(test_two_sum(dct, 10001))

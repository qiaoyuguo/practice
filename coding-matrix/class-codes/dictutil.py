def dict2list(dct, keylist): return [dct[k] for k in keylist]

def list2dict(L, keylist): return dict(zip(keylist, L))

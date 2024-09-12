S = list()
def f(C, idx, SUM, L):
    if idx == len(C):
        S.append([round(SUM, 3), L])
        return
    f(C, idx+1, SUM, L + '0')
    f(C, idx+1, SUM + C[idx], L + '1')
    
def Nearest(c, S):
    minn = S[0]
    idx = 0
    for i in range(1, len(S)):
        if minn > abs(c - S[i][0]):
            minn = abs(c - S[i][0])
            idx = i
    return S[idx]
        
# --------------------------------------------- #
C = [4.613, 3.132, 2.158, 1.017, 0.4811]
f(C, 0, 0, '')

N = [2,4,5,6,7,9]
for _c in N:
    print(Nearest(_c, S))

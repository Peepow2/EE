def L(p, k):
    if p == 1:
        return 1/(k+1)
    return (1-p)*(p**k)/(1-p**(k+1))


def D(p, k, lam, L):
    if p == 1:
        return (k/2)/(lam*(1-L))
    return (1/lam*(1-L))*(p/(1-p)-((k+1)*(p**(k+1)/(1-p**(k+1)))))

p = 0.5
k = 11
while True:
    if abs(L(p, k) - 0.11) <= 0.001:
        print(p)
        break
    if L(p, k) > 0.11:
        p *= 0.5
    else:
        p *= 1.5
        
p = 0.5
k = 11
lam = 1
while True:
    if abs(D(p, k, lam, L(p, k)) - 11) <= 0.01:
        print(p)
        break
    if D(p, k, lam, L) > 11:
        p *= 0.5
    else:
        p *= 1.5

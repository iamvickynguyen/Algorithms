from math import factorial as fac

# calculate binomial coefficients
def binomial(x, y):
    try:
        binom = fac(x) // fac(y) // fac(x - y)
    except ValueError:
        binom = 0
    return binom
	
# calculate binomial coefficients (method 2)
def nCr(n, r):
    f = math.factorial
    return f(n) // f(r) // f(n-r)

# count total number of odd coefficients
table = {}
def count_odd_coefficients(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    if n in table:
        return table[n]
    elif n % 2 == 0:
        table[n] = 3*count_odd_coefficients(n//2)
    else:
        k = (n-1)//2
        table[n] = 2*count_odd_coefficients(k) + count_odd_coefficients(k+1)
    return table[n]

print(count_odd_coefficients(int(input())))
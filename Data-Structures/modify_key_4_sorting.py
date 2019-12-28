import functools

# suppose you want to sort a list of strings by comparing their 1st char then 2nd char
# this function modify compare function


def cmp_key(x, y):
    if x[0] == y[0]:
        if x[1] == y[1]:
            return 0
        else:
            return 1 if x[1] > y[1] else -1
    else:
        return 1 if x[0] > y[0] else -1


# test
names = ['Vicky', 'Nguyen', 'Naruto', 'hokage', 'sasuke']
sorted_name = sorted(names, key=functools.cmp_to_key(cmp_key))
print(sorted_name)

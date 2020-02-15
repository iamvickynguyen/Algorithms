# sort a list of tuples or strings by comparing their 1st element then 2nd element
import functools

def cmp_key(x, y):
    if x[0] == y[0]:
        if x[1] == y[1]:
            return 0
        else:
            return 1 if x[1] > y[1] else -1
    else:
        return 1 if x[0] > y[0] else -1

# test tuples
numbers = [(4, 10), (4, 9), (3, 3), (3, 2), (3, 3), (1, 5)]
sorted_numbers = sorted(numbers, key=functools.cmp_to_key(cmp_key))
print(sorted_numbers)
# [(1, 5), (3, 2), (3, 3), (3, 3), (4, 9), (4, 10)]

# test strings
names = ['vicky', 'nguyen', 'naruto', 'hokage', 'sasuke']
sorted_name = sorted(names, key=functools.cmp_to_key(cmp_key))
print(sorted_name)
# ['hokage', 'naruto', 'nguyen', 'sasuke', 'vicky']

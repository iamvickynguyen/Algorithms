# custom sort a list of tuples or strings
numbers = [(4, 10), (4, 9), (3, 3), (3, 2), (3, 3), (1, 5)] # [(1, 5), (3, 2), (3, 3), (3, 3), (4, 9), (4, 10)]
names = ['vicky', 'nguyen', 'vampire', 'naruto', 'sasuke'] # ['hokage', 'naruto', 'nguyen', 'sasuke', 'vicky']

# METHOD 1:
numbers_1 = sorted(numbers, key=lambda x: (x[0], x[1]))
names_1 = sorted(names, key=lambda x: (x[0], x[1]))

# METHOD 2:
import functools

def custom_cmp_key(x, y):
    if x[0] == y[0]:
        if x[1] == y[1]:
            return 0
        return 1 if x[1] > y[1] else -1
    return 1 if x[0] > y[0] else -1

numbers_2 = sorted(numbers, key=functools.cmp_to_key(custom_cmp_key))
names_2 = sorted(names, key=functools.cmp_to_key(custom_cmp_key))
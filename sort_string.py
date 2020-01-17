import sys

ending = input('enter ending char (if not press enter): ')
print('paste down here:')
l = []
for line in sys.stdin:
    line = line.strip()
    if ending != '':
        line = line.strip()[:-1]
    l.append(line)
l.sort()
print('-------------------------RESULT---------------------------')
for item in l:
    print(item + ending)

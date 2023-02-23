# Shoelace formula to calculate area of polygon
def Shoelace(points):
    n = len(points)
    area = 0.0
    for i in range(n):
        j = (i + 1) % n
        area += (points[i][0] * points[j][1] - points[j][0] * points[i][1])
    return abs(area)/2


points = [[0, 0], [10, 0], [0, 10]]
print(Shoelace(points))

x, y = map(int, input("Размерность змейки > ").split())
znake = [["." for j in range(y)] for i in range(x)]
for i in range(1, x+1):
    for j in range(1, y+1):
        if i%2 != 0:
            znake[i-1][j-1] = "#"
        if i%4 == 0:
            znake[i-1][0] = "#"
            continue
        if i%2 == 0:
            znake[i-1][-1] = "#"
            continue
for i in znake:
    print("".join(i))
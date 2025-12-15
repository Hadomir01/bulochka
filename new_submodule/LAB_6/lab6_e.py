tmp = input("Введите карту сокровищ > ").split()
treasures = []
depths = [int(x) for x in tmp]
for i in range(1, len(depths)-1):
    if depths[i-1] < depths[i] and depths[i+1] < depths[i]:
        treasures.append(depths[i])

if len(treasures) != 0:
    max_treasures = max(treasures)
    depths.remove(max_treasures)
    print(depths)
else:
    print(depths) 
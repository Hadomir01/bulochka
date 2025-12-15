turn1 = input("Введите стратовую позицию: ")
turn2 = input("Введите конечную позицию: ")

x1 = ord(turn1[0])
y1 = ord(turn1[1])
x2 = ord(turn2[0])
y2 = ord(turn2[1])

if abs(x2-x1) == abs(y2-y1):
    print("YES")
else:
    print("NO, GOD PLEASE, NO!")
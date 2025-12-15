n = int(input("Сколько комнат в общаге > "))
c = 0 
lst = []
while c != n:
    c += 1
    rooms = input("Сколько мест в комнате занято и сколько всего > ").split()
    lst.append(rooms)
happy = 0
for i in range(0, len(lst)):
    if (int(lst[i][1])-int(lst[i][0])) >= 2:
        happy += 1

print(happy)
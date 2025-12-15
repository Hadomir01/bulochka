import random 
def game():
    lst = []
    c = 0
    # Пусть ОРЕЛ == 0, а РЕШКА == 1
    while True:
        chance = random.randint(0, 1)
        if chance == 0:
            lst.append("О")
        elif chance == 1:
            lst.append("Р")
        c += 1
        for i in range(0, len(lst)-1):
            try:
                if lst[i] == lst[i+1] == lst[i+2]:
                    return lst, c
            except IndexError:
                continue

print(game())
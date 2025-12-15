import random
import string

def generate_license_plate():
    res = ""
    vibor = random.randint(1, 2)

    if vibor == 1: # Старый стиль
        for i in range(3):
            sim = random.choice(string.ascii_uppercase)
            res = res + sim
        for j in range(3):
            sim = random.randint(0, 9)
            res = res + str(sim)
        return f"Старый стиль: {res}"
    elif vibor == 2: # Новый стиль
        for i in range(4):
            sim = random.randint(0, 9)
            res = res + str(sim)
        for j in range(3):
            sim = random.choice(string.ascii_uppercase)
            res = res + sim
        return f"Новый стиль: {res}"

print(generate_license_plate())    
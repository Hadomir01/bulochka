import time
import random
print("Сейчас автомат выведет на экран числа, которые скажут, выйграете вы или нет...")
time.sleep(7)

lst = []
for c in range(0, 6):
    lst.append(random.randint(1, 49))
    c += 1

res = ""
for i in lst:
    res = res + str(i) + " "
print(res)
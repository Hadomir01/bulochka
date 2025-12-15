import matplotlib.pyplot as plt
import random

lst = []
for i in range(1000):
    lst.append(random.randint(0, 1))

plt.hist(lst, edgecolor="blue", color="m")
plt.title("Соотношение монстров")
plt.xlabel("0 - средний рост/1 - отклонение")
plt.ylabel("Кол-во монстров")
plt.grid(axis="y") 
plt.show()

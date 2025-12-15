# Вставка в хроники
with open("for_e.txt", "r", encoding="utf-8") as f:
    lst = f.readlines()

middle = len(lst)//2
reward = input("Какую награду увидел Оракул? > ")
lst.insert(middle, reward + "\n")
with open("for_e.txt", "w", encoding="utf-8") as f:
    f.writelines(lst)


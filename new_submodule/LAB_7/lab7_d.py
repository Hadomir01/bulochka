# Топ имена
dano = input("Сколько вывести имен и каких? > ").split()
with open("file5.txt", encoding="utf-8") as file_f:
    text_f = [x.split() for x in file_f]
with open("file6.txt", encoding="utf-8") as file_m:
        text_m = [x.split() for x in file_m]
if dano[-1] == "ж":
    for i in range(0, int(dano[0])):
        print(text_f[i][0])
else:
    for i in range(0, int(dano[0])):
        print(text_m[i][0])
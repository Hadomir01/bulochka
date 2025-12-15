lst = input("Введите текст > ").split(" ")
if len(lst) != 2:
    while len(lst) != 2:
        print("Ошибка! Некорректное количество слов! Введите два слова!")
        print(lst)
        lst = input("Введите текст > ").split(" ")
        if len(lst) == 2:
            break

string = ""
for i in lst[::-1]:
    string = string + i + " "
print(string)

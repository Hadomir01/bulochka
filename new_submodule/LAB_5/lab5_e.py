def shifr(lst):
    res_1 = ''
    res_2 = ''
    c = 0
    for i in lst:
        c += 1
        if c%2==1:
            res_1 += i
        else:
            res_2 = i + res_2
    return res_1+res_2

while True:
    stroka = input("Введите текст для шифровки > ")
    if "#" in stroka:
        break
    print("Ошибка! Нет символа #")

lst = []
for i in stroka:
    lst.append(i)
lst.remove("#")

print(f"Результат расшифровки: {shifr(lst)}")
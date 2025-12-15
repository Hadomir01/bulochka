rost_1 = int(input("Рост первого: "))
rost_2 = int(input("Рост второго: "))
rost_3 = int(input("Рост третьего: "))
rost_4 = int(input("Рост четвертого: "))
rost_5 = int(input("Рост пятого: "))

lst = [rost_1, rost_2, rost_3, rost_4, rost_5]
lst1= []
for i in lst:
    if i >=0 :
        lst1.append(i)
if len(lst1) == 5:
    print("Не найдено!")
if len(lst1) == 0:
    print("Не найдено!")
if 0 < len(lst1) < 5:
    print(max(lst1))
    print(min(lst1))
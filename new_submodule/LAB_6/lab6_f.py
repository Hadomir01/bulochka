num = input("Пожалуйста, введите номер карты(3 цифры с оборота не надо, дату тоже) > ")
lst = []
sum = 0
for i in num:
    lst.append(int(i))
if len(lst) != 16:
    print("Некорректный номер карты! Не 16 цифр!")
else:
    for n in range(0, len(lst)):
        if n % 2 != 0:
            sum = sum + lst[n]
        else:
            if (lst[n]*2) > 9:
                sum = sum + (lst[n]*2)-9
            else:
                sum = sum + (lst[n]*2)
    if sum % 10 == 0:
        print("Корректный номер карты!")
    else:
        print("Некорректный номер карты! Сумма не кратна 10!") 
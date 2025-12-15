n = int(input("Сколько слов будем преобразовывать? > "))
c = 0
lst = []
while c != n:
    c += 1
    text = input("Введите слово для образования аббревиатуры > ")
    lst.append(text)

new_lst = []
for i in lst:
    if len(i) > 10:
        i = i[0] + f"{len(i)-2}" + i[-1]
        new_lst.append(i)
    else:
        new_lst.append(i)

for n in new_lst:
    print(n)
numb = int(input("Сколько сообщений? > "))
tmp = []

check = input("Что проверяем... > ")
for i in check:
    tmp.append(i)

c = 0
s = 0

for i in tmp:
    if i == "+": 
        c += 1
    else:
        c -= 1
    
    if c < 0:
        s = 1
        break

if c != 0:
    s = 1

if s == 0:
    print("Все хорошо, регламент выполнен")
else:
    print("Есть нарушения регламента")
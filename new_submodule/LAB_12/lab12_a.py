while True:
    try:
        count = int(input("Число экипажа корабля > "))
    except ValueError:
        print("Пожалуйста, введите число!")
    else:
        break

n = 0
lst_name = []
code = ["woman", "child", "man", "captain"]
while n < count:
    while True:
        name = input("Член экипажа > ")
        if name.isdigit():
            print("Пожалуйста, укажите имя и кто это! 1")
        elif len(name.split()) != 2:
            print("Пожалуйста, укажите имя и кто это! 2")
        else:
            role = name.split()[1].lower()
            if role not in code:
                print("Пожалуйста, укажите имя и кто это! 3")
            else:
                lst_name.append(name.split())
                break
    n += 1

def get_weight(role):
    if role == "woman" or role == "child": 
        return 0
    elif role == "man":
        return 1
    elif role == "captain":
        return 2

lst_name.sort(key=lambda x: get_weight(x[1]))

res = ""
for i in lst_name:
    res += i[0]
print(res)
stroka = input("Введите текст > ")
if len(stroka) > 2:
    res = '.'.join(stroka)
    print(res)
else:
    print(stroka)
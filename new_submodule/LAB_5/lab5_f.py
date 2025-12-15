import random
import string

def gen_pass(len_pass, up_sumb, low_sumb, nums, spec_sumb):
    sp_str = "`~!@#№$;%^:&?*(_-+={[]}<?|>)"
    
    psevdo_pass = ""
    if up_sumb == "да":
        for i in range(0, len_pass):
            psevdo_pass += random.choice(string.ascii_uppercase)
    if low_sumb == "да":
        for i in range(0, len_pass):
            psevdo_pass += random.choice(string.ascii_lowercase)
    if nums == "да":
        for i in range(0, len_pass):
            psevdo_pass += str(random.randint(0,9))
    if spec_sumb == "да":
        for i in range(0, len_pass):
            psevdo_pass += random.choice(sp_str)
    print(psevdo_pass)
    
    lst = []
    for i in set(psevdo_pass):
        lst.append(i)
        if len(lst) == len_pass:
            break
    
    res = ""
    for i in lst:
        res = i + res

    return res

print("=== Добро пожаловать в систему создания паролей! ===")
print("Уверяем Вас, созданные пароли не сохраняются и не передаются в прокуратуру!")
print("Давайте настроим ваш будущий пароль!")

while True:
    try:
        len_pass = int(input("Введите желаемую длину пароля > "))
    except ValueError:
        print("Ошибка! Необходимо целое число!")
    else:
        if len_pass == 0:
            print("Не стоит ломать вселенную паролем из нуля символов...")
        else:
            break

while True:
    up_sumb = input("Нужны ли заглавные буквы? > ")
    if up_sumb.lower() != "да" and up_sumb.lower() != "нет":
        print("Ошибка! Необходимо ответить да или нет")
    else:
        break
while True:
    low_sumb = input("Нужны ли строчные буквы? > ")
    if low_sumb.lower() != "да" and low_sumb.lower() != "нет":
        print("Ошибка! Необходимо ответить да или нет")
    else:
        break
while True:
    nums = input("Нужны ли цифры? > ")
    if nums.lower() != "да" and nums.lower() != "нет":
        print("Ошибка! Необходимо ответить да или нет")
    else:
        break
while True:
    spec_sumb = input("Нужны ли специальные символы? > ")
    if spec_sumb.lower() != "да" and spec_sumb.lower() != "нет":
        print("Ошибка! Необходимо ответить да или нет")
    else:
        break

print(f"Ваш пароль готов: {gen_pass(len_pass, up_sumb, low_sumb, nums, spec_sumb)}")
text = input("Введите слово > ")
shift = int(input("На сколько смещяем? > "))
mod = int(input("Выберите режим шифрования(1) или дешифрования(2) > "))
text_new = ""
base_a = ord("a")
base_A = ord("A")
if mod == 1:
    for i in text:
        if i.isalpha():
            if i.isupper():
                text_new = text_new + chr((ord(i) - base_A + shift) % 26 + base_A)
            else:
                text_new = text_new + chr((ord(i) - base_a + shift) % 26 + base_a)
        else:
            text_new = text_new + i
elif mod == 2:
    for i in text:
        if i.isalpha():
            if i.isupper():
                text_new = text_new + chr((ord(i) - base_A - shift) % 26 + base_A)
            else:
                text_new = text_new + chr((ord(i) - base_a - shift) % 26 + base_a)
        else:
            text_new = text_new + i
print(text_new)
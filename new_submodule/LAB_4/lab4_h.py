stroka = input("Введите строку: ")

# === Объявление переменных ===
bukva = 0
number = 0
spases = 0
znaks = 0
word_count = 0


dlina_stroka = len(stroka)

# === Проверка на символы ===
for i in stroka:
    if i.isalpha():
        bukva += 1
    elif i.isdigit():
        number += 1
    elif i.isspace():
        spases += 1
    else:
        znaks += 1


# === Проверки строки ===
if all(k.isalpha() for k in stroka):
    word_count = 1
    simb = "В исходной строке только буквы!"
elif all(k.isdigit() for k in stroka):
    simb = "В исходной стороке только числа!"
else:
    word_count = 1


# === Изменение регистра ===
new_stroka = stroka.capitalize()


# === Подсчет количества слов ===
for l in range(0, len(new_stroka)-1):
    try:
        if new_stroka[l].isspace() and new_stroka[l+1].isalpha():
            word_count += 1
        else:
            continue
    except:
        break
    

# === Замена гласных ===
glasnie = "аеёиоуыэюяАЕЁИОУЫЭЮЯ"
glasnie_stroka = new_stroka
for j in glasnie_stroka:
    if j in glasnie:
        glasnie_stroka = glasnie_stroka.replace(j, "*")


# === Самое длинное слово ===
t_word = ""
long_word = ""
for m in new_stroka:
    if m.isalpha():
        t_word += m
    else:
        if len(t_word) > len(long_word):
            long_word = t_word
        t_word = ""


# === Красивый вывод анализа ===
print("=== АНАЛИЗ ТЕКСТА ===")


print(f"Исходная строка: {stroka}")
print(f"Строка после обработки: {new_stroka}")
print(f"Длина строки: {dlina_stroka}")
print(f"Слов: {word_count}")
print(f"Самое длинное слово: {long_word}")
print(f"Букв: {bukva}")
print(f"Чисел: {number}")
print(f"Пробелов: {spases}")
print(f"Знаков препинания: {znaks}")
print(f"Строка без гласных: {glasnie_stroka}")


if stroka[0].isupper():
    print("Исходная строка начинается с заглавной буквы!")

if stroka[-1] == ".":
    print("Исходная строка заканчивается точкой")
elif stroka[-1] == "!":
    print("Исходная строка заканчивается знаком восклицания")
elif stroka[-1] == "?":
    print("Исходная строка заканчивается знаком вопроса")


search = input("Что будем искать? > ")
if search in new_stroka:
    print("Найдено!")
    repl = input("На что поменяем? > ")
    repl_stroka = new_stroka.replace(search, repl)
    print(f"Результат замены: {repl_stroka}")
else:
    print("Не найдено!")

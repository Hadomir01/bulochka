text = input("Введите строку: ")
result = ""

for bukva in text:
    if bukva.isalpha():
        result += bukva

print("Результат:", result)

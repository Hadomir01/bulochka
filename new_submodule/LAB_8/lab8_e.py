def decode_postal_code(code):
    # (формат L1 D1 L2 D2)
    L1 = {
        "A": "Солнечный Берег",
        "B": "Зеленые Холмы",
        "C": "Изумрудная Долина",
        "E": "Киберсити",
        "G": "Жемчужный Берег",
        "H": "Туманный Лес",
        "J": "Пламенный Утес",
        "K": "Звездный Ручей",
        "L": "Солнечная Гавань",
        "M": "Лунная Роща"
    }
    L2_основ = "ABCDEFGHIJKLM"
    D1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    D2_стандарт = [0, 1, 2]
    D2_ускор = [3, 4, 5, 6]
    D2_экспресс = [7, 8, 9]

    code = code.upper()
    code = code.split(" ")

    if len(code) != 4:
        return (f"Ввод не корректен!") 

    if (code[0].isalpha() and code[2].isalpha() and code[1].isdigit() and code[3].isdigit()) and (code[0] in L1):
        if int(code[3]) in D2_стандарт:
            k = "Стандартная"
        elif int(code[3]) in D2_ускор:
            k = "Ускоренная"
        elif int(code[3]) in D2_экспресс:
            k = "Экспресс"

        print(f"Регион: {L1[code[0]]}")
        print(f"Тип населенного пункта: {"Город" if int(code[1]) in D1 else "Сельская местность"}")
        print(f"Тип почтивого отделения: {"Основное отделение" if code[2] in L2_основ else "Дополнительное отделение"}")
        print(f"Срочность доставки: {k}")
    else:
       return (f"Ввод не корректен! Неверный формат записи")

print(decode_postal_code(input("Код доставки > ")))
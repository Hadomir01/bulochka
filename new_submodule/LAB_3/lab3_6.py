month = str(input("Напишите название месяца: "))
month = month.lower()

match month:
    case "январь":
        print("31")
    case "февраль":
        print("28 или 29")
    case "март":
        print("31")
    case "апрель":
        print("30")
    case "май":
        print("31")
    case "июнь":
        print("30")
    case "июль":
        print("31")
    case "август":
        print("31")
    case "сентябрь":
        print("30")
    case "октябрь":
        print("31")
    case "ноябрь":
        print("30")
    case "декабрь":
        print("31")
    case _:
        print("месяц не набран") 
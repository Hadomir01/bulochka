def score(text):
    a1 = text.split("-")
    team1 = a1[0]
    a1 = a1[1]
    a2 = a1.rsplit(" ", 1)
    team2 = a2[0]
    a2 = a2[1]
    a3 = a2.split(":")
    goal1 = a3[0]
    goal2 = a3[1]

    if goal1 == goal2:
        return "Ничья"
    elif goal1 > goal2:
        return f"Победитель: {team1}"
    elif goal2 > goal1:
        return f"Победитель: {team2}"

while True:
    text = input("Введите название команд через тире и счет игры через двоеточие > ")
    if "-" not in text or ":" not in text:
        print("Ошибка ввода данных!")
    else:
        break

print(score(text))
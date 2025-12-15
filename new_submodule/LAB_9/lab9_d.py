import matplotlib.pyplot as plt

lst = []
with open("5.txt", encoding="utf-8") as f:
    for i in f:
        i = i.strip()
        lst.append(i.split(";"))

animals = ["Олени", "Кабаны", "Лисы"]
month = ["Январь 2025", "Февраль 2025", "Март 2025", "Апрель 2025", "Май 2025", "Июнь 2025", "Июль 2025", "Август 2025", "Сентябрь 2025", "Октябрь 2025", "Ноябрь 2025", "Декабрь 2025"]
axis_x = ["Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"]
animal_counting = {
    "Олени": "",
    "Кабаны": "",
    "Лисы": ""
}

sum_all_animals = 0
for i in lst:
    if i[2].isdigit():
        sum_all_animals += int(i[2])
    else:
        continue

m = 0
month_count = 0
axis_y = []
while True:
    for i in lst:
        if i[2].isdigit() and i[1] in animals:
            if i[0] == month[m]:
                month_count += int(i[2])
    axis_y.append(month_count)
    m += 1
    month_count = 0
    if m == 12:
        break

a = 0
anim_count = 0
tmp = []
while True:
    for i in lst:
        if i[2].isdigit() and i[1] in animals:
            if i[1] == animals[a]:
                anim_count += int(i[2])
    tmp.append(anim_count)
    a += 1
    anim_count = 0
    if a == 3:
        break

for i, an in enumerate(animal_counting):
    animal_counting[an] = tmp[i]

spad = 0
month_spad = 0
for i in range(0, len(axis_y)-1):
    if axis_y[i] - axis_y[i+1] < spad:
        month_spad = axis_x[i]

print(f"Всего обнаружено: {sum_all_animals}")
print(f"Обнаружений по месяцам: {axis_y}")
print(f"Самые часто замечаемые животные: {max(animal_counting, key=animal_counting.get)}")
print(f"Месяц, в котором наблюдается резкий спад активности животных: {month_spad}")

plt.bar(axis_x, axis_y)
for i in range(len(axis_x)):
    plt.text(axis_x.index(axis_x[i])-0.125, axis_y[i], f'{axis_y[i]}', fontsize=10)

plt.xlabel("Месяцы(2025 г.)")
plt.ylabel("Обнаружение животных(разы)")
plt.title("Активность животных по месяцам")
plt.show()
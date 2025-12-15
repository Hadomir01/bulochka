import matplotlib.pyplot as plt
pizza_name = ["«Маргарита Мания»", "«ПепперониПарад»", "«Гавайский Хаос»", "«Четыре Сыра и Слёзы»", "«Веганский Бунт»"]
saled = [23, 45, 56, 78, 32]

plt.bar(pizza_name, saled, color="m")
plt.xlabel("Пиццерии")
plt.ylabel("Продажи за неделю")
plt.title("Рейтинг пиццерий по продажам")
plt.title(f"Победитель чемпионата - {pizza_name[saled.index(max(saled))]}")
plt.show()
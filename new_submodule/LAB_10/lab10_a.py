import matplotlib.pyplot as plt
import seaborn as sns

start = ""
start_list = []
while True:
    start = str(input("Набирайте имена друзей и их рост > "))
    if start == "":
        break
    else:
        start_list.append(start.split())

name = []
height = []
uniq = []
names = {}

for i in start_list:
    name.append(i[0])
    height.append(int(i[1]))

for i in name:
    if i in names:
        names[i] += 1
        uniq.append(f"{i}_{names[i]}")
    else:
        names[i] = 1
        uniq.append(i)

colors_ = sns.color_palette('deep', len(name))

fig, ax = plt.subplots(figsize=(10, 5))
bars = plt.bar(uniq, height, color=colors_)

for i, (bar, height) in enumerate(zip(bars, height)):
    ax.text(bar.get_x() + bar.get_width()/2, height/2, f'{height}', ha='center', va='center', fontsize=10, fontweight="bold")

plt.xlabel("Друзья")
plt.ylabel("Рост")
plt.xticks(rotation=45)
plt.title("Сравнение роста друзей")
plt.tight_layout()
plt.show()
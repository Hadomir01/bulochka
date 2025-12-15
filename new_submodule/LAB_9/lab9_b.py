import matplotlib.pyplot as plt

sizes = [8, 7, 5, 4]
label = ["спасение мира", "сон", "культурный отдых", "поедание доширака"]

plt.pie(sizes, labels=label, autopct="%1.2f%%", startangle=0)

plt.title("Распорядок дня супер-героя Алексея")
plt.show()

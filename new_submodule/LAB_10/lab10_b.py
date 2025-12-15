from random import randint, choice
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def check(num):
    if num > 100:
        num = 100
    elif num < 0:
        num = 0
    return num

def chance():
    ch = randint(1, 10)
    return ch

energy = 100
happiness = 50
hours = [h for h in range(24)]
sleep = []
happy = []
events = [("Питомец вспомнил хороший день", 15), ("Нашёл конфету", 20), ("Увидел бабочку", 8), ("Захотел танцевать", 12)]

for h in range(0, 24):
    for m in range(0, 60):
        if h >= 6 and h <= 23:
            if h >= 7 and h < 23 and m == 0:
                if chance() == 10:
                    event = choice(events)
                    happiness = int(check(happiness+event[1]))
                    print(f"Время {h}:{m:02d} Событие: '{event[0]}' | Настроение: {happiness}")
            if h == 6 and m == 0:         
                print(f"Время {h}:{m:02d} Питомец проснулся! Доброе утро!")
            if h == 9 and m == 0:
                energy = check(energy+10)
                print(f"Время {h}:{m:02d} Пора кушать! 'Энергия + 10' | Энергия {int(energy)} | Настроение {int(happiness)}")
            if h == 14 and m == 25:
                energy = check(energy+10)
                print(f"Время {h}:{m:02d} Пора кушать! 'Энергия + 10' | Энергия {int(energy)} | Настроение {int(happiness)}")
            if h == 19 and m == 34:
                energy = check(energy+10)
                print(f"Время {h}:{m:02d} Пора кушать! 'Энергия + 10' | Энергия {int(energy)} | Настроение {int(happiness)}")
            if h == 23 and m == 0:
                print(f"Время {h}:{m:02d} Питомец пошел спать! Спокойной ночи!")
        if h >= 6 and h < 23 and m == 59:
            energy = check(energy-(energy*0.05))
            happiness = check(happiness-(happiness*0.05))
            print(f"Время {h}:{m:02d} | Энергия {int(energy)} | Настроение {int(happiness)}")
        if h < 6 and m == 59:
            print(f"Время {h}:{m:02d} | Энергия {int(energy)} | Настроение {int(happiness)}")
        if h >= 23 and m == 59:
            energy = check(energy+(energy*0.05))
            print(f"Время {h}:{m:02d} | Энергия {int(energy)} | Настроение {int(happiness)}")
    sleep.append(int(energy))
    happy.append(int(happiness))

fig, ax = plt.subplots()
grapf_sleep = ax.plot([], [], label="Энергия", color="b", linestyle="--")[0]
grapf_happy = ax.plot([], [], label="Настроение", color="orange", linestyle="--")[0]

def anim(frame):
    x_1_animation = hours[:frame+1]
    y_1_animation = sleep[:frame+1]
    y_2_animation = happy[:frame+1]

    grapf_sleep.set_data(x_1_animation,y_1_animation)
    grapf_happy.set_data(x_1_animation,y_2_animation)
    return grapf_sleep, grapf_happy, 

ani = FuncAnimation(fig, anim, frames=30, interval=100, repeat=False)
ax.set_xlim(0, 23)
ax.set_ylim(0, 105)
ax.set_xticks(hours)
ax.grid(True, alpha=0.5)
ax.legend()
ax.set_xlabel("Время (часы)")
ax.set_ylabel("Динамика")
plt.show()
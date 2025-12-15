import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from random import choice
import math
vector = ["св", "юг", "вс", "зп", "с-в", "с-з", "ю-в", "ю-з"]
x = 0
y = 0
axis_x = []
axis_y = []

for i in range(10000):
    p_vec = choice(vector)
    match p_vec:
        case "св":
            x += 1
        case "юг":
            x -= 1
        case "вс":
            y += 1
        case "зп":
            y -= 1
        case "с-в":
            x += 1
            y += 1
        case "с-з":
            x += 1
            y -= 1
        case "ю-в":
            x -= 1
            y += 1
        case "ю-з":
            x -= 1
            y -= 1
    axis_x.append(x)
    axis_y.append(y)

fig, ax = plt.subplots(figsize=(8, 10))

pirat = ax.plot([], [])[0]
point = ax.plot([], [], 'ro', markersize=8)[0]

# ax.spines['bottom'].set_position('zero')
# ax.spines['left'].set_position('zero')
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

max_x = 3
max_y = 3
ax.set_xlim(-max_x, max_x)
ax.set_ylim(-max_y, max_y)

def anime(frame):
    global max_x, max_y
    x_pirat_animation = axis_x[:frame+1]
    y_pirat_animation = axis_y[:frame+1]

    x_point_animation = axis_x[frame]
    y_point_animation = axis_y[frame]

    if math.fabs(x_point_animation) >= max_x:
        max_x += 2
        ax.set_xlim(-max_x, max_x)

    if math.fabs(y_point_animation) >= max_y:
        max_y += 2
        ax.set_ylim(-max_y, max_y)

    pirat.set_data(x_pirat_animation, y_pirat_animation)
    point.set_data([x_point_animation], [y_point_animation])

    return pirat, point

ani = FuncAnimation(fig, anime, frames=10000, interval=100, repeat=False, blit=True)

plt.show()
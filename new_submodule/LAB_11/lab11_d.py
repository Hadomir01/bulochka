import tkinter as tk
from PIL import Image, ImageTk

window = tk.Tk()
window.title("Программа")
window.geometry("600x600")
gif_size = (300, 300)

try:
    gif = Image.open(r"C:\Users\Даник\Downloads\sur.gif")
    frames = []
    gif_size = (300, 300)
    
    for frame in range(gif.n_frames):
        gif.seek(frame)
        resized_frame = gif.copy().resize(gif_size, Image.Resampling.LANCZOS)
        frames.append(ImageTk.PhotoImage(resized_frame))
    
    gif_label = tk.Label(window)
    gif_label.pack(pady=20)
    
    def animate_gif(frame=0):
        if frames:
            gif_label.configure(image=frames[frame])
            frame = (frame + 1) % len(frames)
            window.after(50, animate_gif, frame)
except:
    print("Гифка не найдена или произошла ошибка загрузки")

c = 0
def determination():
    global c
    c += 1
    if c == 7:
        text.configure(text="А ты настойчив! Вот тебе награда: ты победил!")
    if c == 20:
        text.configure(text="Стоп, почему ты не перестаёшь кликать?")
        window.title("Программа?")
    if c == 27:
        text.configure(text="Хватит!")
    if c == 40:
        text.configure(text="Тебе что, надо несколько раз повторять?")
    if c == 54:
        text.configure(text="ХВАТИТ!")
    if c == 72:
        text.configure(text="Я что для тебя какая-то шутка? Или что?")
        window.title("программа...")
    if c == 93:
        text.configure(text="Ну все, ты меня разозлил!")
        button.configure(fg="red")
    if c == 126:
        text.configure(text="Все, хватит это терпеть!")
    if c == 151:
        text.configure(text="РИКРОООООООЛЛЛЛ")
        window.title("РИКРОООООООЛЛЛЛ")
        animate_gif()
        button.pack_forget()

text = tk.Label(window, text="", font=("Comic Sans MS", 15, "bold"), fg="#D5990B")
text.pack(pady=110)

button = tk.Button(window, text="Запустить", font=(("Georgia", 10, "bold")), command=determination)
button.pack(expand=True)

window.mainloop()
import tkinter as tk
from random import randint

window = tk.Tk()
window.title("Угадай число!")
window.geometry("500x500")
window.configure(bg="#CCCCFF")

quest = randint(1, 100)
c = 0

def game():
    global c
    num = int(enter.get())
    enter.delete(0, tk.END)

    if num > quest:
        c += 1
        ans.configure(text="Не, число меньше", fg="red")
    elif num < quest:
        c += 1
        ans.configure(text="Не, число больше", fg="red")
    else:
        c += 1
        ans.configure(text=f"Ура! Ты угадал!\n Попыток: {c}", fg="green")
    

enter = tk.Entry(window, font=("Georgia", 16))
enter.pack(pady=180)

text = tk.Label(window, text="Игра - Угадай число!", font=("Comic Sans MS", 18, "bold"), bg="#CCCCFF", fg="#333366")
text.place(x=120, y=135)

button = tk.Button(window, text="Угадать", font=(("Comic Sans MS", 12, "bold")), command=game)
button.place(x=205, y=220)

ans = tk.Label(window, text="", font=(("Comic Sans MS", 12, "bold")), bg="#CCCCFF")
ans.place(x=180, y= 270)

window.mainloop()
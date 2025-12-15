import tkinter as tk
from random import randint

window = tk.Tk()
window.title("Mini game")
window.geometry("400x400")
window.resizable(False, False)
window.configure(bg="#CCCCFF")

num = randint(1, 4)

def choose_correct(c):
    if num != c:
        ans.configure(text="Не то...", fg="red")
    else:
        ans.configure(text="Ура! Ты нашел секрет!", fg="green")


b1 = tk.Button(window, text="Нажми меня", font=(("Georgia", 10, "bold")), command=lambda:choose_correct(1))
b1.place(x=35, y=100)

b2 = tk.Button(window, text="Нажми меня", font=(("Georgia", 10, "bold")), command=lambda:choose_correct(2))
b2.place(x=265, y=100)

b3 = tk.Button(window, text="Нажми меня", font=(("Georgia", 10, "bold")), command=lambda:choose_correct(3))
b3.place(x=35, y=250)

b4 = tk.Button(window, text="Нажми меня", font=(("Georgia", 10, "bold")), command=lambda:choose_correct(4))
b4.place(x=265, y=250)

ans = tk.Label(font=("Comic Sans MS", 18, "bold"), bg="#CCCCFF")
ans.pack(pady=175)

window.mainloop()
import tkinter as tk
from random import choice

window = tk.Tk()
window.title("Твое будущее")
window.geometry("400x400")
window.resizable(False, False)
window.configure(bg="#BCDBBC")

def func():
    words = ["Ты сегодня сделаешь что-то крутое!", "Сегодня — хороший день для чая.", "Твоя следующая оценка — 5!", "Верь в себя и у тебя всё получится!"]
    wish.configure(text=f"{choice(words)}")

string = tk.Label(window, text="Узнай свою судьбу...", font=("Times New Roman", 18), bg="#BCDBBC")
string.pack(pady=150)

button = tk.Button(window, text="Узнать судьбу!", font=(("Times New Roman", 12)), width=16, command=func)
button.pack(pady=10)

wish = tk.Label(window, font=("Times New Roman", 18), bg="#BCDBBC")
wish.place(relx=0.5, y=200, anchor="center")

window.mainloop()
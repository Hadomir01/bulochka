import tkinter as tk

window = tk.Tk()
window.title("Окно-светофор")
window.geometry("500x500")

def change_color_red():
    window.configure(bg="red")
def change_color_yellow():
    window.configure(bg="yellow")
def change_color_green():
    window.configure(bg="green")

r = tk.Button(window, bg="red", command=change_color_red, width=1)
r.place(x=5, y=5)
y = tk.Button(window, bg="yellow", command=change_color_yellow, width=1)
y.place(x=20, y=5)
g = tk.Button(window, bg="green", command=change_color_green, width=1)
g.place(x=35, y=5)

window.mainloop()
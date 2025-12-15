import tkinter as tk
from random import choice
from PIL import Image, ImageTk

window = tk.Tk()
window.title("Прогнозёр погоды")
window.geometry("450x350")

images = {}

images["sun"] = ImageTk.PhotoImage(Image.open(r"C:\Users\Даник\Desktop\Wowork\LAB_12\sun.jpg").resize((200, 200)))
images["rain"] = ImageTk.PhotoImage(Image.open(r"C:\Users\Даник\Desktop\Wowork\LAB_12\rain.jpg").resize((200, 200)))
images["wind"] = ImageTk.PhotoImage(Image.open(r"C:\Users\Даник\Desktop\Wowork\LAB_12\wind.jpg").resize((200, 200)))
images["storm"] = ImageTk.PhotoImage(Image.open(r"C:\Users\Даник\Desktop\Wowork\LAB_12\storm2.jpg").resize((200, 200)))
images["snow"] = ImageTk.PhotoImage(Image.open(r"C:\Users\Даник\Desktop\Wowork\LAB_12\snow.jpg").resize((200, 200)))

pogoda = ["☀️ Солнечно", "🌧️ Дождь", "💨 Ветрено", "⛈️ Гроза", "❆ Снег"]
def prognoz():
    p = choice(pogoda)
    if p == pogoda[0]:
        weather.configure(text="☀️ Солнечно", bg="#FFD700", fg="#8B4513")
        window.configure(bg="#FFD700")
        button.configure(bg="#FFA500")
        kartinka.configure(image=images["sun"])
    elif p == pogoda[1]:
        weather.configure(text="🌧️ Дождь", bg="#87CEEB", fg="#191970")
        window.configure(bg="#87CEEB")
        button.configure(bg="#4682B4")
        kartinka.configure(image=images["rain"])
    elif p == pogoda[2]:
        weather.configure(text="💨 Ветрено", bg="#E6E6FA", fg="#2F4F4F")
        window.configure(bg="#E6E6FA")
        button.configure(bg="#D8BFD8")
        kartinka.configure(image=images["wind"])
    elif p == pogoda[3]:
        weather.configure(text="⛈️ Гроза", bg="#483D8B")
        window.configure(bg="#483D8B")
        weather.configure(fg="white")
        button.configure(bg="#6A5ACD")
        kartinka.configure(image=images["storm"])
    elif p == pogoda[4]:
        weather.configure(text="❆ Снег", bg="#F5F5F5")
        window.configure(bg="#F5F5F5")
        weather.configure(fg="#2C3E50")
        button.configure(bg="#7FB3D5")
        kartinka.configure(image=images["snow"])

weather = tk.Label(window, text="", font=("Arial", 14, "bold"))
weather.grid(row=0, column=0, columnspan=2, pady=20, padx=20)

kartinka = tk.Label(window)
kartinka.grid(row=1, column=0, columnspan=2)

button = tk.Button(window, text="Спрогнозировать", font=("Arial", 14, "bold"),bg="lightblue", command=prognoz)
button.grid(row=2, column=0, columnspan=2, padx=55, pady=10)

window.grid_rowconfigure(0, weight=1)
window.grid_columnconfigure(0, weight=1)

window.mainloop()
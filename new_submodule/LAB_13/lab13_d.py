import tkinter as tk
from tkinter import ttk, messagebox as msg
from PIL import Image, ImageTk
from random import choice

window = tk.Tk()
window.geometry("500x650")
window.title("Игра 'Виселица'")

images = {}

images[0] = ImageTk.PhotoImage(Image.open(r"LAB_13\6_left.png").resize((225, 225)))
images[1] = ImageTk.PhotoImage(Image.open(r"LAB_13\5_left.png").resize((225, 225)))
images[2] = ImageTk.PhotoImage(Image.open(r"LAB_13\4_left.png").resize((225, 225)))
images[3] = ImageTk.PhotoImage(Image.open(r"LAB_13\3_left.png").resize((225, 225)))
images[4] = ImageTk.PhotoImage(Image.open(r"LAB_13\2_left.png").resize((225, 225)))
images[5] = ImageTk.PhotoImage(Image.open(r"LAB_13\1_left.png").resize((225, 225)))
images[6] = ImageTk.PhotoImage(Image.open(r"LAB_13\game_over.png").resize((225, 225)))

used = set()
unused = set()
# 11223434BA

def update_bukv():
    global used, unused
    used_text = "Использованные:\n" + " ".join(sorted(used))
    
    rus = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
    sorted_unused = []
    
    for letter in rus:
        if letter in unused:
            sorted_unused.append(letter)
    
    unused_text = "Неиспользованные:\n" + " ".join(sorted_unused)
    
    used_l.config(text=used_text)
    unused_l.config(text=unused_text)

def start_window():
    global categories
    def vibor_temi():
        global tema
        tema = menu.get()
        if tema and tema != "Выберите тему..." and tema in list(categories.keys()):
            new_game.destroy()
            start_game()

    categories = {
    "Фрукты": ["Яблоко", "Банан", "Апельсин", "Киви", "Виноград", "Персик", "Груша", "Ананас"],
    "Школа": ["Учебник", "Учитель", "Дневник", "Класс", "Урок", "Перемена", "Портфель", "Доска"],
    "Спорт": ["Футбол", "Баскетбол", "Теннис", "Плавание", "Бег", "Велосипед", "Гимнастика", "Волейбол"],
    "Архитектура": ["Фасад", "Арка", "Колонна", "Купол", "Фронтон", "Портал", "Капитель", "Контрфорс"],
    "Астрономия": ["Галактика", "Туманность", "Созвездие", "Астероид", "Метеорит", "Квазар", "Пульсар", "Экзопланета"],
    "Литературные жанры": ["Поэма", "Новелла", "Эссе", "Сонет", "Баллада", "Панегирик", "Гротеск", "Притча"],
    "Медицина": ["Диагноз", "Анамнез", "Терапия", "Реабилитация", "Профилактика", "Патология", "Этиология", "Симптом"]
    }

    new_game = tk.Frame(window)
    new_game.place(relx=0.5, rely=0.3, anchor="center")

    nazvanie_igry = tk.Label(new_game, text="Виселица", font=("Times New Roman", 26))
    nazvanie_igry.pack(pady=130)
    menu = ttk.Combobox(new_game, values=list(categories.keys()), font=("System", 9))
    menu.set("Выберите тему...")
    menu.pack()

    knopka = tk.Button(new_game, text="Начать игру!", font=("Times New Roman", 14), command=vibor_temi)
    knopka.pack(pady=60)

def start_game():
    global used, unused, used_l, unused_l
    def check_bukvu():
        nonlocal attempts

        if easter_egg == "11223434" and ent_bukva.get() == "ba":
            msg.showinfo("Konami code!", "Поздравляю! Вы нашли пасхалку!\n" \
            "Держи +30 попыток")
            attempts += 30 
            l3.configure(text=f"Попыток осталось: {attempts}")
            easter_egg == ""
            return

        bukva = ent_bukva.get().upper()
        ent_bukva.delete(0, tk.END)

        if not bukva:
            return
        
        if len(bukva) != 1:
            msg.showwarning("Ошибка", "Введите только одну букву!")
            return

        if bukva not in "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ":
            msg.showwarning("Ошибка", "Введите русскую букву!")
            return
        
        if bukva in used:
            msg.showwarning("Буква уже использована", f"Буква '{bukva}' уже была использована!")
            return

        used.add(bukva)
        unused.discard(bukva)
        update_bukv()

        if bukva in quest_up:
            for i, simb in enumerate(quest_up):
                if simb == bukva:
                    display_quest_list[i] = bukva

            display_quest_text = " ".join(display_quest_list)
            l1.config(text=display_quest_text)

            if "_" not in display_quest_list:
                ans = msg.askyesno("Ура! Победа!", "Поздравляем! Слово отгадано! \n" \
                f"Слово: {quest}\n" \
                "Хотите сыграть ещё?")
                if ans:
                    game_wind.destroy()
                    used.clear()
                    unused.clear()
                    start_window()
                else:
                    window.destroy()
        else:
            attempts -= 1
            l3.configure(text=f"Попыток осталось: {attempts}")
            if attempts >= 0 and attempts <= 6:
                image_index = max(0, min(6, 6 - attempts))
                hangman_label.config(image=images[image_index])

        if attempts == 0:
            ans = msg.askyesno("Поражение", "Увы, но вы проиграли... \n" \
                f"Было загадано слово {quest}\n" \
                "Попробуете снова?")
            if ans:
                game_wind.destroy()
                used.clear()
                unused.clear()
                start_window()
            else:
                window.destroy()
    
    def for_easter_egg(x):
        nonlocal easter_egg
        if x.keysym == 'Up':
            easter_egg += "1"
        elif x.keysym == 'Down':
            easter_egg += "2"
        elif x.keysym == 'Left':
            easter_egg += "3"
        elif x.keysym == 'Right':
            easter_egg += "4"
    
    quest = choice(categories[tema])
    quest_up = quest.upper()
    display_quest_list = ["_" for i in quest_up]
    display_quest = ""
    attempts = 6
    easter_egg = ""
    
    used.clear()
    unused = set("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ")

    for i in quest:
        display_quest += "_ "
    
    game_wind = tk.Frame(window)
    game_wind.place(relx=0.5, anchor="n")
    
    l = tk.Label(game_wind, text=f"Категория: {tema}", font=("Times New Roman", 18))
    l.grid(row=0, column=0, columnspan=2, pady=10)
    
    l1 = tk.Label(game_wind, text=f"{display_quest}", font=("Times New Roman", 18))
    l1.grid(row=1, column=0, columnspan=2, pady=10)

    used_l = tk.Label(game_wind, text="Использованные: ", font=("Times New Roman", 11), fg="red")
    used_l.grid(row=2, column=0, columnspan=2, pady=5)
    
    unused_l = tk.Label(game_wind, text="Неиспользованные: ", font=("Times New Roman", 11), fg="green")
    unused_l.grid(row=3, column=0, columnspan=2, pady=5)

    l2 = tk.Label(game_wind, text="Буква:", font=("Times New Roman", 14))
    l2.grid(row=4, column=0, pady=10)

    ent_bukva = tk.Entry(game_wind, width=10, font=("Times New Roman", 14))
    ent_bukva.grid(row=4, column=1, pady=10)

    l3 = tk.Label(game_wind, text=f"Попыток осталось: {attempts}", font=("Times New Roman", 14))
    l3.grid(row=5, column=0, pady=10, columnspan=2)
    
    check_button = tk.Button(game_wind, text="Проверить", font=("Times New Roman", 14), command=check_bukvu)
    check_button.grid(row=6, column=0, columnspan=2, pady=10)

    hangman_label = tk.Label(game_wind, image=images[0])
    hangman_label.image = images[0]
    hangman_label.grid(row=7, column=0, columnspan=2, pady=5)

    ent_bukva.bind('<Return>', lambda x: check_bukvu())
    ent_bukva.bind('<Up>', for_easter_egg)
    ent_bukva.bind('<Down>', for_easter_egg)
    ent_bukva.bind('<Left>', for_easter_egg)
    ent_bukva.bind('<Right>', for_easter_egg)
    
    update_bukv()

start_window()

window.mainloop()
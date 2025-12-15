import tkinter as tk
from tkinter import messagebox as msg

window = tk.Tk()
window.geometry("450x400")
window.title("Сравниватель списков")

def on_entry_click(event, entry, placeholder):
    if entry.get() == placeholder:
        entry.delete(0, "end") 
        entry.config(fg='black')

def on_focus_out(event, entry, placeholder):
    if entry.get() == '':
        entry.insert(0, placeholder)  
        entry.config(fg='grey') 

def on_enter_key(event, n):
    add(n)

def add(n):
    if n == 1:
        text = enter1.get()
        if text and text != "Введите слово":
            listbox1.insert(tk.END, text)
            enter1.delete(0, tk.END)
            enter1.insert(0, "Введите слово")
            enter1.config(fg='grey')
            msg.showinfo("Успех", f"Слово '{text}' успешно добавлено")
        else:
            msg.showerror("Ошибка", f"Заполните поле")
    else:
        text = enter2.get()
        if text and text != "Введите слово":
            listbox2.insert(tk.END, text)
            enter2.delete(0, tk.END)
            enter2.insert(0, "Введите слово")
            enter2.config(fg='grey')
            msg.showinfo("Успех", f"Слово '{text}' успешно добавлено")
        else:
            msg.showerror("Ошибка", f"Заполните поле")

def del_item(n):
    if n == 1:
        dt = listbox1.curselection()
        if dt:
            listbox1.delete(dt)
            msg.showinfo("Удалено", "Элемент удалён")
        else:
            msg.showwarning("Ошибка", "Ничего не выбрано")
    else:
        dt = listbox2.curselection()
        if dt:
            listbox2.delete(dt)
            msg.showinfo("Удалено", "Элемент удалён")
        else:
            msg.showwarning("Ошибка", "Ничего не выбрано")

def list_comparison():
    A = list(listbox1.get(0, tk.END))
    B = list(listbox2.get(0, tk.END))
    set1 = set(A)
    set2 = set(B)

    un_elements = set1.intersection(set2)
    only_in_1 = set1 - set2
    only_in_2 = set2 - set1

    message = "Результаты сравнения:\n\n"
    message += f"1. Одинаковые элементы ({len(un_elements)}):\n"

    if un_elements:
        message += ", ".join(sorted(un_elements)) + "\n"
    else:
        message += "Нет одинаковых элементов\n"
    message += f"\n2. Элементы только в Списке 1 ({len(only_in_1)}):\n"

    if only_in_1:
        message += ", ".join(sorted(only_in_1)) + "\n"
    else:
        message += "Нет уникальных элементов\n"
    message += f"\n3. Элементы только в Списке 2 ({len(only_in_2)}):\n"

    if only_in_2:
        message += ", ".join(sorted(only_in_2))
    else:
        message += "Нет уникальных элементов"
    
    msg.showinfo("Сравнение списков", message)

name1 = tk.Label(window, text="Список 1", font=("System", 10, "bold"))
name1.grid(row=0, column=0, pady=10)

name2 = tk.Label(window, text="Список 2", font=("System", 10, "bold"))
name2.grid(row=0, column=1)

listbox1 = tk.Listbox(window, selectmode=tk.SINGLE, height=15, width=30)
listbox1.grid(row=1, column=0, padx=20)

listbox2 = tk.Listbox(window, selectmode=tk.SINGLE, height=15, width=30)
listbox2.grid(row=1, column=1, padx=20)

enter1 = tk.Entry(window, fg='grey')
enter1.insert(0, "Введите слово")
enter1.bind('<FocusIn>', lambda x: on_entry_click(x, enter1, "Введите слово"))
enter1.bind('<FocusOut>', lambda x: on_focus_out(x, enter1, "Введите слово"))
enter1.bind('<Return>', lambda x: on_enter_key(x, 1))
enter1.grid(row=2, column=0)

enter2 = tk.Entry(window, fg='grey')
enter2.insert(0, "Введите слово")
enter2.bind('<FocusIn>', lambda x: on_entry_click(x, enter2, "Введите слово"))
enter2.bind('<FocusOut>', lambda x: on_focus_out(x, enter2, "Введите слово"))
enter2.bind('<Return>', lambda x: on_enter_key(x, 2))
enter2.grid(row=2, column=1)

button1 = tk.Button(window, text="Добавить в список 1", command=lambda:add(1))
button1.grid(row=3, column=0)

button2 = tk.Button(window, text="Добавить в список 2", command=lambda:add(2))
button2.grid(row=3, column=1)

button_del1 = tk.Button(window, text="🗑", bg="red", width=5, command=lambda:del_item(1))
button_del1.grid(row=3, column=0, sticky="e")

button_del2 = tk.Button(window, text="🗑", bg="red", width=5, command=lambda:del_item(2))
button_del2.grid(row=3, column=1, sticky="e")

comparison_button = tk.Button(window, text="Сравнить списки", command=list_comparison)
comparison_button.grid(row=4, column=0, columnspan=2, pady=20)

window.mainloop()
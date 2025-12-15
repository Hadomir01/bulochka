import tkinter as tk
from tkinter import messagebox

window = tk.Tk()
window.title("Телефонная книжка")
window.geometry("350x300")

listbox = tk.Listbox(window, selectmode=tk.SINGLE)
listbox.pack(padx=20, pady=10, fill=tk.BOTH, expand=True)

def on_entry_click(event, entry, placeholder):
    if entry.get() == placeholder:
        entry.delete(0, "end") 
        entry.config(fg='black')  

def on_focus_out(event, entry, placeholder):
    if entry.get() == '':
        entry.insert(0, placeholder)  
        entry.config(fg='grey')  

def add_item():
    name = enter_name.get()
    phone = enter_phone.get()
    if name and phone and name != "Введите имя" and phone != "Введите телефон":
        listbox.insert(tk.END, f"{name} {phone}")
        enter_name.delete(0, tk.END)
        enter_name.insert(0, "Введите имя")
        enter_name.config(fg='grey')
        enter_phone.delete(0, tk.END)
        enter_phone.insert(0, "Введите телефон")
        enter_phone.config(fg='grey')
        messagebox.showinfo("Успешно", "Контакт добавлен", parent=window)
    else:
        messagebox.showwarning("Ошибка", "Заполните все поля", parent=window)

def del_item():
    dt = listbox.curselection()
    if dt:
        listbox.delete(dt)
        messagebox.showinfo("Удалено", "Элемент удалён", parent=window)
    else:
        messagebox.showwarning("Ошибка", "Ничего не выбрано", parent=window)

def del_all():
    if listbox.size() > 0:
        result = messagebox.askyesno("Подтверждение", "Удалить все контакты?", parent=window)
        if result:
            listbox.delete(0, tk.END)
            messagebox.showinfo("Удалено", "Все контакты удалены", parent=window)
    else:
        messagebox.showinfo("Информация", "Список контактов пуст", parent=window)

enter_name = tk.Entry(window, fg='grey', width=30)
enter_name.insert(0, "Введите имя")
enter_name.bind('<FocusIn>', lambda x: on_entry_click(x, enter_name, "Введите имя"))
enter_name.bind('<FocusOut>', lambda x: on_focus_out(x, enter_name, "Введите имя"))
enter_name.pack()

enter_phone = tk.Entry(window, fg='grey', width=30)
enter_phone.insert(0, "Введите телефон")
enter_phone.bind('<FocusIn>', lambda x: on_entry_click(x, enter_phone, "Введите телефон"))
enter_phone.bind('<FocusOut>', lambda x: on_focus_out(x, enter_phone, "Введите телефон"))
enter_phone.pack()

add_button = tk.Button(window, text="Добавить", command=add_item)
add_button.pack()

del_button = tk.Button(window, text="Удалить", command=del_item)
del_button.pack()

clear_button = tk.Button(window, text="Удалить все", command=del_all)
clear_button.pack()

window.mainloop()
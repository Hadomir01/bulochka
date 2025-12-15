import tkinter as tk
from tkinter import messagebox

root = tk.Tk()
root.title("Список покупок")
root.geometry("400x400")

# Listbox
listbox = tk.Listbox(root, selectmode=tk.SINGLE)
listbox.pack(padx=20, pady=10, fill=tk.BOTH, expand=True)

# Поле ввода
entry = tk.Entry(root, width=40)
entry.pack(pady=5)

def add_item():
    item = entry.get().strip()
    items = listbox.get(0, tk.END)
    if item:
        if item in items:
            messagebox.showwarning("Ошибка", f"{item} уже есть в списке!")
            entry.delete(0, tk.END)
            entry.focus_set()
            return
        listbox.insert(tk.END, item)
        entry.delete(0, tk.END)
    else:
        messagebox.showwarning("Ошибка", "Поле ввода пустое")

def delete_item():
    sel = listbox.curselection()
    if sel:
        listbox.delete(sel)
        messagebox.showinfo("Удалено", "Элемент удалён")
    else:
        messagebox.showwarning("Ошибка", "Ничего не выбрано")


def edit_item():
    def save():
        new_text = edit_entry.get().strip()
        if not new_text:
            messagebox.showwarning("Ошибка", "Поле не может быть пустым")
            return
        
        items = list(listbox.get(0, tk.END))
        if new_text in items and new_text != current:
            messagebox.showwarning("Ошибка", f"{new_text} уже есть в списке!")
            edit_entry.select_range(0, tk.END)
            edit_entry.focus_set()
            return
        
        if new_text:
            listbox.delete(index)
            listbox.insert(index, new_text)
        edit_win.destroy()

    selected = listbox.curselection()
    if not selected:
        messagebox.showwarning("Ошибка", "Выберите элемент")
        return

    index = selected[0]
    current = listbox.get(index)

    edit_win = tk.Toplevel(root)
    edit_win.title("Редактировать")
    edit_win.geometry("250x100")
    edit_win.grab_set()

    edit_entry = tk.Entry(edit_win, width=30)
    edit_entry.insert(0, current)
    edit_entry.pack(pady=10)
    edit_entry.focus_set()
    edit_entry.bind('<Return>', lambda x: save())

    edit_button = tk.Button(edit_win, text="Сохранить", command=save)
    edit_button.pack()
    

# === КНОПКИ ===
tk.Button(root, text="Добавить", command=add_item).pack(pady=2)
tk.Button(root, text="Удалить", command=delete_item).pack(pady=2)
tk.Button(root, text="Редактировать", command=edit_item).pack(pady=2)

entry.bind('<Return>', lambda x: add_item())

# Добавим немного данных
lst = ["Хлеб", "Молоко", "Яйца"]
for item in lst:
    listbox.insert(tk.END, item)

root.mainloop()
import tkinter as tk
from tkinter import ttk

window = tk.Tk()
window.title("Конвертер валют")
window.geometry("400x220")
window.resizable(False, False)
window.configure(bg="#F0F8FF")

valutes = ["RUB ₽", "USD $", "EUR €", "GBP £", "JPY ¥"]

exchange_rate = {
    "RUB ₽": 1.0,
    "USD $": 77.95,
    "EUR €": 90.35,
    "GBP £": 103.2,
    "JPY ¥": 0.5
}

def converter():
    try:
        amount = float(enter.get())
        from_currency = box1.get()
        to_currency = box2.get()
        
        if from_currency not in valutes or to_currency not in valutes:
            result_label.configure(text="Ошибка: выберите валюты!", fg="red")
            return
        
        amount_in_rub = amount * exchange_rate[from_currency]
        converted_amount = amount_in_rub / exchange_rate[to_currency]

        
        result_text = f"{amount:.2f} {from_currency} = {converted_amount:.2f} {to_currency}"
        result_label.configure(text=result_text, fg="green")

        if converted_amount < 0:
            result_label.configure(text="Ошибка: введите положительное число!", fg="red")

    except ValueError:
        result_label.configure(text="Ошибка: введите число!", fg="red")

label = tk.Label(window, text="Конвертатор-3000", font=("System", 14, "bold"), bg="#F0F8FF")
label.grid(row=0, column=0, columnspan=2)

enter = tk.Entry(window, font=("System", 12))
enter.grid(row=2, column=0, columnspan=2, padx=100, pady=10)

box1 = ttk.Combobox(window, values=valutes, font=("System", 9))
box1.set("Из...")
box1.grid(row=1, column=0, padx=15)

box2 = ttk.Combobox(window, values=valutes, font=("System", 9))
box2.set("В...")
box2.grid(row=1, column=1)

button = tk.Button(window, text="Конвертировать", font=("System", 14, "bold"), bg="#90EFE8", command=converter)
button.grid(row=3, column=0, columnspan=2, padx=55, pady=10)

result_label = tk.Label(window, font=("System", 12, "bold"), bg="#F0F8FF")
result_label.grid(row=4, column=0, columnspan=2, pady=5)

window.mainloop()
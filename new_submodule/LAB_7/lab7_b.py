# Поиск Академии
with open("file3.txt", encoding="utf-8") as f1:
    with open("file4.txt", encoding="utf-8") as f2:
        text1 = f1.read()
        text2 = f2.read()
if "Academy" in text1:
    print("Слово в file3.txt!")
elif "Academy" in text2:
    print("Слово в file4.txt!")
else:
    print("Слово не обнаружено!")
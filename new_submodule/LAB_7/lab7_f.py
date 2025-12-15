with open("for_f.txt", "r", encoding="utf-8") as f:
    tmp = f.readlines()
    with open("for_f.txt", "w", encoding="utf-8") as f:

        text = input("Введите текст > ")
        tmp.append(text[::-1] + "\n")
        f.writelines(tmp)
with open("for_f.txt", "r", encoding="utf-8") as f:  
    text = f.readlines()

    for i in range(0, len(text)):
        print(text[i][::-1])

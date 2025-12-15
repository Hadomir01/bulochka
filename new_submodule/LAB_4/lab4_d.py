def check_words(text, word):
    buff = ""
    for i in range(0, len(word)):
        for j in range(0, len(text)):
            if text[j] == word[i] and text[j] not in buff:
                buff = buff + text[j]
        text = text[1:]


            

    return True if (buff == word) else False

print(check_words(input("Введите Главное слово: "), input("Введите производное слово: ")))


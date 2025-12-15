text1 = str(input("Печатайте текст > "))
text2 = str(input("Печатайте текст > "))
text3 = str(input("Печатайте текст > "))
glasnie = "аеёиоуыэюяАЕЁИОУЫЭЮЯ"
gl_count_1 = 0
gl_count_2 = 0
gl_count_3 = 0

if text1 == "" or text2 == "" or text3 == "":
    print("Не хайку! Должно быть 3 строки.")
else:
    for i in text1:
        if i in glasnie:
            gl_count_1 += 1
    for j in text2:
        if j in glasnie:
            gl_count_2 += 1
    for k in text3:
        if k in glasnie:
            gl_count_3 += 1
    
    if (gl_count_1 + gl_count_2 + gl_count_3) == 17 and (gl_count_1 == 5 and gl_count_2 == 7 and gl_count_3 == 5):
        print("Хайку!")
    else:
        print("Не хайку!")
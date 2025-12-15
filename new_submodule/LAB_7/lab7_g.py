import random
with open("for_g.txt", encoding="utf-8") as f:
    lst = [x.strip() for x in f]
password = ""
while True:
    word = random.choice(lst).capitalize()
    password = password + word
    c = 0
    for i in password:
        if i.isupper():
            c += 1
    if 8 <= len(password) <= 10 and c == 2:
        print(password, len(password))
        break
    elif len(password) < 8:
        continue
    else:
        password = ""
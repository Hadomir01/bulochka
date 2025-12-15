import random
import time

stn = ['камень', 'к', 'stone', 'st']
ppr = ['бумага', 'б', 'paper', 'p']
scrs = ["ножницы", "scissors", "н", "sc"]

choice_pc = ["камень", "бумага", "ножницы"]

match_score_pl = 0
match_score_pc = 0

print("===== МЕЖГАЛАКТИЧЕСКИЙ ТУРНИР ПО КАМЕНЬ-НОЖНИЦЫ-БУМАГА =====")
time.sleep(3)
print("Правила турнира:\nКамень побеждает ножницы \nНожницы побеждают бумагу\nБумага побеждает камень\nДля победы в матче нужно первым одержать 3 победы. Ничьи не засчитываются!")
time.sleep(5)

while (match_score_pl != 3) or (match_score_pc != 3):
    turn_pl = input("Настал ваш ход: ")
    turn_pc = random.choice(choice_pc)
    if (turn_pl in stn) and (turn_pc in stn): # к/к
        print(f"Компьютер выбрал {turn_pc}")
        print(f"Ничья! Никто не получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in ppr) and (turn_pc in ppr): # б/б
        print(f"Компьютер выбрал {turn_pc}")
        print(f"Ничья! Никто не получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in scrs) and (turn_pc in scrs): #н/н
        print(f"Компьютер выбрал {turn_pc}")
        print(f"Ничья! Никто не получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in stn) and (turn_pc in ppr): # к/б
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pc += 1
        print(f"Компьютер получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in stn) and (turn_pc in scrs): # к/н
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pl += 1
        print(f"Игрок получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in ppr) and (turn_pc in stn): # б/к
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pl += 1
        print(f"Игрок получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in ppr) and (turn_pc in scrs): # б/н
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pc += 1
        print(f"Компьютер получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in scrs) and (turn_pc in stn): # н/к
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pc += 1
        print(f"Компьютер получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    elif (turn_pl in scrs) and (turn_pc in ppr): # н/б
        print(f"Компьютер выбрал {turn_pc}")
        match_score_pl += 1
        print(f"Игрок получает балл! Счёт: Игрок- {match_score_pl} | Компьютер- {match_score_pc}")
    
    if (match_score_pl == 3) or (match_score_pc == 3):
        break


print("=====!!!ВНИМАНИЕ!!!=====")
time.sleep(2)
print("У нас есть победитель!!!")
time.sleep(2)
if match_score_pc == 3:
    print(f"Со счетом {match_score_pl} | {match_score_pc} Победил Компьютер!!!")
elif match_score_pl == 3:
    print(f"Со счетом {match_score_pl} | {match_score_pc} Победил Игрок!!!")

time.sleep(2)
print("Спасибо участникам за игру!!!")
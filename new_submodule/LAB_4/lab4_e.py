import random 

quiz = random.randint(1, 100)

print("Попробуйте угадать число от 1 до 100, которое загадал компьютер!")
ans = int(input("Напишите свое предположение: "))

while quiz != ans:
    if ans < quiz:
        print("Загаданное число больше!")
        ans = int(input("Попробуйте ещё раз: "))
    if ans > quiz:
        print("Загаданное число меньше!")
        ans = int(input("Попробуйте ещё раз: "))
    if ans == quiz:
        print("Поздравляем! Ты угадал число!")


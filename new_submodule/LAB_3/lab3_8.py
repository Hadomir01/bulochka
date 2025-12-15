import random 
import time

safe = random.randint(1, 3)

print("Вы заблудились в заколдованном лесу. Перед вами три тропинки: \n" \
"1. Тропинка, усыпанная серебряными листьями; \n" \
"2. Тропинка, освещенная таинственным сиянием; \n" \
"3. Тропинка, ведущая в темную чащу. \n" \
"Какую тропинку вы выберете? (1, 2 или 3) ")

lst = [0, 1, 2, 3]
choise_track = int(input())

while choise_track not in lst:
    print("Пожалуйста, выберите тропинку из предложенных вариантов! (1, 2 или 3)")
    choise_track = int(input())

if choise_track == 0:
    print("Вы не можете решиться и остаетесь на месте...")
    time.sleep(3)
    print("Ночью на вас нападают волки!")
    time.sleep(1)
    print("Вам чудом удается спастись!")
    time.sleep(5)
elif choise_track == 1 or choise_track == 2 or choise_track == 3:
    print("Вы осторожно ступаете на выбранную тропинку...")
    time.sleep(3)
    print("Воздух наполняется магической энергией...")
    time.sleep(3)
    print("Вокруг раздаются таинственные звуки леса...")
    time.sleep(7)

if choise_track == 1:
    print("Вы идете по тропинке с серебряными листьями...")
    time.sleep(3)
    if safe == choise_track:
        print("Внезапно перед вами появляется лесной дух!")
        time.sleep(3)
        print("Он дарит вам волшебный амулет удачи!")
        time.sleep(1)
        print("Вы находите путь домой с ценным подарком!")
        time.sleep(5)
    else:
        print("Листья превращаются в ядовитых змей!")
        time.sleep(3)
        print("Вам едва удается спастись бегством!")
        time.sleep(5)

if choise_track == 2:
    print("Вы следуете за таинственным сиянием...")
    time.sleep(3)
    if safe == choise_track:
        print("Сияние приводит вас к древнему храму!")
        time.sleep(3)
        print("Мудрый старец учит вас секретам магии!")
        time.sleep(1)
        print("Вы обретаете новые знания!")
        time.sleep(5)
    else:
        print("Сияние оказывается ловушкой!")
        time.sleep(3)
        print("Вы попадаете в магическую паутину!")
        time.sleep(1)
        print("Час вы выбираетесь на свободу!")
        time.sleep(5)

if choise_track == 3:
    print("Вы входите в темную чащу...")
    time.sleep(3)
    if safe == choise_track:
        print("В чаще вы находите спящего единорога!")
        time.sleep(3)
        print("Он просыпается и становится вашим другом!")
        time.sleep(1)
        print("Единорог провожает вас до края леса!")
        time.sleep(5)
    else:
        print("Из темноты на вас нападают гоблины!")
        time.sleep(3)
        print("Вам приходится отдать им все свои вещи!")
        time.sleep(1)
        print("Вы выбираетесь из леса ни с чем!")
        time.sleep(5)

print("Безопасной была тропинка номер", safe)
time.sleep(2)
print("Спасибо за игру!)")












while True:
    try:
        Андрей = int(input("Введите рост Андрея > "))
    except ValueError:
        print("Ошибка! Введите рост Андрея корректно!")
    else:
        break

heights = input("Введите рост одноклассников Андрея > ").split()
for i in range(0, len(heights)-1):
    if int(heights[i]) < Андрей:
        heights.insert(i, str(Андрей))
        print(i+1)
        print(heights)
        break
    elif int(heights[i]) == Андрей:
        heights.insert(i+1, str(Андрей))
        print(i+2)
        print(heights)
        break
    elif Андрей < int(heights[-1]):
        heights.append(str(Андрей))
        print(len(heights))
        print(heights)
        break
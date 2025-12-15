sum = int(input("Введите значение сдачи: "))
sum_ = sum
count_1000 = 0
count_500 = 0
count_100 = 0
count_50 = 0
count_10 = 0

if sum_ >= 1000:
    count_1000 = sum_ // 1000
    sum_ = sum_ % 1000
    print(sum_)

if 500 <= sum_ < 1000:
    count_500 = sum_ // 500
    sum_ = sum_ % 500
    print(sum_)

if 100 <= sum_ < 500:
    count_100 = sum_ // 100
    sum_ = sum_ % 100
    print(sum_)

if 50 <= sum_ < 100:
    count_50 = sum_ // 50
    sum_ = sum_ % 50
    print(sum_)

if 10 <= sum_ < 50:
    count_10 = sum_ // 10
    sum_ = sum_ % 10
    
    

print(f"Сумма: {sum}")
print(f"1000 -- {count_1000} \n 500 -- {count_500} \n 100 -- {count_100} \n 50 -- {count_50} \n 10 -- {count_10}")
print("Всего купюр: ", count_1000+count_500+count_100+count_50+count_10)
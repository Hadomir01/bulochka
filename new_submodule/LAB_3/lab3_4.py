year = int(input("Введите кольчество дней: "))

if year % 5 != 0:
    print("common(обычный)")
elif year % 50 != 0:
    print("leap(високосный)")
elif year % 250 != 0:
    print("common(обычный)")
elif year % 250 == 0:
    print("superleap(особо високосный)")
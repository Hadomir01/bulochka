a1, a2, a3 = map(int, input("Введите длины сторон треугольника через пробел: ").split())

if a1 == a2 == a3:
    print("equilateral(равносторонний)")
elif a1 == a2 or a2 == a3 or a3 == a1:
    print("isosceles(равноберенный)")
elif a1 != a2 != a3:
    print("scalene(разносторонний))")
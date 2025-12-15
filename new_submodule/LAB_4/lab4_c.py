height = int(input("Высота елочки: "))

for i in range(height):
    print(" " * (height - i - 1), end = ' ')
    print("#" * (2*i + 1))

print(" " * (height) + "#")



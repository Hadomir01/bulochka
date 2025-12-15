lst = input("Введите текст > ").split()
res = []
for i in lst:
    if not res or res[-1] != i:
        res.append(i)

result = " ".join(res)

print(result)
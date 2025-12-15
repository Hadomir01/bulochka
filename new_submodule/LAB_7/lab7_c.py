# Без единой Е
with open("file4.txt", encoding="utf-8") as f:
    lst = [x.split() for x in f]
l = 0
c = 0
for i in range(0, len(lst)-1):
    l = l + len(lst[i])
for x in range(0, len(lst)-1):
    for y in lst[x]:
        if "e" in y:
            c += 1
res = c/l*100
print(f"{res:.2f}%")

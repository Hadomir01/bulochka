# Олимпиада
lst = []
with open("file2.txt", encoding="utf-8") as file:
    for i in file:
        lst.append(i.split())
        lst = sorted(lst, key=lambda x: x[-1])[::-1]

print(f"{lst[1][0] + " " + lst[1][1]} набрал(-а) {lst[1][-1]} баллов на олимпиаде")
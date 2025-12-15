
s = input()
seen = ""
result = ""
for char in s:
    if char not in seen:
        result = result + char
        seen = seen + char
print(result)
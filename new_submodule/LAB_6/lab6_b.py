tovar = input("Введите количество проданного товара по дням(в порядке следования дней) > ").split()
res = []
sells = []
for i in range(0, len(tovar)-1):
    try:
        if tovar[i] < tovar[i+1]:
            res.append(i+2)
            sells.append(tovar[i+1])
    except IndexError:
        break

ans = ""
for i in res:
    ans = ans + str(i) + " "
ans_sell = ""
for i in sells:
    ans_sell = ans_sell + str(i) + " "
print(f"Дни, когда продажи выросли: {ans}")
print(f"Объем товара в эти дни: {ans_sell}")
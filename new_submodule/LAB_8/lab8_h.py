def sales_summary(price_list: dict, sales: list) -> dict:
    res = {
        "total_revenue": "", # Общая выручка
        "items_sold": "", # Продано товаров (каждого)
        "top_item": "" # Самый продаваемый товар
    }  

    revenue = 0
    for i in sales:
        if i[0] in price_list and i[1] != 0:
            revenue = revenue + (price_list[i[0]] * i[1])
    res["total_revenue"] = revenue

    saled = {

    }
    for x in sales:
        if x[0] in price_list and x[1] != 0:
            if x[0] in saled:
                saled[x[0]] += x[1]
            else:
                saled[x[0]] = x[1]
    res["items_sold"] = saled

    try:
        max_saled = max(saled, key=saled.get)
        res["top_item"] = max_saled
    except ValueError:
        res["top_item"] = None

    return res


price_list = {"Хлеб": 50, "Молоко": 80, "Сыр": 200}
sales = [("Хлеб", 0), ("Молоко", 2), ("Хлеб", 1), ("Кофе", 5)]
print(sales_summary(price_list, sales))
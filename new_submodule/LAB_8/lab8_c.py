def reduce_measure(amount, unit):
    # 1 cup = 16 tablespoons
    # 1 tablespoon = 3 teaspoons
    if unit == "cup" or unit == "cups":
        amount = amount*16*3
    elif unit == "tablespoon" or unit == "tablespoon":
        amount = amount*3
    
    cups = 0
    tablespoons = 0
    teaspoons = 0

    if amount > 16*3:
        cups = amount // (16*3)
        amount = amount % (16*3)

    if 3 < amount < 16*3:
        tablespoons = amount // 3
        amount = amount % 3

    teaspoons = amount
    
    if cups > 1:
        cup_name = "cups"
    elif cups == 1:
        cup_name = "cup"
    else:
        cup_name = ""
    if tablespoons > 1:
        tablespoon_name = "tablespoons"
    elif tablespoons == 1:
        tablespoon_name = "tablespoon"
    else:
        tablespoon_name = ""
    if teaspoons > 1:
        teaspoon_name = "teaspoons"
    elif teaspoons == 1:
        teaspoon_name = "teaspoon"
    else:
        teaspoon_name = ""
        
    return f"You need: {cups if cups != 0 else ""} {cup_name} {tablespoons if tablespoons != 0 else ""} {tablespoon_name} {teaspoons if teaspoons != 0 else ""} {teaspoon_name}"

print(reduce_measure(59, "teaspoons"))
print(reduce_measure(60, "teaspoons"))
print(reduce_measure(61, "teaspoons"))
print(reduce_measure(25, "teaspoons"))
print(reduce_measure(7, "tablespoons"))
print(reduce_measure(0, "teaspoons"))


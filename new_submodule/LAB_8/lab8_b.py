def is_magic_date(day, month, year):
    if str(day*month) == str(year)[-2:]:
        return True
    else:
        return False

lst = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
lst_ = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
for year in range(1900, 2001):
    for month in range(1, 13):
        for day in range(lst[month-1]):
            if is_magic_date(day, month, year) == True:
                print(f"{day}.{month}.{year}")
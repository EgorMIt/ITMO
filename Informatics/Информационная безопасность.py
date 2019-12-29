# 1 Упражнение
# Вставляешь из задания p, q, c, (k - это количество знаков "... коды стали длиной k знаков" из 1 упражнения)
p = 53
q = 239
c = 2593
k = 5
# Пишешь каждой переменной массива свой трехзначный код, через запятую(3 цифры - 1 буква слова)
# Хотя бы это сделай)))
a = [207,238,236,239,232,228,243]


# 2 Упражнение
# Самостоятельно разбиваешь свое большое число по количеству знаков и убираешь лишние нули в начале числа
# Пример: 312223953446223521130234         По 4 знака - нули слева! : 3122 2395 3446 2235 2113 234
# Через запятую загоняешь в массив
name = [1486,207,718,155,843,1308,2572]

# Числа из зыкрытого ключа
# 1 число:
g = 1927
# 2 число:
l = 2629





# Эту часть кода лучше не трогай)))
b = ""
op = ""
p1 = p - 1
q1 = q - 1
N = p*q
for gg in range(N+1):
    if (c*gg % (p1*q1)) == 1:
        d = gg
for i in a:
    if k == 5:
        if int(i)**c% N // 1000 == 0:
            h = ("00" + str(int(i)**int(c)%N))
            b += h
        elif int(i)**c %N // 10000 == 0:
            h = ("0" + str(int(i)**int(c)%N))
            b += h
        else:
            b += str(int(i)**int(c)%N)
    else:
        if int(i)**c% N // 100 == 0:
            h = ("00" + str(int(i)**int(c)%N))
            b += h
        elif int(i)**c %N // 1000 == 0:
            h = ("0" + str(int(i)**int(c)%N))
            b += h
        else:
            b += str(int(i)**int(c)%N)
print("1 Уппажнение")
print("d =",d)
print("N =",N)
print(b)
print()
print("2 Упражнение")
print("Просто вставь это слово:")
for i in name:
    huy = i**g%l
    if huy == 192:
        op += "А"
    elif huy == 193:
        op += "Б"
    elif huy == 194:
        op += "В"
    elif huy == 195:
        op += "Г"
    elif huy == 196:
        op += "Д"
    elif huy == 197:
        op += "Е"
    elif huy == 198:
        op += "Ж"
    elif huy == 199:
        op += "З"
    elif huy == 200:
        op += "И"
    elif huy == 201:
        op += "Й"
    elif huy == 202:
        op += "К"
    elif huy == 203:
        op += "Л"
    elif huy == 204:
        op += "М"
    elif huy == 205:
        op += "Н"
    elif huy == 206:
        op += "О"
    elif huy == 207:
        op += "П"
    elif huy == 208:
        op += "Р"
    elif huy == 209:
        op += "С"
    elif huy == 210:
        op += "Т"
    elif huy == 211:
        op += "У"
    elif huy == 212:
        op += "Ф"
    elif huy == 213:
        op += "Х"
    elif huy == 214:
        op += "Ц"
    elif huy == 215:
        op += "Ч"
    elif huy == 216:
        op += "Ш"
    elif huy == 217:
        op += "Щ"
    elif huy == 218:
        op += "Ь"
    elif huy == 219:
        op += "Ы"
    elif huy == 220:
        op += "Ъ"
    elif huy == 221:
        op += "Э"
    elif huy == 222:
        op += "Ю"
    elif huy == 223:
        op += "Я"
    elif huy == 224:
        op += "а"
    elif huy == 225:
        op += "б"
    elif huy == 226:
        op += "в"
    elif huy == 227:
        op += "г"
    elif huy == 228:
        op += "д"
    elif huy == 229:
        op += "е"
    elif huy == 230:
        op += "ж"
    elif huy == 231:
        op += "з"
    elif huy == 232:
        op += "и"
    elif huy == 233:
        op += "й"
    elif huy == 234:
        op += "к"
    elif huy == 235:
        op += "л"
    elif huy == 236:
        op += "м"
    elif huy == 237:
        op += "н"
    elif huy == 238:
        op += "о"
    elif huy == 239:
        op += "п"
    elif huy == 240:
        op += "р"
    elif huy == 241:
        op += "с"
    elif huy == 242:
        op += "т"
    elif huy == 243:
        op += "у"
    elif huy == 244:
        op += "ф"
    elif huy == 245:
        op += "х"
    elif huy == 246:
        op += "ц"
    elif huy == 247:
        op += "ч"
    elif huy == 248:
        op += "ш"
    elif huy == 249:
        op += "щ"
    elif huy == 250:
        op += "ь"
    elif huy == 251:
        op += "ы"
    elif huy == 252:
        op += "ъ"
    elif huy == 253:
        op += "э"
    elif huy == 254:
        op += "ю"
    elif huy == 255:
        op += "я"
    elif huy == 256:
        op += "Ты п***р"
print(op)

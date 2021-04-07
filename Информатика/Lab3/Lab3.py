def ToInt(x):  # посимвольный/поразрядный прервод из строки в int
    k = 0
    for i in x:
        k = k * 10 + ord(i) - 48  # 0=48, 1=49...
    return k


def ToTenth(a):  # В 10ую
    l = list(str(a))
    s = len(l)
    k = 0
    for i in range(0, s):
        l[i] = ToInt(l[i]) * pow(-10, s - 1 - i)
        k = k + l[i]
    return k


def ToSixtnth(a):  # В 16ричную
    new = 0
    l = a.split('.')
    k = list(l[0])
    string = ''
    while len(k) < 4:
        k.insert(0, 0)
    l[0] = ''.join(map(str, k))
    for i in range(0, len(l)):
        k = list(l[i])
        for j in range(0, len(k)):
            new = new + ToInt(k[j]) * (pow(2, 4 - 1 - j))
        if new == 10:
            string = string + 'A'
        elif new == 11:
            string = string + 'B'
        elif new == 12:
            string = string + 'C'
        elif new == 13:
            string = string + 'D'
        elif new == 14:
            string = string + 'E'
        elif new == 15:
            string = string + 'F'
        else:
            string = string + str(new)
        new = 0
    return string


with open('input.txt') as f:
    result = []
    lines = f.readlines()
    for y in lines:
        lst = y.split()
        first = lst[0]
        second = lst[1]
        number = lst[2:7]
        if first == '-10':
            for i in range(2, len(lst)):
                result.append(ToTenth(lst[i]))
            result = list(map(str, result))
        if first == '2':
            for i in range(2, len(lst)):
                result.append(ToSixtnth(lst[i]))
            result = list(map(str, result))

        print('{} -> {} : {}'.format(first, second,
                                     ' | '.join(['{} -> {}'.format(i, j)
                                                 for i, j in zip(number, result)])))
        result = []

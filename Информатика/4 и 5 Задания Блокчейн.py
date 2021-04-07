#Задание 4
a = 244
c = 592
d = 767

#Задание 5
one = "001b9f193ba9007052df08750c65edf6368ec110c126d3937c8b5906b00ab99d"     # в "..." вставляем hash, который уже дан по заданию
two = 618     # пишим число, которое дано по заданию




# Ничего не тронгай ниже
import hashlib
x = 1
b = 1
print("Задание 4:")
o = str(hashlib.sha256(str(a).encode()).hexdigest())
print(o)
h = o + str(hashlib.sha256(str(c).encode()).hexdigest())
o = str(hashlib.sha256(str(h).encode()).hexdigest())
print(o)
j = o + str(hashlib.sha256(str(d).encode()).hexdigest())
o = str(hashlib.sha256(str(j).encode()).hexdigest())
print(o)
two1 = hashlib.sha256(str(two).encode()).hexdigest()
string = one + two1
while x != 1001:
    s = hashlib.sha256(str(b).encode()).hexdigest()
    gg = string
    gg +=s
    gg = hashlib.sha256(str(gg).encode()).hexdigest()
    if gg[:2] == "00":
        i = gg
    x +=1
    b +=1
print()
print("Задание 5:")
print("В ответ пишешь: ", i)

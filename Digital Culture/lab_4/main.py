def dist(a, b):
    if len(a) > len(b):
        a, b = b, a
    n = len(a)
    m = len(b)

    row = range(n + 1)
    for i in range(1, m + 1):
        prev = row
        row = [i] + [0] * n
        for j in range(1, n + 1):
            add = prev[j] + 1
            delete = row[j - 1] + 1
            change = prev[j - 1]
            if a[j - 1] != b[i - 1]:
                change += 1
            row[j] = min(add, delete, change)
    return row[n]


# Text reading
text = open(' text.txt', "r", encoding="utf-8").read().lower()
punctuation = "!?,;.:—«()»"
text = "".join([ch for ch in text if ch not in punctuation])
matr = text.split()

# Dictionary reading
dictionary = open('dict1.txt', "r", encoding="utf-8").read().lower().split()
dictionary = list([dictionary[i] for i in range(0, len(dictionary), 2)])

d = {}

for i in matr:
    if d.get(i) != None:
        d.update({i: d.get(i) + 1})
    else:
        d.update({i: 1})

k = 0

mas = []

for i in d.keys():
    if i in dictionary:
        k += 1
    else:
        mas.append(i)

for i in mas:
    mn = len(i)
    sl = ""
    for j in dictionary:
        if dist(i, j) < mn:
            mn = dist(i, j)
            sl = j
    if mn > 2:
        for k in range(len(i)):
            if i[:k] in dictionary and i[k:] in dictionary:
                print(i + ' ' + i[:k] + ' ' + i[k:] + ' ' + str(1))
    else:
        print(i + ' ' + sl + ' ' + str(mn))

print("count of wordforms in dictionary from text - " + str(k))
print("count of wordforms - " + str(len(matr)))
print("count of unique wordforms - " + str(len(d)))
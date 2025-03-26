cards = [0] * 100
q = int(input())
for _ in range(q):
    query = input()
    if query[0] == "1":
        x = int(query.split()[-1])
        cards.append(x)
    else:
        print(cards.pop())

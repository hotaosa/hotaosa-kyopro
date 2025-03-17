x = float(input())
for i, f in enumerate([100, 38.0, 37.5, 0]):
    if x >= f:
        print(i)
        exit()

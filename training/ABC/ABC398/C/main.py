from collections import Counter

n = int(input())
a = list(map(int, input().split()))
b = sorted([(a[i], i) for i in range(n)], reverse=True)
c = Counter(a)

for ai, i in b:
    if c[ai] == 1:
        print(i + 1)
        exit()
print("-1")

from collections import Counter

c = Counter(map(int, input().split())).most_common()
print("Yes" if len(c) >= 2 and c[0][1] >= 3 and c[1][1] >= 2 else "No")

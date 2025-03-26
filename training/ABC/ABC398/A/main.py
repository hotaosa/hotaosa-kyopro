n = int(input())
s = "-" * ((n - 1) // 2)
t = "=" * (2 - (n & 1))
print("".join([s, t, s]))

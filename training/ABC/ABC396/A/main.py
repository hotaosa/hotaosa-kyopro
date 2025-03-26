n = int(input())
a = list(map(int, input().split()))
for i in range(n - 2):
    if len(set(a[i : i + 3])) == 1:
        print("Yes")
        exit()
print("No")

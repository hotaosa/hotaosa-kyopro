import re

input()
print("Yes" if re.search(r"(\d+) \1 \1", input()) else "No")

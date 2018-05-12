import sys


pattern, text = sys.stdin.read().split()
ans = [i + 1 for i in range(len(text) + 1) if text[i:].startswith(pattern)]
print(len(ans))
print(*ans)

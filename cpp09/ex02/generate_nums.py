nums = []
x = 7919
for i in range(3000):
    x = (x * 1103515245 + 12345) & 0x7fffffff
    nums.append(1 + (x % 100000))

numbers_line = " ".join(map(str, nums))

with open("numbers.txt", "w") as f:
    f.write(numbers_line + "\n")
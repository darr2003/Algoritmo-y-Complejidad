import random

size = 1000000
nums = list(range(1, size // 2 + 1))
nums2 = list(range(size // 2 + 1, size + 1))
random.shuffle(nums2)
nums.extend(nums2)

file_name = "dataset.txt"
with open(file_name, "w") as file:
    file.write(" ".join(map(str, nums)))

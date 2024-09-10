size = 1000000
nums = list(range(1, size + 1))


file_name = "dataset.txt"
with open(file_name, "w") as file:
    file.write(" ".join(map(str, nums)))

size = 1000000
nums = list(range(1, size+1))

nombre = "datasetDesordenado.txt"
file = open(nombre, "w")
for num in nums:
    file.write(str(num)+ " ")
file.close()
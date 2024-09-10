import random

# Genera matriz con valores entre min_val y max_val
def generate_matrix(rows, cols, min_val=1, max_val=100):
    return [[random.randint(min_val, max_val)
            for _ in range(cols)] for _ in range(rows)]

# Escribe dos matrices en un archivo
def write_matrices_to_file(file_name, matrixA, matrixB):
    with open(file_name, 'w') as file:
        file.write(f"{len(matrixA)} {len(matrixA[0])}\n")
        for row in matrixA:
            file.write(' '.join(map(str, row)) + '\n')

        file.write('\n')
        file.write(f"{len(matrixB)} {len(matrixB[0])}\n")
        for row in matrixB:
            file.write(' '.join(map(str, row)) + '\n')

x, y, z = 50, 100, 50
matrixA = generate_matrix(x, y, min_val=1, max_val=20)
matrixB = generate_matrix(y, z, min_val=1, max_val=20)

write_matrices_to_file('Input.txt', matrixA, matrixB)

print("Matrices generated and written to 'Input.txt'")

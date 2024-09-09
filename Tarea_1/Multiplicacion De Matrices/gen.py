import random

def generate_matrix(rows, cols):
    return [[random.randint(1, 10) for _ in range(cols)] for _ in range(rows)]

def write_matrices_to_file(file_name, matrixA, matrixB):
    with open(file_name, 'w') as file:
        file.write(f"{len(matrixA)} {len(matrixA[0])}\n")
        for row in matrixA:
            file.write(' '.join(map(str, row)) + '\n')

        file.write('\n')  
        file.write(f"{len(matrixB)} {len(matrixB[0])}\n")
        for row in matrixB:
            file.write(' '.join(map(str, row)) + '\n')

rowsA, colsA = 5, 5
rowsB, colsB = 5, 4

matrixA = generate_matrix(rowsA, colsA)
matrixB = generate_matrix(rowsB, colsB)

write_matrices_to_file('Input.txt', matrixA, matrixB)

print(f"Matrices generated and written to 'Input.txt'")

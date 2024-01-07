import numpy as np

def generate_matrix(dim1, dim2):
    matrix = np.empty((dim1, dim2), dtype=object)
    
    for i in range(dim1):
        for j in range(dim2):
            matrix[i, j] = ('Empty', 0)
    
    return matrix

# Example usage:
dim1 = 3
dim2 = 4
result_matrix = generate_matrix(dim1, dim2)
print(result_matrix)
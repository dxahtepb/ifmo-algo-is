def check_graph(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j] != matrix[j][i] or (i == j and matrix[i][j] == 1):
                return 'NO'
    return 'YES'
 
 
if __name__ == '__main__':
    with open('input.txt', 'r') as file_in, \
         open('output.txt', 'w') as file_out:
 
        nodes = int(file_in.readline().rstrip())
 
        matrix = []
 
        for _ in range(nodes):
            line = list(map(int, file_in.readline().rstrip().split()))
            matrix.append(line)
 
        file_out.write(check_graph(matrix) + '\n')

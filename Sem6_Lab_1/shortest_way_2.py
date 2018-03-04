from collections import deque
 
 
def count_distances(matrix, n, m, start):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    queue = deque([start])
 
    while queue:
        x, y = queue.popleft()
 
        for dx, dy in directions:
            new_x, new_y = x + dx, y + dy
            if new_x < 0 or new_x >= n or new_y < 0 or new_y >= m:
                continue
            if matrix[new_x][new_y] < 0:
                continue
 
            if matrix[new_x][new_y] > matrix[x][y] + 1:
                matrix[new_x][new_y] = matrix[x][y] + 1
                queue.append((new_x, new_y))
 
    return matrix
 
 
def find_path(matrix, n, m, start, finish):
    directions = [(0, 1, 'L'), (1, 0, 'U'), (0, -1, 'R'), (-1, 0, 'D')]
    path = []
    current_cell = finish
 
    if matrix[finish[0]][finish[1]] == 10**6:
        return '-1'
 
    while current_cell != start:
        x, y = current_cell
 
        for dx, dy, symbol in directions:
            new_x, new_y = x + dx, y + dy
            if new_x < 0 or new_x >= n or new_y < 0 or new_y >= m:
                continue
            if matrix[new_x][new_y] < 0:
                continue
 
            if matrix[new_x][new_y] == matrix[x][y] - 1:
                path.append(symbol)
                current_cell = (new_x, new_y)
                break
 
    return path
 
 
if __name__ == '__main__':
    with open('input.txt', 'r') as file_in, \
         open('output.txt', 'w') as file_out:
 
        n, m = map(int, file_in.readline().rstrip().split())
        start, finish = 0, 0
 
        matrix = [[10**6] * m for _ in range(n)]
 
        for i in range(n):
            row = list(iter(file_in.readline().rstrip()))
 
            for j, cell in enumerate(row):
                if cell == 'S':
                    start = (i, j)
                    matrix[i][j] = 0
                elif cell == 'T':
                    finish = (i, j)
                elif cell == '#':
                    matrix[i][j] = -100
 
        matrix = count_distances(matrix, n, m, start)
        path = find_path(matrix, n, m, start, finish)
 
        if path != '-1':
            file_out.write(str(len(path)) + '\n')
            file_out.write(''.join(reversed(path)))
        else:
            file_out.write('-1')

if __name__ == '__main__':
    with open('input.txt', 'r') as file_in, \
         open('output.txt', 'w') as file_out:
 
        nodes, edges = map(int, file_in.readline().rstrip().split())
 
        matrix = []
        for _ in range(nodes):
            matrix.append([0] * nodes)
 
        for _ in range(edges):
            vertex_from, vertex_to = map(lambda x: int(x)-1, file_in.readline().rstrip().split())
            matrix[vertex_from][vertex_to] = 1

        file_out.write('\n'.join([' '.join(map(str, line)) for line in matrix]))

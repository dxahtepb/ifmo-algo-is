from collections import deque
 
 
def count_distances(graph, start):
    distances = [10 ** 6] * len(graph)
 
    queue = deque([start])
    distances[start] = 0
 
    while queue:
        node = queue.popleft()
        for child in graph[node]:
            if distances[child] > distances[node] + 1:
                distances[child] = distances[node] + 1
                queue.append(child)
 
    return distances
 
 
if __name__ == '__main__':
    with open('pathbge1.in', 'r') as file_in, \
         open('pathbge1.out', 'w') as file_out:
 
        n_nodes, n_edges = map(int, file_in.readline().rstrip().split())
 
        graph = [[] for _ in range(n_nodes)]
 
        for _ in range(n_edges):
            vertex_from, vertex_to = map(lambda x: int(x)-1,
                                         file_in.readline().rstrip().split())
            graph[vertex_from].append(vertex_to)
            graph[vertex_to].append(vertex_from)
 
        distances = count_distances(graph, 0)
 
        file_out.write(' '.join(map(str, distances)))

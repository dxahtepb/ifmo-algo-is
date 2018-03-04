def find_components(graph):
    visited = [0] * n_nodes
    n_components = 0
 
    for node in range(len(graph)):
        if visited[node] == 0:
            n_components += 1
            visited[node] = n_components
            dfs(graph, node, visited, n_components)
 
    return n_components, visited
 
 
def dfs(graph, start, visited, n_components):
    stack = [start]
 
    while stack:
        children = graph[stack.pop()]
        for child in children:
            if visited[child] == 0:
                visited[child] = n_components
                stack.append(child)
 
 
if __name__ == '__main__':
    with open('components.in', 'r') as file_in, \
         open('components.out', 'w') as file_out:
 
        n_nodes, n_edges = map(int, file_in.readline().rstrip().split())
 
        graph = [[] for _ in range(n_nodes)]
 
        for _ in range(n_edges):
            vertex_from, vertex_to = map(lambda x: int(x)-1,
                                         file_in.readline().rstrip().split())
            graph[vertex_from].append(vertex_to)
            graph[vertex_to].append(vertex_from)
 
        n_components, labels = find_components(graph)
 
        file_out.write(str(n_components) + '\n')
        file_out.write(' '.join(map(str, labels)))

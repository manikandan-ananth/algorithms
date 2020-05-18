#!/home/linuxbrew/.linuxbrew/bin/python3
import sys
from copy import deepcopy
from random import choice

def loadGraph(file_name, graph):
    lines = open(file_name).readlines()

    for line in lines:
        vertices = line.split()
        graph[vertices[0]] = vertices[1:]

def perform_random_contraction(graph):
    
    while len(graph) > 2:
        v1 = choice(list(graph.keys()))
        v2 = choice(graph[v1])

        # Merge v2 Neighbors into v1
        graph[v1].extend(graph[v2])

        # Replace occurences of v2 with v1
        for v in graph[v2]:
            graph[v].remove(v2)
            graph[v].append(v1)
        
        while v1 in graph[v1]:
            graph[v1].remove(v1)
        
        del graph[v2]

    l = [len(graph[key]) for key in graph.keys()]   
    assert (l[0] == l[1])
    return l[0]

if __name__ == "__main__":

    graph = {}
    loadGraph(sys.argv[1], graph)

    attempts = 1000 #keeping t low to save time
    min_cut = perform_random_contraction(deepcopy(graph))
    for i in range(0, attempts-1):
        m = perform_random_contraction(deepcopy(graph))    
        if m < min_cut:
            min_cut = m
    
    print (min_cut)
# coding=utf-8
from __future__ import print_function
from time import time

__author__ = 'annie'

"""
Python 2.7.9

Task is to compute strongly connected components (SCCs) and to output the sizes of the 5 largest SCCs in the given
graph, in decreasing order of sizes, separated by commas (avoid any spaces). If your algorithm finds less than 5 SCCs,
then write 0 for the remaining terms.
The file SCC.txt contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714.
Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the
head.
"""

def get_adjacency_list(path):
    """
    Возвращает словарь смежности для исходного графа и для транспонированного.
    В словаре для листьев должен быть пустой список.
    :param path: путь до файла графа
    :return: dict(vertex: [...], vertex: [...], ...), dict(vertex: [...], vertex: [...], ...)
    """
    adjacency_list = {i: [] for i in xrange(NUMBER_VERTEX)}
    adjacency_list_T = {i: [] for i in xrange(NUMBER_VERTEX)}
    with open(path) as f:
        for line in f:
            u, v = [int(i)-1 for i in line.split()]
            adjacency_list[u].append(v)
            adjacency_list_T[v].append(u)
    return adjacency_list, adjacency_list_T


def dfs1(adj):
    """
    DFS для определния порядка времени выхода из вершин.
    :param adj: словарь смежности, в ключах есть все вершины
    :return: list(vertex, vertex, ...)
    """
    next = [] # стек для обхода вершин
    order_in = [] # стек, хранит порядок входа в вершины
    order_out = [] # порядок выхода
    while adj:
        start, adj_list = adj.popitem()
        order_in.append(start)
        next.extend(['|'] + adj_list)
        while next:
            v = next.pop()
            if v == '|':
                order_out.append(order_in.pop())
                continue
            if v in adj:
                order_in.append(v)
                next.extend(['|'] + adj.pop(v))
    return order_out[::-1]


def dfs2(adj, order):
    """
    DFS для подсчета размера компонент сильной связнойсти.
    :param adj: словарь смежности, в ключах есть все вершины
    :param order: порядок обхода графа
    :return: list(size, size, ...)
    """
    next = [] # стек для обхода вершин
    sizes = []
    count_used = 0
    for start in order:
        if start in adj:
            prev_size = count_used
            count_used += 1
            next.extend(adj.pop(start))
            while next:
                v = next.pop()
                if v in adj:
                    count_used += 1
                    next.extend(adj.pop(v))
            sizes.append(count_used - prev_size)
    return sizes


def get_sizes_SCC(path, num=5):
    """
    Возвращает размеры нескольких максимальных компонент сильной связности.
    :param path: путь до файла графа
    :param num: количество компонент
    :return: str(max1,max2,max3,...)
    """
    adjacency_list, adjacency_list_T = get_adjacency_list(path)
    order = dfs1(adjacency_list_T)
    sizes = dfs2(adjacency_list, order)
    max_5_sizes = []
    for i in xrange(min(5, len(sizes))):
        m = max(sizes)
        max_5_sizes.append(m)
        sizes.remove(m)
    ans = u','.join(str(i) for i in max_5_sizes + [0]*(num-len(max_5_sizes)))
    return ans


if __name__ == '__main__':
    path = 'SCC.txt' # список рёбер
    NUMBER_VERTEX = 875714
    NUMBER_EDGES = 5105042
    start = time()
    print(get_sizes_SCC(path)) # 434821,968,459,313,211
    work = time()-start
    print('{0:.0f}m {1:.0f}s'.format(work / 60, work % 60)) # 0m 22s

from google.colab import drive
drive.mount('/content/drive')

import heapq #  imported to use a priority queue
import math # imported for using math.inf

f = open("/content/drive/MyDrive/Fall 24/CSE422/Input file.txt", "r")
lst = ''
for line in f:
    lst += line
    a = lst.split('\n')
new_lst = []
for j in a:
    new_lst.append(j.split(' '))
f.close()
print("Contents of new_lst:", new_lst)

#dictionaries
distance = {}
heuristic = {}
visited = {}

for temp in new_lst:
    if len(temp) < 2:
        continue  # skip lines that don't have enough elements
    node_name = temp[0]
    heuristic[node_name] = int(temp[1])
    distance[node_name] = {}
    visited[node_name] = False
    for i in range(2, len(temp), 2):
      if i + 1 >= len(temp):
        continue  # skip pairs that are incomplete
      neighbor_node = temp[i]
      distance[node_name][neighbor_node] = int(temp[i + 1])
      visited[neighbor_node] = False

start = input("Start node: ")
goal = input("End node: ")

p_queue = []
max_distance = math.inf
path1 = []

visited[start] = True

# push start node neighbors to the priority queue
for node, path in distance[start].items():
    heapq.heappush(p_queue, (path + heuristic[node], [start, node]))

# A* algorithm
while len(p_queue) > 0:
    cost, paths = heapq.heappop(p_queue)
    if visited[paths[-1]]:
        continue
    visited[paths[-1]] = True
    for node, path in distance[paths[-1]].items():
        paths_new = paths + [node]
        new_cost = cost - heuristic[paths[-1]] + heuristic[node] + distance[paths[-1]][node]
        heapq.heappush(p_queue, (new_cost, paths_new))
        if paths_new[-1] == goal and new_cost < max_distance:
            max_distance = new_cost
            path1 = paths_new


if path1 == []:
    print("NO PATH FOUND")
else:
    print('Path:', ' -> '.join(path1))
    print(f'Total distance: {max_distance} km')
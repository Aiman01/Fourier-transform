import matplotlib.pyplot as plt
import numpy as np
from sklearn.neighbors import NearestNeighbors
import networkx as nx


#create a sin wave
l=np.linspace(0, 2 * np.pi, 100)
x=np.cos(l)
y=np.sin(l)


#randomize the points in the wave
idx=np.random.permutation(x.size)
x=x[idx]
y=y[idx]

#create 2-NN graph between nodes
points = np.c_[x, y]
clf=NearestNeighbors(2).fit(points)
G=clf.kneighbors_graph()

T=nx.from_scipy_sparse_matrix(G)

#find shortest path from source
path=[list(nx.dfs_preorder_nodes(T, i)) for i in range(len(points))]

mindist=np.inf
minidx=0

for i in range(len(points)):
	p=path[i]
	ordered=points[p]
	cost=(((ordered[:-1]-ordered[1:])**2).sum(1)).sum()
	if cost < mindist:
		mindist=cost
		minidx=i


startingPoint=path[minidx]

xx=x[startingPoint]
yy=y[startingPoint]


plt.plot(xx, yy)
plt.show() 

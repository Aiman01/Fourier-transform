import numpy as np
from sklearn.neighbors import NearestNeighbors
import matplotlib.pyplot as plt
import networkx as nx
import cv2

img = cv2.imread('new.png',0)
edges = cv2.Canny(img,100,200)

coords=list()
for x in range(len(edges)):
	for y in range(len(edges[x])):
		if edges[x][y]==255:  coords.append([x, y])



x=np.array([i[0] for i in coords])
y=np.array([i[1] for i in coords])


points = np.c_[x, y]

clf = NearestNeighbors(2).fit(points)
G = clf.kneighbors_graph()

T = nx.from_scipy_sparse_matrix(G)

order = list(nx.dfs_preorder_nodes(T, 0))


xx = x[order]
yy = y[order]
print(list([xx, yy]))
plt.subplot(121),plt.imshow(list([xx, yy]),cmap = 'gray')
plt.title('EDITED Image'), plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(edges,cmap = 'gray')
plt.title('Edge Image'), plt.xticks([]), plt.yticks([])
plt.show()


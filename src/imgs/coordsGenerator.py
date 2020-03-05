import numpy as np
from sklearn.neighbors import NearestNeighbors
import matplotlib.pyplot as plt
import networkx as nx
import cv2

imgName='cat.PNG'
img = cv2.imread(imgName,0)
edges = cv2.Canny(img,50,200)

coords=list()

# Extract pixel coordinates from image
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


with open("img.h", "w") as file:
    file.write("float drawing[][2]={\n")
    for i in range(len(xx)):
        file.write("{"+str(xx[i])+", "+str(yy[i])+"},\n")
    file.write("};")
    file.close()

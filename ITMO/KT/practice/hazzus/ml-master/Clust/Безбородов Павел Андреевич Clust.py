import random

import numpy as np
import pandas as pd

from tqdm.notebook import tqdm as log_progress
from sklearn.manifold import TSNE
from sklearn.metrics import confusion_matrix, adjusted_rand_score, silhouette_score
from sklearn.metrics.cluster import pair_confusion_matrix
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.preprocessing import LabelEncoder

import matplotlib.pyplot as plt

ds = pd.read_csv('../kNN/wine.csv')
ds.head()

X = ds[ds.columns[1:]]
y = ds[ds.columns[:1]]
classes = y['class'].unique()
# X['Sex'] = X['Sex'].map({'M': 0, 'F': 1, 'I': 2})
X.head()

def minmax(dataset):   
    result = {}
    for column in dataset.columns:
        result[column] = {'min': dataset[column].min(axis=0), 'max': dataset[column].max(axis=0)}
    return result

def normalize(dataset, minimax):
    for column in dataset.columns:
        mmc = minimax[column]
        dataset[column] = dataset[column].map(lambda val: (val - mmc['min']) / (mmc['max'] - mmc['min']))

normalize(X, minmax(X))
X.head()

reducer = TSNE(n_components=2)
Xr = reducer.fit_transform(X.values)

def draw_clusters(X, y, colors):
    plt.figure(figsize=(10,10))
    
    for i, c in enumerate(classes):
        filtered = np.array(list(map(lambda x: x[1], filter(lambda x: y[x[0]] == c, enumerate(X)))))
        x_dots, y_dots = np.transpose(filtered)
        
        plt.scatter(x_dots, y_dots, color=colors[i], label='Class no {}'.format(c))
        plt.legend()
    
    
    plt.show()

list(map(lambda x: x[1], filter(lambda x: y.values[x[0]] == 4, enumerate(Xr))))
draw_clusters(Xr, y.values, ['red', 'pink', 'blue'])

class KMeansClassifier:
    EPS = 1e-10
    
    def __init__(self, clusters, iterations=10000):
        self.clusters = clusters
        self.iterations = iterations
        
    def distance(self, centroids, X):
        distance = np.zeros((X.shape[0], self.clusters))
        for k in range(self.clusters):
            row_norm = np.linalg.norm(X - centroids[k, :], axis=1)
            distance[:, k] = np.square(row_norm)
        return distance    
        
    def update(self, X, label):
        centroids = np.zeros((self.clusters, X.shape[1]))
        for k in range(self.clusters):
            centroids[k, :] = np.mean(X[label == k, :], axis=0)
        return centroids
            
    def fit(self, X):
        self.centroids = X[np.random.permutation(X.shape[0])[:self.clusters]]
        # print(self.centroids)
        for it in range(self.iterations):
            dist = self.distance(self.centroids, X)
            closest = np.argmin(dist, axis=1)
            new_centroids = self.update(X, closest)
            
            stop = np.all(self.centroids - new_centroids < self.EPS)
            
            self.centroids = new_centroids
            if stop:
                break
                
    def predict(self, x):
        dist = self.distance(self.centroids, x)
        return np.argmin(dist, axis=1) + 1

clf = KMeansClassifier(clusters=3)
clf.fit(X.values)

predicted = clf.predict(X.values)

remap = {3:3, 2:1, 1:2}
predicted = np.array(list(map(lambda x: remap[x], predicted)))
predicted, y.values.reshape(X.values.shape[0])

draw_clusters(Xr, predicted.reshape(y.values.shape), ['red', 'pink', 'blue'])

cm = pair_confusion_matrix(y.values.T[0], predicted)

def AdjRand(cm):
    (TN, FP), (FN, TP) = cm
    # print(FP, FN, TP, TN, TP + FN, TP + FN + FP + TN)
    
    return 2. * (TP * TN - FN * FP) / ((TP + FN) * (FN + TN) +
                                       (TP + FP) * (FP + TN))
    # return (TP + FN) / (TP + FN + FP + TN)

AdjRand(cm)

def inter_cluster_distances(labels, distances):
    n_unique_labels = len(np.unique(labels))
    cluster_distances = np.full((n_unique_labels, n_unique_labels), float('inf'))

    np.fill_diagonal(cluster_distances, 0)

    for i in np.arange(0, len(labels) - 1):
        for ii in np.arange(i, len(labels)):
            if labels[i] != labels[ii] and (distances[i, ii] < cluster_distances[labels[i], labels[ii]]):
                cluster_distances[labels[i], labels[ii]] = cluster_distances[
                    labels[ii], labels[i]] = distances[i, ii]
    return cluster_distances


def diameter(labels, distances):
    n_clusters = len(np.unique(labels))
    diameters = np.zeros(n_clusters)

    for i in range(0, len(labels) - 1):
        for ii in range(i + 1, len(labels)):
            if labels[i] == labels[ii] and distances[i, ii] > diameters[
                    labels[i]]:
                diameters[labels[i]] = distances[i, ii]
    return diameters


def dunn(X, labels):
    distances = euclidean_distances(X)

    labels = LabelEncoder().fit(labels).transform(labels)

    ic_distances = inter_cluster_distances(labels, distances)
    min_distance = min(ic_distances[ic_distances.nonzero()])
    max_diameter = max(diameter(labels, distances))

    return min_distance / max_diameter

ks = list(range(1, 10))
res_ex = []
res_in = []
for k in ks:
    clf = KMeansClassifier(clusters=k)
    clf.fit(X.values)
    predicted = clf.predict(X.values)
    
    remap = {}
    j = 1
    for p in predicted:
        if p not in remap:
            remap[p] = j
            j += 1
    
    predicted = np.array(list(map(lambda x: remap[x], predicted)))
    
    # print(X.values.shape)
    
    cm = pair_confusion_matrix(y.values.T[0], predicted)
    
    res_ex.append(AdjRand(cm))
    
    if k == 1:
        res_in.append(dunn(X.values, y.values.T[0]))
    else:
        res_in.append(dunn(X.values, predicted))

    
plt.figure(figsize=(15, 7))
plt.grid('--')
plt.plot(ks, res_in, label='internal (Dunn)')
plt.plot(ks, res_ex, label='external (Adjusted Rand)')
plt.legend()



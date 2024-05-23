import tensorflow as tf
import numpy as np

from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt
from tqdm.notebook import tqdm as log_progress 

(train_images, train_labels), (test_images, test_labels) = datasets.mnist.load_data()
# normalize
train_images, test_images = train_images / 255.0, test_images / 255.0
# reshape
train_images = train_images.reshape((60000, 28, 28, 1))
test_images = test_images.reshape((10000, 28, 28, 1))

plt.figure(figsize=(4, 4))
for i in range(3 * 3):
    plt.subplot(3, 3, i+1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i], cmap=plt.cm.binary)
    plt.xlabel(train_labels[i])
plt.show()

def build_model(layer_config):
    model = models.Sequential()
    for nc, k, p, act_f in layer_config:
        model.add(layers.Conv2D(nc, k, activation=act_f))
        model.add(layers.MaxPooling2D(p))
    model.add(layers.Flatten())
    # model.add(layers.Softmax())
    model.add(layers.Dense(10, activation='softmax'))
    return model

configs = [
    [(32, (3, 3), (2, 2), 'relu')] * 2,
    list(zip(
        [32, 64],
        [3, 3], 
        [(2, 2)] * 2, 
        ['relu'] * 2)),
    [
        (64, (6, 6), (2, 2), 'relu'),
        (64, (3, 3), (2, 2), 'softmax'),
        (32, (3, 3), (2, 2), 'relu')
    ],
    [
        (256, (3, 3), (3, 3), 'relu'),
        (128, (3, 3), (2, 2), 'relu')
    ]
]

best = None
max_acc = 0

for c in configs:
    model = build_model(c)
    model.compile(optimizer='sgd', 
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), 
              metrics=['accuracy'])
    for i in range(10):
        model.fit(train_images, train_labels, validation_data=(test_images, test_labels))
        if i in {1, 3, 5, 10}:
            loss, acc = model.evaluate(test_images, test_labels)
            if (acc > max_acc):
                max_acc = acc
                best = (c, i)
                print(best, acc)

best

def lenet5():
    model = models.Sequential()

    model.add(layers.Conv2D(32, kernel_size=3, activation='relu', input_shape=(28, 28, 1)))
    model.add(layers.BatchNormalization())
    model.add(layers.Conv2D(32, kernel_size=3, activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Conv2D(32, kernel_size=5, strides=2, padding='same', activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Dropout(0.4))

    model.add(layers.Conv2D(64, kernel_size=3, activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Conv2D(64, kernel_size=3, activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Conv2D(64, kernel_size=5, strides=2, padding='same', activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Dropout(0.4))

    model.add(layers.Flatten())
    model.add(layers.Dense(128, activation='relu'))
    model.add(layers.BatchNormalization())
    model.add(layers.Dropout(0.4))
    model.add(layers.Dense(10, activation='softmax'))
    return model

lenet = lenet5()
lenet.compile(optimizer='sgd', 
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), 
              metrics=['accuracy'])
lenet.fit(train_images, train_labels, epochs=10, validation_data=(test_images, test_labels))
lenet.evaluate(test_images, test_labels)

best_selfmade = build_model(best[0])

best_selfmade.compile(optimizer='sgd', 
                      loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), 
                      metrics=['accuracy'])
best_selfmade.fit(train_images, train_labels, epochs=best[1], validation_data=(test_images, test_labels))
best_selfmade.evaluate(test_images, test_labels)

def show_matrices(model, test_x, test_y):
    confusion_matrix = np.full((10, 10), 0)
    max_confusion_index_matrix = np.full((10, 10, 2), -1.)
    print('Loss: {}, Accuracy: {}'.format(*model.evaluate(test_x, test_y)))
    predicted = model.predict(test_x)
    for i in range(len(test_x)):
        actual = test_y[i]
        predict = predicted[i]
        predict_idx = np.argmax(predict)
        confusion_matrix[actual][predict_idx] += 1

        for j in range(len(predict)):
            score = predict[j]
            if max_confusion_index_matrix[actual][j][0] < score:
                max_confusion_index_matrix[actual][j][0] = score
                max_confusion_index_matrix[actual][j][1] = i
                
    print(confusion_matrix)
    
    plt.figure(figsize=(20, 20))
    for i in range(10):
        for j in range(10):
            plt.subplot(10, 10, i*10+j+1)
            plt.xticks([])
            plt.yticks([])
            plt.grid(False)
            assert(test_y[int(max_confusion_index_matrix[i][j][1])] == i)
            plt.imshow(test_x[int(max_confusion_index_matrix[i][j][1])], cmap=plt.cm.binary)
            plt.xlabel(max_confusion_index_matrix[i][j][0])
    plt.show()

show_matrices(best_selfmade, test_images, test_labels)

show_matrices(lenet, test_images, test_labels)

(f_train_images, f_train_labels), (f_test_images, f_test_labels) = datasets.fashion_mnist.load_data()
# normalize
f_train_images, f_test_images = f_train_images / 255.0, f_test_images / 255.0
# reshape
print(f_train_images.shape, f_test_images.shape)
f_train_images = f_train_images.reshape((60000, 28, 28, 1))
f_test_images = f_test_images.reshape((10000, 28, 28, 1))

f_best_selfmade = build_model(best[0])

f_best_selfmade.compile(optimizer='sgd', 
                      loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), 
                      metrics=['accuracy'])
f_best_selfmade.fit(f_train_images, f_train_labels, epochs=best[1], validation_data=(f_test_images, f_test_labels))

f_lenet = lenet5()
f_lenet.compile(optimizer='sgd', 
                loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), 
                metrics=['accuracy'])
f_lenet.fit(f_train_images, f_train_labels, epochs=10, validation_data=(f_test_images, f_test_labels))
f_lenet.evaluate(f_test_images, f_test_labels)

show_matricesw_matrices(f_best_selfmade, f_test_images, f_test_labels)

show_matrices(f_lenet, f_test_images, f_test_labels)



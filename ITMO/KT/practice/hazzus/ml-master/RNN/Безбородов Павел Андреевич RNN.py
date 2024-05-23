import re
import string
import random
import markovify

import numpy as np
import tensorflow as tf

from sklearn import preprocessing
from tensorflow.keras.utils import to_categorical
from tensorflow.keras import models, layers
from tensorflow.keras.preprocessing import sequence

def get_text(filepath):
    with open(filepath, 'r') as f:
        raw = f.read()
    raw = raw.lower()
    return re.sub(r'[^а-яА-Я.!?…\n]+', ' ', raw)

def get_vocab(text):
    res = []
    rev = {}
    for c in text:
        if c not in res:
            rev[c] = len(res)
            res.append(c)
    return rev, res

def encode(s, remap):
    return [remap[c] for c in s]

def div(spltd, max_len):
    res = []
    for spl in spltd:
        spl += '.'
        res += [spl[i:i+max_len] for i in range(0, len(spl), max_len)]
    return res

maxlen = 80
bsize = 64

zar = get_text('zaratustra.txt')
print('Text length:', len(zar))
voc, revoc = get_vocab(zar)
count = len(revoc)
print('Vocab power:', count)

# I really tried but it all only got bad things
# splitted = re.split(r'[\?\!\.…]+', zar)
# splitted = div(splitted, maxlen)
# splitted = filter(lambda x: len(x) != 0, zar.split())
# splitted = [encode(s, voc) + [voc[' ']] for s in splitted]
# splitted[:5]
# maxlen = max(map(len, splitted))

# filled = sequence.pad_sequences(splitted, maxlen=maxlen+1, value=voc[' '])
filled = np.array(encode(zar, voc))
# for i in range(0, len(zar) - maxlen, maxlen):
#     
filled, filled.shape

char_dataset = tf.data.Dataset.from_tensor_slices(filled.reshape((-1,)))
sequences = char_dataset.batch(maxlen+1, drop_remainder=True)

def splt(chunk):
    input_text = chunk[:-1]
    target_text = chunk[1:]
    return input_text, target_text

dataset = sequences.map(splt)

dataset = dataset.shuffle(1000).batch(bsize, drop_remainder=True)
dataset

# TODO more logic for arch
def build_model(vocab_size, batch_size):
    model = models.Sequential([
        layers.Embedding(vocab_size, 64, batch_input_shape=[batch_size, None]),
        layers.LSTM(256, return_sequences=True, stateful=True),
        layers.Dropout(0.2),
        layers.Dense(vocab_size, activation='softmax')
    ])
    return model

checkpoint = tf.keras.callbacks.ModelCheckpoint(filepath='chpts/{epoch}', save_weights_only=True)

def generate_text(model, start_string, length):
    start = encode(start_string, voc)
    start = tf.expand_dims(start, 0)
    
    result = []

    model.reset_states()
    for i in range(length):
        predictions = model(start)
        predictions = tf.squeeze(predictions, 0)
        
        predicted_id = tf.math.argmax(predictions, axis=1)[-1]
        
        # print(encode(tf.math.argmax(predictions, axis=1), revoc))
        
        start = tf.expand_dims([predicted_id], 0)

        result.append(revoc[predicted_id])
        # result += encode(predicted_ids, revoc)

    return (start_string + ''.join(result))

model = build_model(len(voc), bsize)1
model.compile(optimizer=tf.keras.optimizers.Adagrad(learning_rate=0.1), 
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True), metrics=['accuracy'])

i, more = 150, 450
model.fit(dataset, initial_epoch=i, epochs=i+more, callbacks=[checkpoint])

sbatch_model = build_model(len(voc), 1)
sbatch_model.load_weights(tf.train.latest_checkpoint('chpts'))
sbatch_model.build(tf.TensorShape([1, None]))

print(generate_text(sbatch_model, 'заратустра сказал', 1000))

corpus = list(map(lambda x: list(x + '.'), re.split(r'[\?\!\.…]+', zar)))

chain = markovify.Chain(corpus=corpus, state_size=5)
print(' '.join([''.join(chain.walk()) for _ in range(100)]))



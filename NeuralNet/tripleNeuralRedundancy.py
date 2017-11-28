
#==============#
# tripleNeuralRedundancy.py  #
# ECE 2195 DCA #
# Team 2       #
#==============#

# Based On...
'''
A linear regression learning algorithm example using TensorFlow library.
Author: Aymeric Damien
Project: https://github.com/aymericdamien/TensorFlow-Examples/
'''

# Imports
from __future__ import print_function
import tensorflow as tf
import numpy
import sys

rng = numpy.random

# Parameters
learning_rate   = 0.03
training_epochs = 1000
NUM_SENSORS     = 3;

# Training Data
train_V = numpy.empty([0, NUM_SENSORS])

train_T = numpy.empty([1, 0])

test_V = numpy.empty([0, NUM_SENSORS])

print("NOTE: file must exist, \"train_triplex.txt\")\n" );
# TRAINS NETWORK on assumption that VOLTAGE=TEMPERATURE is true
f = open("train_triplex.txt", 'r')
for line in f:
  linestring = str(line)
  tokenized = linestring.split(", ")
  # tokenized [0] voltage1
  # tokenized [1] voltage2
  # tokenized [2] voltage3
  # tokenized [3] temperature
  vrow =  numpy.array([[float(tokenized[0]), float(tokenized[1]), float(tokenized[2])]])
  train_V = numpy.append(train_V, vrow, axis=0);

  train_T = numpy.append(train_T, float(tokenized[3]));

print(train_V.shape, train_T.shape)
n_samples = train_V.shape[0]

# infilename    =        input( " Enter the test input filename:            " );
# outfilename   =        input( " Enter the inferred output filename:       " );
infilename = "v_triplex_test.txt"
outfilename = "inferred_tnr.txt"

f = open(infilename, 'r')

for line in f:
    linestring = str(line)
    tokenized = linestring.split(", ")
    # tokenized [0] voltage1
    # tokenized [1] voltage2
    # tokenized [2] voltage3
    # tokenized [3] temperature
    vrow =  numpy.array([[float(tokenized[0]), float(tokenized[1]), float(tokenized[2])]])
    test_V = numpy.append(test_V, vrow, axis=0);

f.close()

# modifications based on:
'''
https://medium.com/all-of-us-are-belong-to-machines/gentlest-intro-to-tensorflow-part-3-matrices-multi-feature-linear-regression-30a81ebaaa6c
'''

# tf Graph Input
X = tf.placeholder(tf.float32, [None, NUM_SENSORS], name="Voltages")
Y = tf.placeholder("float")

# Set model weights
W = tf.Variable(tf.zeros([NUM_SENSORS, 1]), name="weight")
b = tf.Variable(tf.zeros([1]), name="bias")

# Construct a linear model
prediction = tf.add(tf.matmul(X, W), b)

# Mean squared error
cost = tf.reduce_sum(tf.pow(prediction - Y, 2))/(2 * n_samples)
# Gradient descent
#  Note, minimize() knows to modify W and b because Variable objects are trainable=True by default
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

# Start training
with tf.Session() as sess:
# Run the initializer
    sess.run(init)

    # Fit all training data
    for epoch in range(training_epochs):
        for (x, t) in zip(train_V, train_T):
            v = numpy.array([x])
            sess.run(optimizer, feed_dict={X: v, Y: t})

    t_out = sess.run(prediction, feed_dict={X: test_V});

    dataFile = open( outfilename, 'w' )
    print(t_out.shape)
    # Print Calculations
    idx = 0;
    print(test_V.shape)
    for temp in t_out:
        print(str( test_V[idx][0]) + ", " +
              str( test_V[idx][1]) + ", " +
              str( test_V[idx][2]) + ", " + str( temp[0] ) );

        dataFile.write(str( test_V[idx][0]) + ", " +
                       str( test_V[idx][1]) + ", " +
                       str( test_V[idx][2]) + ", " + str( temp[0] ) + "\n");
        idx += 1

    dataFile.close()
# END triple neural redundancy.py

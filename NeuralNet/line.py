
#==============#
# Line.py      #
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
import matplotlib.pyplot as plt

rng = numpy.random

# Parameters
learning_rate   = 0.03
training_epochs = 1000

# Training Data
train_X = numpy.asarray([])

train_Y = numpy.asarray([])
test_voltages = numpy.asarray([])


print("NOTE: file must exist, \"train.txt\")" );
# TRAINS NETWORK on assumption that VOLTAGE=TEMPERATURE is true
f = open("train.txt", 'r')
for line in f:
  linestring = str(line)
  tokenized = linestring.split(", ")
  train_X = numpy.append(train_X, float(tokenized[0]));
  train_Y = numpy.append(train_Y, float(tokenized[1]));

n_samples = train_X.shape[0]

infilename    =        input( " Enter the test input      filename:       " );
outfilename   =        input( " Enter the inferred output filename:       " );
f = open(infilename, 'r')

for line in f:
    linestring = str(line)
    tokenized = linestring.split(", ")
    # tokenized [0] voltage
    # tokenized [1] temperature
    test_voltages = numpy.append(test_voltages, float(tokenized[0]));

f.close()

# tf Graph Input
X = tf.placeholder("float")
Y = tf.placeholder("float")

# Set model weights
W = tf.Variable(rng.randn(), name="weight")
b = tf.Variable(rng.randn(), name="bias")

# Construct a linear model
pred = tf.add(tf.multiply(X, W), b)

# Mean squared error
cost = tf.reduce_sum(tf.pow(pred-Y, 2))/(2*n_samples)
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
        for (x, y) in zip(train_X, train_Y):
            sess.run(optimizer, feed_dict={X: x, Y: y})

    t_out = sess.run(pred, feed_dict={X: test_voltages});


    dataFile = open( outfilename, 'w' )

    # Print Calculations
    idx = 0;
    for temp in t_out:
        print(str( min([test_voltages[idx], 0]) )  + ", " + str( temp ) );
        dataFile.write( str( min([test_voltages[idx], 0]) )  + ", " + str( temp ) + "\n" );
        idx += 1

    dataFile.close()
# END line.py

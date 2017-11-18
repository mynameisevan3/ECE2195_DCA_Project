
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
learning_rate   = 0.01
training_epochs = 1000
display_step    = 50

# Training Data
train_X = numpy.asarray([0.0,
0.033,
0.066,
0.099,
0.132,
0.165,
0.198,
0.231,
0.264,
0.29700000000000004,
0.33,
0.363,
0.396,
0.42900000000000005,
0.462,
0.495,
0.528,
0.561,
0.5940000000000001,
0.627,
0.66,
0.6930000000000001,
0.726,
0.759,
0.792,
0.8250000000000001,
0.8580000000000001,
0.891,
0.924,
0.9570000000000001,
0.99,
1.0230000000000001,
1.056,
1.089,
1.122,
1.155,
1.1880000000000002,
1.221,
1.254,
1.2870000000000001,
1.32,
1.353,
1.3860000000000001,
1.419,
1.452,
1.485,
1.518,
1.5510000000000002,
1.584,
1.617,
1.6500000000000001,
1.683,
1.7160000000000002,
1.749,
1.782,
1.8150000000000002,
1.848,
1.881,
1.9140000000000001,
1.947,
1.98,
2.013,
2.0460000000000003,
2.079,
2.112,
2.145,
2.178,
2.2110000000000003,
2.244,
2.277,
2.31,
2.343,
2.3760000000000003,
2.4090000000000003,
2.442,
2.475,
2.508,
2.541,
2.5740000000000003,
2.607,
2.64,
2.673,
2.706,
2.7390000000000003,
2.7720000000000002,
2.805,
2.838,
2.871,
2.904,
2.9370000000000003,
2.97,
3.003,
3.036,
3.069,
3.1020000000000003,
3.1350000000000002,
3.168,
3.201,
3.234,
3.2670000000000003,])


train_Y = numpy.asarray([-196.32676255716976,
-187.63614905251924,
-190.87886467138813,
-179.8562529195554,
-182.72512203806505,
-173.27074183209427,
-176.39529591986008,
-181.597424767771,
-162.45420092690742,
-163.4399266352875,
-152.54651427547577,
-156.130683596623,
-148.92175254226288,
-138.62251301627356,
-148.4290154790953,
-137.7884633358443,
-137.47924421914797,
-132.99961748805657,
-128.37441068217095,
-119.31447865801441,
-115.96410617616615,
-119.70450476780834,
-109.53949048063436,
-112.66844301215119,
-103.98346232208873,
-97.74597194870643,
-94.31991504790884,
-99.72369809356034,
-97.4235996298069,
-76.5730914202998,
-79.36203379131626,
-68.70098217368738,
-66.54273261066237,
-71.67219664524077,
-63.44999835899764,
-51.48526502329758,
-53.7629864856858,
-43.05187691185698,
-46.504350896022146,
-53.069901143444355,
-42.159987227809914,
-32.189628692828876,
-34.931427218231114,
-33.61078972438103,
-29.737538751948097,
-22.592002466508475,
-24.732162377957625,
-14.352345433556156,
0.05838792034603202,
-7.324843280368421,
 9.377631013472055,
-5.34955373063749,
 13.678986963216941,
 20.036700370723583,
 24.44130588240611,
 19.850179218699182,
 15.253962279519625,
 37.53302248029119,
 25.727242036429075,
 29.450688234270224,
 48.62719437822567,
 35.492742852901486,
 42.08445799036404,
 46.45950957824753,
 52.82521549442087,
 61.56570853884456,
 59.073584771210434,
 74.12167288029934,
 76.60215872283075,
 84.30702529969138,
 71.78423374963187,
 85.16708836239972,
 80.70615342739764,
 93.06874454524717,
 104.3502640262803,
 104.57825453920003,
 107.99143756900881,
 106.65376785249829,
 115.53314838962332,
 106.06270793439647,
 125.56862102439604,
 133.63852082778487,
 124.81727523977612,
 123.27893900457211,
 145.23350467846765,
 131.28725563087778,
 146.89956257957797,
 145.94174151168104,
 146.37211814312766,
 158.1732720313043,
 162.5401959022305,
 164.264268371317,
 160.69012976788414,
 162.90656450345287,
 168.37048188353077,
 183.01928829881484,
 191.8082239329309,
 191.05967243253522,
 200.72890502715097,
 203.79684055910687])
n_samples = train_X.shape[0]

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

        # Display logs per epoch step
        # if (epoch+1) % display_step == 0:
        #     c = sess.run(cost, feed_dict={X: train_X, Y:train_Y})
        #     print("Epoch:", '%04d' % (epoch+1), "cost=", "{:.9f}".format(c), \
        #         "W=", sess.run(W), "b=", sess.run(b))

    # print("Optimization Finished!")
    # training_cost = sess.run(cost, feed_dict={X: train_X, Y: train_Y})
    # print("Training cost=", training_cost, "W=", sess.run(W), "b=", sess.run(b), '\n')
    #
    # # Graphic display
    # plt.plot(train_X, train_Y, 'ro', label='Original data')
    # plt.plot(train_X, sess.run(W) * train_X + sess.run(b), label='Fitted line')
    # plt.legend()
    # plt.show()
    #
    # # Testing example
    # test_X = numpy.asarray([6.83, 4.668, 8.9, 7.91, 5.7, 8.7, 3.1, 2.1])
    # test_Y = numpy.asarray([1.84, 2.273, 3.2, 2.831, 2.92, 3.24, 1.35, 1.03])
    #
    # print("Testing... (Mean square loss Comparison)")
    # testing_cost = sess.run(
    #     tf.reduce_sum(tf.pow(pred - Y, 2)) / (2 * test_X.shape[0]),
    #     feed_dict={X: test_X, Y: test_Y})  # same function as cost above
    # print("Testing cost=", testing_cost)
    # print("Absolute mean square loss difference:", abs(
    #     training_cost - testing_cost))
    #
    # plt.plot(test_X, test_Y, 'bo', label='Testing data')
    # plt.plot(train_X, sess.run(W) * train_X + sess.run(b), label='Fitted line')
    # plt.legend()
    # plt.show()

    test_voltages = numpy.asarray([0, 1.1, 2, 2.1, 3, 3.3])

    print(sess.run(pred, feed_dict={X: test_voltages}))



# END line.py

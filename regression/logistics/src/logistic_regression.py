# -*- coding : utf-8 -*-  
from __future__ import print_function

import os, sys
import time, random
import numpy as np
import matplotlib as plt

def sigmoid(x, w, b):
    ''' np.exp(-w.dot(x) - b) 不能太大或太小 '''
    return 1 / (np.exp(-w.dot(x) - b) + 1)

def batch_gradient_descent(input_x, input_y, eta, epochs) :
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0; w = np.zeros(len(input_x[0]))
    for epoch in range(epochs):
        delta_w = sum([(y - sigmoid(x, w, b)) * x / lenx for x, y in zip(input_x, input_y)])
        delta_b = sum([(y - sigmoid(x, w, b)) / lenx for x, y in zip(input_x, input_y)])
        w = w + eta * delta_w
        b = b + eta * delta_b

        if epoch % 100 == 0:
            print ("epoch =", epoch, " w = ", w, " b =", b)
    return w, b

def minibatch_gradient_descent (input_x, input_y, eta, epochs, minibatch = 10):
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0; w = np.zeros(len(input_x[0]))
    for epoch in range(epochs):
        for batch in range(lenx // minibatch):
            batch_x = input_x[batch * minibatch : batch * minibatch + minibatch]
            batch_y = input_y[batch * minibatch : batch * minibatch + minibatch]
            delta_w = sum([(y - sigmoid(x, w, b)) * x / minibatch for x, y in zip(batch_x, batch_y)])
            delta_b = sum([(y - sigmoid(x, w, b)) / minibatch for x, y in zip(batch_x, batch_y)])
            w = w + eta * delta_w
            b = b + eta * delta_b
        if epoch % 100 == 0:
            print ("epoch =", epoch, " w = ", w, " b =", b)
    return w, b

def sto_gradient_descent (input_x, input_y, eta, epochs, minibatch = 10):
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0; w = np.zeros(len(input_x[0]))
    for epoch in range(epochs):
        for batch in range(lenx // minibatch):
            batch_x = input_x[batch * minibatch : batch * minibatch + minibatch]
            batch_y = input_y[batch * minibatch : batch * minibatch + minibatch]
            delta_w = sum([(y - sigmoid(x, w, b)) * x / minibatch for x, y in zip(batch_x, batch_y)])
            delta_b = sum([(y - sigmoid(x, w, b)) / minibatch for x, y in zip(batch_x, batch_y)])
            w = w + eta * delta_w
            b = b + eta * delta_b
        if epoch % 100 == 0:
            print ("epoch =", epoch, " w = ", w, " b =", b)
    return w, b


if __name__ == '__main__':
    w = np.array([1, 2, 3])
    x = [np.random.normal(loc = 0, scale = 1, size = 3) for index in range(1000)]
    y = [sigmoid(index, w, 3) for index in x]
    '''
    注意y值，当w.dot(x) + b太大会导致y恒等1，因为计算有误差

    '''
    w, b = sto_gradient_descent(x, y, eta = 0.5, epochs = 10000)
    print (w, b)

# -*- coding:utf-8 -*-  
from __future__ import print_function

import os, sys
import time, random
import numpy as np
import matplotlib as plt

def batch_gradient_descent(input_x, input_y, eta, epochs) :
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0
    w = np.zeros(len(input_x[0]))
    for epoch in range(epochs):
        delta_w = sum([((y - w.dot(x) - b) * -x) / lenx for x, y in zip(input_x, input_y)])
        delta_b = sum([((y - w.dot(x) - b) / -lenx) for x, y in zip(input_x, input_y)])
        w = w - eta * delta_w
        b = b - eta * delta_b
        print (w, b)
    return w, b

def minibatch_gradient_descent(input_x, input_y, eta, epochs, minibatch = 10):
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0
    w = np.zeros(len(input_x[0]))
    for epoch in range(epochs):
        for batch in range(lenx // minibatch):
            batch_x = input_x[batch * minibatch : (batch + 1) * minibatch]
            batch_y = input_y[batch * minibatch : (batch + 1) * minibatch]

            delta = [((y - w.dot(x) - b) / -minibatch) for x, y in zip(batch_x, batch_y)]
            delta_w = sum(val * x for val, x in zip(delta, input_x))
            delta_b = sum(delta)

            w = w - eta * delta_w
            b = b - eta * delta_b
    return w, b

def sto_gradient_descent(input_x, input_y, eta, epochs) :
    lenx = len(input_x)
    leny = len(input_y)
    
    if lenx != leny:
        raise Exception("length of input_x is not same as input_y")
    if lenx == 0:
        raise Exception("length of input_x and input_y should not be 0")

    b = 0.0
    w = np.zeros(len(input_x[0]), dtype = np.float64)
    for epoch in range(epochs):
        for x, y in zip(input_x, input_y) :
            test = w.dot(x)
            delta_w = (y - w.dot(x) - b) * -x
            delta_b = (y - w.dot(x) - b) * -1
            w = w - eta * delta_w
            b = b - eta * delta_b
            print (w, b)
    return w, b


if __name__ == '__main__':
    w = [1, 2, 3]
    # x = [np.random.normal(loc = 1, scale = 1, size = 1) for index in range(1000)]
    # y = [index[0] * 1 + index[1] * 2 + index[2] * 3 + 3 for index in x]
    # y = [index * 3 + 3 for index in x]
    # w, b = batch_gradient_descent(x, y, eta = 0.01, epochs = 1000)
    # print (w, b)
    # w, b = minibatch_gradient_descent(x, y, eta = 0.01, epochs = 1000, minibatch = 20)
    # print (w, b)
    x = [np.array([index]) + np.random.normal(loc = 1, scale = 1, size = 1) for index in range(10)]
    y = [np.array([index + 1]) for index in range(10)]
    w, b = minibatch_gradient_descent(x, y, eta = 0.001, epochs = 1000)
    print (w, b)
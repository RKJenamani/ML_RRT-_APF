import cv2
import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd
import sklearn 
import sklearn.datasets 
import sklearn.linear_model 
import matplotlib 
import sys
import math

img = cv2.imread('images/img0.jpg')
ideal_path = open('data/output.txt')

def ispath(x,y):
	if img[x,y]<200 and img[x,y]>100:
		return True
	else
		return False

def loss(A_L):
	#make graph and array
	return lossfunction(array)

def lossfunction(epoch_array):
	step_down = 100
	error = 0
	#for each point in ideal and each epoch:
		error += (idealx - epochx)*(idealx - epochx) + (idealy - epochy)*(idealy - epochy)
	return error/step_down

def test_train_split():

def sigmoid(Z):
	return 1/(1 + np.exp(-Z))

def relu(Z):
    A = np.maximum(0,Z)
    cache = Z 
    return A, cache

def relu_backward(dA, cache):
    Z = cache
    dZ = np.array(dA, copy=True)  
    dZ[Z <= 0] = 0
    return dZ

def initialize_parameters_deep(layer_dims):
    parameters = {}
    L = len(layer_dims)            
    for l in range(1, L):
        parameters['W' + str(l)] = np.random.randn(layer_dims[l], layer_dims[l-1]) / np.sqrt(layer_dims[l-1]) 
        parameters['b' + str(l)] = np.zeros((layer_dims[l], 1))
        
        assert(parameters['W' + str(l)].shape == (layer_dims[l], layer_dims[l-1]))
        assert(parameters['b' + str(l)].shape == (layer_dims[l], 1))
    return parameters

def linear_activation_forward(A_prev, W, b, activation):
    if activation == "Output":
        Z = W.dot(A_prev) + b
        linear_cache = (A_prev, W, b)
        A, activation_cache = Z,Z
    
    elif activation == "relu":
        Z = = W.dot(A_prev) + b
        linear_cache = (A_prev, W, b)
        A, activation_cache = relu(Z)
    
    cache = (linear_cache, activation_cache)
    return A, cache

def forward_prop(X,weights):
	caches = []
    A = X
    L = len(parameters) // 2                
    for l in range(1, L):
        A_prev = A 
        A, cache = linear_activation_forward(A_prev, parameters['W' + str(l)], parameters['b' + str(l)], activation = "relu")
        caches.append(cache)
 
    A_L, cache = linear_activation_forward(A, parameters['W' + str(L)], parameters['b' + str(L)], activation = "Output")
    caches.append(cache)
    
    return A_L, caches


def linear_activation_backward(dA, cache, activation):
    linear_cache, activation_cache = cache
    
    if activation == "relu":
        dZ = relu_backward(dA, activation_cache)
        A_prev, W, b = linear_cache
    	m = A_prev.shape[1] 
        dW = 1./m * np.dot(dZ,A_prev.T)
    	db = 1./m * np.sum(dZ, axis = 1, keepdims = True)
    	dA_prev = np.dot(W.T,dZ)
        
    elif activation == "Output":
        dZ = dA
        A_prev, W, b = linear_cache
    	m = A_prev.shape[1] 
        dW = 1./m * np.dot(dZ,A_prev.T)
    	db = 1./m * np.sum(dZ, axis = 1, keepdims = True)
    	dA_prev = np.dot(W.T,dZ)
    
    return dA_prev, dW, db

def backward_prop(A_L,weights):
	grads = {}
    L = len(caches) 
    m = A_L.shape[1]    
    dA_L = loss(A_L)
    current_cache = caches[L-1]
    grads["dA" + str(L)], grads["dW" + str(L)], grads["db" + str(L)] = linear_activation_backward(dA_L, current_cache, activation = "Output")
    
    for l in reversed(range(L-1)):
        current_cache = caches[l]
        dA_prev_temp, dW_temp, db_temp = linear_activation_backward(grads["dA" + str(l + 2)], current_cache, activation = "relu")
        grads["dA" + str(l + 1)] = dA_prev_temp
        grads["dW" + str(l + 1)] = dW_temp
        grads["db" + str(l + 1)] = db_temp

    return grads

def update_parameters(parameters, grads, learning_rate):
    L = len(parameters) // 2 # number of layers in the neural network

    # Update rule for each parameter 
    for l in range(L):
        parameters["W" + str(l+1)] = parameters["W" + str(l+1)] - learning_rate * grads["dW" + str(l+1)]
        parameters["b" + str(l+1)] = parameters["b" + str(l+1)] - learning_rate * grads["db" + str(l+1)]
        
    return parameters

def final_model(X, Y, layers_dims, learning_rate, iterations, print_cost=False):
    costs = [] 
    weights = initialize_parameters_deep(layers_dims)
    
    for i in range(0, iterations):
        A_L, caches = forward_prop(X, weights)
        cost = compute_cost(A_L, Y)
        grads = backward_prop(A_L, Y, caches)
        parameters = update_parameters(weights, grads, learning_rate)
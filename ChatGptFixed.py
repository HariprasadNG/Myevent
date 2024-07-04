import numpy as np
import matplotlib.pyplot as plt


def ReLU(z):
  return np.maximum(0,z)

def linear(z):
  return z

def linearPrime(z):
  return 1

def ReLUPrime(z):
  a=ReLU(z)
  return 1 if a > 0 else 0

def createNW (nuronsInlayer, layers):
  weights = []
  bias = []
  actfunc = []
  for i in range(layers):
    weights.append(np.random.rand(nuronsInlayer, nuronsInlayer) - .5)
    #bias.append(np.random.rand(nuronsInlayer,1) - .5)
    bias.append(np.zeros((nuronsInlayer,1)))
    actfunc.append(np.full(nuronsInlayer, {"act": linear, "actPrime": linearPrime}))
  return  weights, bias, actfunc

def addInputAndOutPutLayers (inputSize, weights, bias, actfunc, outputsize , adjustlastLayers = True, multiplier = 8):
   x = weights[0].shape[0]
   
   if (adjustlastLayers):
    weights[0] = np.random.rand(x, inputSize) - .5
    weights[-1] = np.random.rand(outputSize, x) - .5
    bias[-1] = np.zeros((outputSize, 1))
    actfunc[-1] = np.full(outputSize, actfunc[-1][0])
    return weights, bias, actfunc
   
   newFrontW = []
   newFrontB = []
   newFrontA = []
   while (x > inputSize):
      if (multiplier * inputSize < x):
         newFrontW.append(np.random.rand(inputSize*multiplier, inputSize))
         newFrontB.append(np.zeros(( inputSize*multiplier,1)))
         newFrontA.append(np.full(inputSize*multiplier, {"act": linear, "actPrime": linearPrime}))
         inputSize = inputSize*multiplier
      else:
         newFrontW.append(np.random.rand(x, inputSize))
         newFrontB.append(np.zeros(( x,1)))
         newFrontA.append(np.full(x, {"act": linear, "actPrime": linearPrime}))
         inputSize = x
    
   newEndW = []
   newEndB = []
   newEndA = []
   while (x > outputsize):
      if ( int(x/multiplier) > outputsize):
         newEndW.append(np.random.rand(int(x/multiplier), x))
         newEndB.append(np.zeros((int(x/multiplier),1)))
         newEndA.append(np.full(int(x/multiplier), {"act": linear, "actPrime": linearPrime}))
         x = int(x/multiplier)
      else:
          newEndW.append(np.random.rand(outputsize, x))
          newEndB.append(np.zeros((outputsize,1)))
          newEndA.append(np.full(outputsize, {"act": linear, "actPrime": linearPrime}))
          x = outputsize
      
   return  newFrontW+weights+newEndW, newFrontB+bias+newEndB, newFrontA+actfunc+newEndA
         

def forwardProp(input, weights, bias, actfunc):
  layerPOut = input
  hiddenLayerOut = []
  hiddenLayerZ = []
  for i, w in enumerate(weights):
    layerZ = (w @ layerPOut) + bias[i]
    hiddenLayerZ.append(layerZ)
    layerOut = []
    for j, z in enumerate(layerZ):
      layerOut.append(actfunc[i][j]["act"](z[0]))
    layerPOut = np.reshape(layerOut, (len(layerOut), 1))
    hiddenLayerOut.append(layerPOut)
  return layerPOut, hiddenLayerOut, hiddenLayerZ

def computeGradient(input, expectedOut, hiddenLayerOut, hiddenLayerZ, weights, bias, actfunc):
    dw = []
    db = []
    # Append input to the beginning of hiddenLayerOut for convenience
    hiddenLayerOut.insert(0, input)
    
    # Initial gradient of the cost with respect to the activation (output layer)
    da = hiddenLayerOut[-1] - expectedOut

    for i, hz in reversed(list(enumerate(hiddenLayerZ))):
        # Compute the derivative of the error with respect to z (before activation)
        de = []

        for j, daj in enumerate(da):
            de.append(daj[0] * actfunc[i][j]["actPrime"](hz[j][0]))

        de = np.reshape(de, (len(de), 1))
            
        # Compute gradients for biases and weights
        db.append(de)
        dw.append(de @ hiddenLayerOut[i].T)
        
        # Update da for the next layer (backpropagate)
        da = weights[i].T @ de
    
    # Reverse gradients to match the order of layers
    return dw[::-1], db[::-1]

def adjustWeights(weights, dw, bias, db, eta):
    for i in range(len(weights)):
        weights[i] -= eta * dw[i]
        bias[i] -= eta * db[i]
    return weights, bias

def runForEpoch(input, expectedOut, weights, bias, actfunc, epochct=100):
  for x in range(epochct):
    layerOut, hiddenLayerOut, hiddenLayerZ = forwardProp(input, weights, bias, actfunc)
    dw, db = computeGradient(input, expectedOut, hiddenLayerOut, hiddenLayerZ, weights, bias, actfunc)
    weights, bias = adjustWeights(weights, dw, bias, db, .0005)

  return weights, bias

nuron_per_layer = 16
layers = 3
inputSize = 5
outputSize = 2
weights, bias, actfunc = createNW(nuron_per_layer, layers)
weights, bias, actfunc = addInputAndOutPutLayers(inputSize,weights, bias, actfunc, outputSize)
weights = np.load('weights.npy', allow_pickle=True)
bias = np.load('bias.npy', allow_pickle=True)


for i in range(100000):
  input = np.zeros((inputSize,1))
  input[0][0] = np.random.rand(1,1)[0][0]#0.1#i%100 #np.random.rand(1,1)[0][0] - 0.5
  input[1][0] = np.random.rand(1,1)[0][0]#0.5#i%100 + 1 #np.random.rand(1,1)[0][0] - 0.5

  # input[2][0] = 0.01 #Addition
  # expectedOut = np.zeros((outputSize,1))
  # expectedOut[0][0] = input[0][0] + input[1][0] 
  # weights, bias = runForEpoch(input, expectedOut, weights, bias, actfunc)

  input[2][0] = 0
  input[3][0] = 0.01 #Multiplication
  expectedOut = np.zeros((outputSize,1))
  expectedOut[0][0] = input[0][0] * input[1][0] 
  weights, bias = runForEpoch(input, expectedOut, weights, bias, actfunc)

  input[3][0] = 0
  input[4][0] = 0.01#0.07595 #Reflect
  expectedOut = np.zeros((outputSize,1))
  expectedOut[0][0] = -input[0][0] 
  expectedOut[1][0] = input[1][0] 
  weights, bias = runForEpoch(input, expectedOut, weights, bias, actfunc)
    
np.save("weights", np.array(weights, dtype=object), allow_pickle=True)
np.save("bias", np.array(bias, dtype=object), allow_pickle=True) 

for i in range (1000):
    input = np.zeros((inputSize,1))
    input[0][0] = np.random.rand(1,1)[0][0]
    input[1][0] = np.random.rand(1,1)[0][0]
    expectedOut = np.zeros((outputSize,1))

    # input[2][0] = 0.01
    # expectedOut[0][0] = -input[0][0] - input[1][0] 
    # layerOut, hiddenLayerOut, hiddenLayerZ = forwardProp(input, weights, bias, actfunc)
    # plt.scatter(expectedOut[0][0], expectedOut[1][0], s=10, c='RED', marker= '|')
    # plt.scatter(layerOut[0][0], layerOut[1][0], s=10, c='BLUE', marker= 'o')

    # input[3][0] = 0.01
    # expectedOut[0][0] = -input[0][0] * input[1][0] 
    # layerOut, hiddenLayerOut, hiddenLayerZ = forwardProp(input, weights, bias, actfunc)
    # plt.scatter(expectedOut[0][0], expectedOut[1][0], s=10, c='YELLOW', marker= '|')
    # plt.scatter(layerOut[0][0], layerOut[1][0], s=10, c='ORANGE', marker= 'o')

    input[4][0] = 0.01
    expectedOut[0][0] = -input[0][0] 
    expectedOut[1][0] = input[1][0] 
    layerOut, hiddenLayerOut, hiddenLayerZ = forwardProp(input, weights, bias, actfunc)
    plt.scatter(input[0][0], input[1][0], s=10, c='GREEN', marker= 'o')
    plt.scatter(layerOut[0][0], layerOut[1][0], s=10, c='BLACK', marker= 'o')
  
    # if i%1 == 0:
    #     print("\n", i, " input \n", input)
    #     print("\n expected \n",expectedOut)
    #     print("\n", i, "out \n", layerOut)

plt.show()

# print("weights \n", weights)
# print("\nbias \n", bias)
# print("\n out \n", layerOut)


    

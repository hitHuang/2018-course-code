import matplotlib.pyplot as plt
import sys

X = []
Y = []

with open("dataSet.txt", "r") as op:
    point = op.readline()
    while point:
        p = point.split(" ")
        X.append(float(p[0]))
        Y.append(float(p[1]))
        point = op.readline()

resX = []
resY = []

with open("dataRes.txt", "r") as op:
    point = op.readline()
    startX = float(point.split(" ")[0])
    startY = float(point.split(" ")[1])
    while point:
        p = point.split(" ")
        resX.append(float(p[0]))
        resY.append(float(p[1]))
        point = op.readline()
resX.append(startX)
resY.append(startY)

plt.figure(figsize=(8,8))
plt.xlim((0,100))
plt.ylim((0,100))
plt.scatter(X, Y, color='g')
plt.scatter(resX, resY, color="r")
plt.plot(resX, resY, color='r', linewidth=2.0)

plt.show()

from pulp import *
import sys

#if __name__ == '__main__':
arg = sys.argv[1]
sz = int(arg)

prob = LpProblem("SetCover", LpMinimize)

#sz = 1000


for i in range(1,sz+1,1):
    exec('x%s=LpVariable("x%s",0,1,LpContinuous,[])'%(i,i))

execstring = "["
for i in range(1,sz,1):
    execstring += "x%s,"%(i)
execstring += "x%s]"%(sz)
#print(execstring)
exec('X = %s'%(execstring))

res = 0

for i in range(1,sz+1,1):
    res += X[i-1]

#print(res)
prob += res, "obj" 

xs = []
for i in range(1,sz+1,1):
    xs.append([])
    for j in range(1,sz+1,1):
        xs[i-1].append(0)
index = -1
with open("input.txt","r") as op:
    line = op.readline()
    while line:
        index = index + 1
        nums = line.replace("\n","").split(" ")
        for k in nums:
            if k != "":
                xs[index][int(k)-1] = 1
        line = op.readline()
for i in range(1, sz+1,1):
    execstring = ""
    for j in range(1,sz+1,1):
        if xs[i-1][j-1] == 1:
            execstring += "x%s+"%(j)
    execstring = execstring[0:len(execstring)-1]
    if execstring == "":
        continue
    execstring += ">=1"
    #print(execstring)
    exec('prob += %s'%(execstring))

prob.solve()
#print("Status:", LpStatus[prob.status])
#for v in prob.variables():
#    print(v.name," = ", v.varValue)
#print("objective = ", value(prob.objective))

with open("output.txt", "w") as op:
    for i in range(1,sz+1,1):
        exec('op.write(str(x%s.varValue))'%(i))
        op.write("\n")
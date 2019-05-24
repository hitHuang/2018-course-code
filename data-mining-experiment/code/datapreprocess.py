f = open("dataset.txt", "r")
p = open("data.txt","w")
cnt = 0
while 1:
    line = f.readline()
    if not line:
        break
    line = line.replace(",", " ").replace("vhigh", "4").replace("high", "3").replace("med","2").replace("low","1").replace("5more","5").replace(" more"," 6").replace("small","1").replace("big","3")
    line = line.replace("vgood","4").replace("good","3").replace("unacc","1").replace("acc","2")
    p.write(line)
    cnt = cnt + 1
f.close()
p.close()
print (cnt)

import os

a = open("result.log")
s = "";
for i in a:
    s += i
a.close()

os.system('ls > result.log')
a = open("result.log")
for i in a:
    s += i
a.close()

os.system('ls > result.log')
a = open("result.log")
for i in a:
    s += i
a.close()

a = open("result.log", "w")
a.write(s)
a.close()

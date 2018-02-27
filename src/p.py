f = open("aaa")
ff = []
for i in f:
    ff.append(i)

um = []
dois = []
for i in ff:
    l = i.split(" / ")
    um.append(l[0])
    dois.append(l[1][:len(l[1]) - 1])
print(um)
print(dois)
for i in um:
    if i in dois:
        dois.remove(i)
    else:
        print("NAO ENCONTROU", i)
        break

print(dois)

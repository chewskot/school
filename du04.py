n = int(input())
n+=1
sito = [True]*n
for i in range(2,n):
    if sito[i]:
        for j in range(i*i,n,i):
            sito[j] = False


prvocisla = 0
for i in range(2,n):
    if sito[i]:
        prvocisla +=1
print(prvocisla)

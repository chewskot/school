class Reader:
    def __init__(self):
        self.line = []
    def read_int(self):
        while self.line == []:
            self.line = input().split()
        num = int(self.line[0])
        del self.line[0]
        return num
    def binary_search(self,list, n):  
        low = 0  
        high = len(list) - 1  
        mid = 0  
        while low <= high:  
            mid = (high + low) // 2   
            if list[mid] < n:  
                low = mid + 1  
            elif list[mid] > n:  
                high = mid - 1  
            else:
                while list[mid-1] == list[mid] and mid>0:
                    mid = mid-1
                return mid
        return -1
reader = Reader()
N = reader.read_int()
K = reader.read_int()
cisla = [0]*N
cisla_K = [0]*K
vypis = [0]*K
for j in range(N):
    cisla[j] = reader.read_int()
for i in range(K):
    cisla_K[i] = reader.read_int()
for l in range(K):
    vypis[l] = reader.binary_search(cisla, cisla_K[l])
for a in range(len(vypis)):
    if(a == len(vypis)):
            print(vypis[a]+1)
    else:
        print(vypis[a]+1, end = " ")



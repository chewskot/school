zavorky = ["(", ")"]
n = int(input())
vysledky = [0]*2*n
def zavorky_tvorba(k, pocet):
    if k < n*2:
        for i in zavorky:
            if pocet == n:
                if i == "(":
                    continue
                elif i == ")":
                    pocet=pocet -1
            elif 0<=pocet<n:
                if i == "(":
                    pocet = pocet+1
                elif i == ")":
                    pocet=pocet -1
            
            if pocet <0:
                return None
            vysledky[k] = i
            zavorky_tvorba(k+1, pocet)
            pocet = pocet-1
    elif k == n*2:
        if pocet != 0:
            return None
        else:
            print("".join(vysledky))

zavorky_tvorba(0, 0)
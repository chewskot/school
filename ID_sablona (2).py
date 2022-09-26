class Prvek:
    def __init__(self, x, dalsi):
        self.x = x
        self.dalsi = dalsi

def VytiskniLSS( p ):
    print( "LSS:", end=" " )
    while p!=None:
        print( p.x, end=" " )
        p = p.dalsi
    print(".")

def NactiLSS():
    """cte cisla z radku, dokud nenacte prazdny radek"""
    prvni = None
    posledni = None
    r = input()
    while r!="":
        radek = r.split()
        if len(radek)==0: # protoze ten test r!="" v RCDX neukoncil cyklus!
            break
        for s in radek:
            p = Prvek(int(s),None)
            if prvni==None:
                prvni = p
            else:
                posledni.dalsi = p
            posledni = p
        r = input()
    return prvni

#################################################
import sys
sys.setrecursionlimit(1500)
def IntersectionDestruct(a,b):
    """ destruktivni prunik dvou usporadanych seznamu
    * nevytvari zadne nove prvky, vysledny seznam bude poskladany z prvku puvodnich seznamu,
    * vysledek je MNOZINA, takze se hodnoty neopakuji """
    
    if b == None:
        
        return None
    
    elif a == None:
        
        return None
    
    if a.dalsi != None:
        
        while a.x == a.dalsi.x:
            a = a.dalsi
            
    if b.dalsi != None:
        
        while b.x == b.dalsi.x:
            b = b.dalsi
            
    while a.x < b.x:
        
        if a.dalsi != None:
            a = a.dalsi
            
    while b.x <= a.x:
        
        if b.x == a.x:
            a.dalsi = IntersectionDestruct(a.dalsi,b.dalsi)
            break
        
        if b.dalsi != None:
            
            while b.dalsi.x > a.x:
                
                if a.dalsi != None:
                    a = a.dalsi
                else:
                    return None
        else:
            return None
        b = b.dalsi    

    return a

#################################################

VytiskniLSS( IntersectionDestruct( NactiLSS(), NactiLSS() ) )

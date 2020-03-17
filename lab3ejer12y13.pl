construir(P):- P = 3 * x ** 3 + 2 * x ** 2 - 1.

monomio(M):- integer(M).
monomio(C * x):- integer(C).
monomio(x ** N):- integer(N).
monomio(C * x ** N):- integer(C), integer(N).

polinomio(P):- monomio(P).
polinomio(P1 + P2):- polinomio(P1), monomio(P2).
polinomio(P1 - P2):- polinomio(P1), monomio(P2).



eval(P, _, R):- integer(P), R is P.
eval(P, V, R):- P = C * x, integer(C), R is C * V.
eval(P, V, R):- P = x ** N, integer(N), R is V ** N.
eval(P, V, R):- P = C * x ** N, integer(C), integer(N),
                R is C * V ** N.
                
eval(P, V, R):- P = P1 + P2, eval(P1, V, R1), 
                eval(P2, V, R2), R is R1 + R2.
           
eval(P, V, R):- P = P1 - P2, eval(P1, V, R1), 
                eval(P2, V, R2), R is R1 - R2.
                


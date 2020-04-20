
tiempo(G):- T1 is cputime, G, T2 is cputime, T is T2 - T1, write(T).

suma(A, B, C):- C is A + B.

invertir([], []):-!.
invertir(L, I):- L = [H|T], invertir(T, I1), append(I1, [H], I).

invertir2(L, I):- invertir2ac(L, [], I).
invertir2ac([], A, I):- !, I = A.
invertir2ac(L, A, I):- L = [H|T], R = [H|A], invertir2ac(T, R, I).

myLength([], 0):- !.
myLength(L, N):- L = [_|T], myLength(T, N2), N is 1 + N2.

myLength2(L, N):- myLength2ac(L, 0, N).
myLength2ac([], A, N):- !, N = A.
myLength2ac(L, A, N):- L = [_|T], Z is A + 1, myLength2ac(T, Z, N).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% add(X, L, R)
% Añade X a la lista (al final) si X no esta en la lista

% Si X es miembro de la lista L entonces R = L, 
% sino L1 es igual a la lisa [X | L];
% add(a, [a,b,c] ,X) -> [a,b,c]

add(X, [], [X]):- !.
add(X, L, R):- L = [H|_], H = X, !, R = L.
add(X, L, R):- L = [H|T], add(X, T, R1), append([H], R1, R). 

add2(X, L, R):- inlista(X, L), !, R = L.
add2(X, L, R):- not(inlista(X, L)) , R = [X|L].


inlista(X, L):- L = [H|_], H = X, !.
inlista(X, [_|T]):- inlista(X, T).


diferente(X, Y):- X \= Y, !, true.
diferente(X, Y):- X = Y, false.



cubo :- repeat, write("Siguiente numero: "), read(X), Y is X**3, write(" resultado = "), write(Y), nl, false.








%         10
%    5            20
% 3    8     14      26
%2 4  7 9  12  15  23  

%nil | hoja(X) | nodo(X, A, B)

%nodo(20, nodo(14, hoja(12), hoja(15)), nodo(26, hoja(23), nil))

% es_arbol(X)
% devuelve true si X es un arbol

es_arbol(nil):- !.
es_arbol(hoja(_)):- !.
es_arbol(nodo(_, A, B)) :- es_arbol(A), es_arbol(B).

% peso(A, P)
% Unifica P con el peso del arbol A

peso(A, P):- es_arbol(A), A = nil, !, P is 0.
peso(A, P):- es_arbol(A), A = hoja(_), !, P is 1.
peso(A, P):- es_arbol(A), A = nodo(_, A1, A2), peso(A1, P1), peso(A2, P2), P is P1 + P2 + 1.

% altura(A, P)
% Unifica P con la altura del arbol A

altura(A, P):- es_arbol(A), A = nil, !, P is 1.
altura(A, P):- es_arbol(A), A = hoja(_), !, P is 1.
altura(A, P):- es_arbol(A), A = nodo(_, A1, A2), altura(A1, P1), altura(A2, P2), max(P1, P2, PM), P is PM + 1.



max(A, B, A):- A >= B, !.
max(A, B, B):- A < B. 

% frontera(A, F)
% Unifica F con la frontera del arbol A
frontera(A, F):- es_arbol(A), A = nil, !, F = [].
frontera(A, F):- es_arbol(A), A = hoja(X), !, F = [X].
frontera(A, F):- es_arbol(A), A = nodo(_, A1, A2), frontera(A1, F1), frontera(A2, F2), append(F1, F2, F).

% inorder(A, F)
% Unifica F con la lista de nodos resultado de realizar un inorder traversal

inorder(A, F):- es_arbol(A), A = nil, !, F = [].
inorder(A, F):- es_arbol(A), A = hoja(X), !, F = [X].
inorder(A, F):- es_arbol(A), A = nodo(X, A1, A2), inorder(A1, F1), inorder(A2, F2), 
                            append(F1, [X], F3), append(F3, F2, F).
                            

% nil | hoja(X) | nodo(X, [A1, A2... An])

%               20
%      3            25            80
%                            50      15     0
%                          2    3   
%nodo(20, [hoja(3), nil, hoja(25), nodo(80, [nodo(50, [hoja(2), hoja(3)]), hoja(15), hoja(0)])])

es_arbol2(nil):- !.
es_arbol2(hoja(_)):- !.
es_arbol2(nodo(_, L)):- es_arbol2_hijos(L).
es_arbol2_hijos([]):- !.
es_arbol2_hijos([H|T]):- es_arbol2(H), es_arbol2_hijos(T).


peso2(A, P):- A = nil, !, P is 0.
peso2(A, P):- A = hoja(_), !, P is 1.   
peso2(A, P):- A = nodo(_, L), peso2_hijos(L, PL), P is PL + 1.

peso2_hijos([], 0):- !.
peso2_hijos(H, P) :- H = [H1|T1], peso2(H1, P1), peso2_hijos(T1, P2), P is P1 + P2.


frontera2(A, F):- A = nil, !, F = [].
frontera2(A, F):- A = hoja(X), !, F = [X].
frontera2(A, F):- A = nodo(_, L), frontera2_hijos(L, F2), F = F2.

frontera2_hijos(L, F2):- L = [], !, F2 = [].
frontera2_hijos(L, F2):- L = [H|T], frontera2(H, F3), frontera2_hijos(T, F4), append(F3, F4, F2).

construir(X):- X = [98,45,38,69,10,69,20,12080,13,69,1,2,3,2,1,55,80,56,100]. 

% partir(L, L1, L2)
% Nos devuelve la lista L dividida en dos listas L1 y L2
% L1 contiene los elementos menores o iguales que el primero de L
% L2 contiene los elementos mayores que el primero de L
% El primero elemento de L no esta contenido en ninguna de las 2
% L1 y L2 no tienen por qué estar ordenadas
partir([], [], []).
partir(L, L1, L2):- L = [H|T], partir(T, H, L1, L2).
partir(L, N, L1, L2):- L = [H|T], H > N, L2 = [H|T2], partir(T, N, L1, T2).
partir(L, N, L1, L2):- L = [H|T], H =< N, L1 = [H|T1], partir(T, N, T1, L2).
partir([], _, [], []).


quicksort([], []).
quicksort([H|T], OL):- partir([H|T], L1, L2),quicksort(L1, OL1), quicksort(L2, OL2), 
                        OL3 = [H|OL2], append(OL1, OL3, OL).



mergesort([], []):-!.
mergesort([X], [X]):- !.
mergesort(L, OL):- partir2(L, L1, L2), mergesort(L1, OL1), mergesort(L2, OL2), merge(OL1, OL2, OL).


partir2([], [], []):-!.
partir2(L, L1, L2):- length(L, N), M is N // 2, append(L1, L2, L), length(L1, M), !. 

merge([], [], []):-!.
merge([], L2, L2):-!.
merge(L1, [], L1):-!. 
merge(L1, L2, L):- L1 = [H1|T1], L2 = [H2|_], H1 =< H2, !, L = [H1|T3], merge(T1, L2, T3).
merge(L1, L2, L):- L1 = [H1|_], L2 = [H2|T2], H1 > H2, L = [H2|T3], merge(L1, T2, T3).


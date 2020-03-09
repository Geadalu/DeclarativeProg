%Ejercicio 9.
%Defina un predicado partir(L, L1, L2) que divida la lista L 
%en dos partes L1 y L2, tales que los elementos de L1 son 
%menores o iguales que un cierto elemento N perteneciente a L y los de L2 
%son mayores que ese elemento N. El elemento N seleccionado no se incluye en 
%las listas partidas L1 y L2.

%partir(L, L1, L2):- L = [H|T], N = H, sacar(T, N, L1, L2).
%sacar(T, N, L1, L2):- T = [HT|TT], Aux = HT, HT > N, append(HT, L2, L3), sacar(TT, N, L1, L3).
%sacar(T, N, L1, L2):- T = [HT|TT], Aux = HT, HT < N, append(HT, L2, L3), sacar(TT, N, L1, L3).

%partir(L, L1, L2):- L = [H|T], N = H, sacar(T, N, L1, L2).
%sacar(T, N, [], []):- L1 = [], L2 = [].
%sacar(T, N, L11, L22):- T = [HT|TT], HT > N, L2 = [HT|L22], sacar(TT, N, L1, L2).
%sacar(T, N, L11, L22):- T = [HT|TT], HT < N, L1 = [HT|L11], sacar(TT, N, L1, L2).

partir([], [], []).
partir([X|L], L1, L2):- partir(L, L1, L2, X).
partir([], [], [], N).
partir([H|T], [H|T1], L2, N):- H =< N, partir(T, T1, L2, N).
partir([H|T], L1, [H|T2], N):- H > N, partir(T, L1, T2, N).
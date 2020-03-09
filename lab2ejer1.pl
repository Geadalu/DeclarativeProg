sustituir(X, Y, L1, L2):- L1 = [H|T], H = X, L2 = [Y|T2], sustituir(X, Y, T, T2).
sustituir(X, Y, L1, L2):- L1 = [H|T], H \= X, sustituir(X, Y, T, L3), L2 = [H|L3].
sustituir(_, _, L1, L2):- L1 = [], L2 = [].
sustituir(_, _, [], []):- !.
sustituir(X, Y, [H|T], [Y|T2]):- H = X, !, sustituir(X, Y, T, T2).
sustituir(X, Y, [H|T], [H|T2]):- H \= X, sustituir(X, Y, T, T2).

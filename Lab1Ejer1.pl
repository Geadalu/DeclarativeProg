hombre(teraj).
hombre(abraham).
hombre(najor).
hombre(haran).
hombre(lot).
hombre(batuel).
hombre(ismael).
hombre(laban).
hombre(isaac).
hombre(esau).
hombre(jacob).

mujer(sara).
mujer(melca).
mujer(jesca).
mujer(agar).
mujer(rebeca).

esclava(agar).

padre(teraj, abraham).
padre(teraj, najor).
padre(teraj, haran).
padre(teraj, sara).
padre(haran, lot).
padre(haran, melca).
padre(haran, jesca).
padre(najor, batuel).
padre(batuel, rebeca).
padre(batuel, laban).
padre(abraham,ismael).
padre(abraham, isaac).
padre(isaac, esau).
padre(isaac, jacob).

madre(agar, ismael).
madre(sara, isaac).
madre(melca, batuel).
madre(rebeca, esau).
madre(rebeca, jacob).

casado(abraham, sara).
casado(najor, melca).
casado(isaac, rebeca).

ascendiente_directo(X, Y) :- (padre(X, Y); madre(X, Y)).
ascendiente(X, Z) :- ascendiente_directo(X, Z).
ascendiente(X, Z) :- ascendiente_directo(X, Y), ascendiente(Y, Z).

descendiente_directo(X, Y) :- (hijo(X, Y); hija(X, Y)).
descendiente(X, Z) :- descendiente_directo(X, Z).
descendiente(X, Z) :- descendiente_directo(X, Y), descendiente(Y, Z).

hijo(X,Y) :- hombre(X), ascendiente_directo(Y,X).
hija(X,Y) :- mujer(X), ascendiente_directo(Y,X).

abuelo(X, Y) :- hombre(X), ascendiente_directo(X, Z), ascendiente_directo(Z, Y). 

hermano(X, Y) :- ascendiente_directo(Z, X), ascendiente_directo(Z, Y).

tio(X, Y) :- hermano(X, Z), ascendiente_directo(Z, Y).

sobrino(X, Y) :- hermano(X, Z), descendiente_directo(Z, Y).

incesto(X, Y) :- (descendiente(X, Y) ; ascendiente(X, Y)), casado(X, Y).
































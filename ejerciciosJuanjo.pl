familia(persona(antonio, foix, fecha(7, febrero, 1950), trabajo(renfe, 1200)),
persona(maria, lopez, fecha(17, enero, 1952), trabajo(sus_labores, 0)),
[persona(patricia, foix, fecha(10, junio, 1970), trabajo(estudiante, 0)),
persona(juan, foix, fecha(30, mayo, 1972), trabajo(estudiante,0))] ).

familia( persona(manuel, monterde, fecha(15, marzo, 1934), trabajo(profesor, 2000)),
persona(pilar, gonzalez, fecha(9, julio, 1940), trabajo(maestra, 1900)),
[ persona(manolo, monterde, fecha(10, febrero, 1964), trabajo(arquitecto, 5000)),
persona(javier, monterde, fecha(24, noviembre, 1968), trabajo(estudiante, 0)) ] ).

familia( persona(jose, benitez, fecha(3, septiembre, 1958), trabajo(profesor, 2000)),
persona(aurora, carvajal, fecha(29, agosto, 1972), trabajo(maestra, 1900)),
[ persona(jorge, benitez, fecha(6, noviembre, 1997), trabajo(desocupado, 0))] ).

familia( persona(jacinto, gil, fecha(7, junio, 1958), trabajo(minero, 1850)),
persona(guillermina, diaz, fecha(12, enero, 1957), trabajo(sus_labores, 0)),
[ persona(carla, gil, fecha(1, agosto, 1958), trabajo(oficinista, 1500)),
persona(amalia, gil, fecha(6, abril, 1962), trabajo(deliniante, 1900)), 
persona(irene, gil, fecha(3, mayo, 1970), trabajo(estudiante, 0)) ] ).

familia( persona(ismael, ortega, fecha(7, junio, 1966), trabajo(carpintero, 2350)),
persona(salvadora, diaz, fecha(12, enero, 1968), trabajo(sus_labores, 0)),
[persona(carla2, gil, fecha(1, agosto, 1958), trabajo(oficinista, 1500)),
persona(amalia2, gil, fecha(6, abril, 1962), trabajo(deliniante, 1900)), 
persona(irene2, gil, fecha(3, mayo, 1970), trabajo(estudiante, 0)),
persona(carla3, gil, fecha(1, agosto, 1958), trabajo(oficinista, 1500)),
persona(amalia3, gil, fecha(6, abril, 1962), trabajo(deliniante, 1900)), 
persona(irene3, gil, fecha(3, mayo, 1970), trabajo(estudiante, 0)) ] ).

familia( persona(pedro, ramirez, fecha(7, junio, 1966), trabajo(en_paro,0)),
persona(teresa, fuentes, fecha(12, enero, 1968), trabajo(administrativa, 1250)),
[] ).

familia( persona(anduin, wrynn, fecha(7, junio, 1966), trabajo('Rey de Ventormenta',0)),
persona(gwendolyn, wrynn, fecha(12, enero, 1968), trabajo(administrativa, 1250)),
[] ).

padre(P) :- familia(P, _, _).

madre(M) :- familia(_, M, _).

hijo(H) :- familia(_, _, [H | _]).


existe(P) :- familia(P, _, _).
existe(P) :- familia(_, P, _).
existe(P) :- familia(_, _, L), existe_lista(L, P).

% existe_lista(L, P)
% Te dice si en L existe la persona P
existe_lista(L, P) :- L = [H|_], P = H.
existe_lista(L, P) :- L = [H|T], existe_lista(T, P).




% sustituir(X, Y, L1, L2)
% Hay que coger la lista L1, y cambiar X por Y, y devolverlo en L2

sustituir(X, Y, L1, L2):- L1 = [], L2 = [].
sustituir(X, Y, L1, L2):- L1 = [H|T], X\=H, sustituir(X, Y, T, L3), L2 = [H|L3].
sustituir(X, Y, L1, L2):- L1 = [H|T], H = X, L2 = [Y|T2], sustituir(X, Y, T, T2).


% aplanar(L1, L2)
% L1 puede ser una lista de listas de cualquier anidamiento, y hay que devolver una lista de un solo nivel
% Ejemplo: [[a,b],c[[[d]], e] -> [a,b,c,d,e]


aplanar(L1, L2):- L1 = [], L2 = [].
aplanar(L1, L2):- L1 = [H|T], not(atomic(H)), aplanar(H, H2), aplanar(T, T2), append(H2, T2, L2).
aplanar(L1, L2):- L1 = [H|T], atomic(H), aplanar(T, L3), L2 = [H|L3].



descomponer(N, A, B):- between(0, N, A), between(0, N, B), A mod 2 =:= 0, B mod 2 =:= 0, N is A + B.

numBrandreth(N, C):- between(32, 99, N), C is N * N, C1 is C // 100, C2 is C mod 100, N is C1 + C2. 



igualesElemOrden(L1, L2):- L1 = [], L2 = [].
igualesElemOrden(L1, L2):- L1 = [H|T], L2 = [H|T2], igualesElemOrden(T, T2).



igualesElem(L1,L2):- length(L1,N), length(L2,N), ie(L1,L2).
ie([],[]).
ie([X|Xs],[X|Ys]):- !, ie(Xs,Ys). 
ie([X|Xs],[Y|Ys]):- eliminar(X,Ys,YYs), eliminar(Y,Xs,XXs), ie(XXs,YYs). 

eliminar(_,[],[]).
eliminar(X,[X|Ys],Ys):- !.
eliminar(X,[Y|Ys],[Y|Zs]):- eliminar(X,Ys,Zs).

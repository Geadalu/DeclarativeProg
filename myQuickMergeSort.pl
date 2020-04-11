partir([], [], []).
partir(L, L1, L2):- L = [H|T], partir(T, H, L1, L2).
partir(L, N, L1, L2):- L = [H|T], H > N, L2 = [H|T2], partir(T, N, L1, T2).
partir(L, N, L1, L2):- L = [H|T], H =< N, L1 = [H|T1], partir(T, N, T1, L2).
partir([], _, [], []).


quicksort(L, LO) :- L = [H|T], partir(L, L1, L2), quicksort(L1, LO1), quicksort(L2, LO2),  LO3 = [H|LO2], append(LO1, LO3, LO).
quicksort([], []).

mergesort(L, LO) :- L = [H|T], partir2(L, L1, L2).

partir2(
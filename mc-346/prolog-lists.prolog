maior([A], A).
maior([A,B|R], M) :- A>=B, maior([A|R], M).
maior([A,B|R], M) :- A<B, maior([B|R], M).

ultimo([A], A).
ultimo([_|R], U) :- ultimo(R, U).

semultimo([_], []).
semultimo([A|R], U) :- semultimo(R, X), U=[A|X].

impares([], []).
impares([A], [A]).
impares([A,_|R], I) :- impares(R, X), I=[A|X].

positivos([], []).
positivos([A|R], P) :- A>=0, positivos(R, X), P=[A|X].
positivos([A|R], P) :- A<0, positivos(R, P).

somapos([], 0).
somapos([A|R], P) :- A>=0, somapos(R, X), P is A+X.
somapos([A|R], P) :- A<0, somapos(R, P).

crescente([]).
crescente([_]).
crescente([A,B|R]) :- B>A, crescente([B|R]).

shift_right([], []).
shift_right(L, P) :- ultimo(L, U), semultimo(L, S), P=[U|S].

shift_left([], []).
shift_left([A|R], S) :- append(R, [A], S).

inverte([], []).
inverte([A|R], I) :- inverte(R, X), append(X, [A], I).


conta([],_, 0).
conta([I|R], I, C) :- conta(R, I, X), C is X+1.
conta([A|R], I, C) :- A =\= I, conta(R, I, C).

remove([], _, []).
remove([I|R], I, L) :- remove(R, I, L).
remove([A|R], I, L) :- A =\= I, remove(R, I, X), L=[A|X].

troca([], _, _, []).
troca([I|R], I, T, L) :- troca(R, I, T, X), L=[T|X].
troca([A|R], I, T, L) :- A =\= I, troca(R, I, T, X), L=[A|X].



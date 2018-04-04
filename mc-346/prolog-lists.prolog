maior([A], A).
maior([A,B|R], M) :- A>=B, maior([A|R], M).
maior([A,B|R], M) :- A<B, maior([B|R], M).

ultimo([A], A).
ultimo([_|R], U) :- ultimo(R, U).

semultimo([_], []).
semultimo([A|R], [A|X]) :- semultimo(R, X).

impares([], []).
impares([A], [A]).
impares([A,_|R], [A|X]) :- impares(R, X).

positivos([], []).
positivos([A|R], [A|X]) :- A>=0, positivos(R, X).
positivos([A|R], P) :- A<0, positivos(R, P).

somapos([], 0).
somapos([A|R], P) :- A>=0, somapos(R, X), P is A+X.
somapos([A|R], P) :- A<0, somapos(R, P).

crescente([]).
crescente([_]).
crescente([A,B|R]) :- B>A, crescente([B|R]).

shift_right([], []).
shift_right(L, [U|S]) :- ultimo(L, U), semultimo(L, S).

shift_left([], []).
shift_left([A|R], S) :- append(R, [A], S).

inverte([], []).
inverte([A|R], I) :- inverte(R, X), append(X, [A], I).

conta([],_, 0).
conta([I|R], I, C) :- conta(R, I, X), C is X+1.
conta([A|R], I, C) :- A =\= I, conta(R, I, C).

remove([], _, []).
remove([I|R], I, L) :- remove(R, I, L).
remove([A|R], I, [A|X]) :- A =\= I, remove(R, I, X).

troca([], _, _, []).
troca([I|R], I, T, [T|X]) :- troca(R, I, T, X).
troca([A|R], I, T, [A|X]) :- A =\= I, troca(R, I, T, X).

tamanho([], 0).
tamanho([_|R], T) :- tamanho(R, X), T is X+1.

pos(L, I, P) :- append(X, [I|_], L), tamanho(X, P).
pos([], _, -1).



primo(A, B) :- precursor(X, A), precursor(Y, B), precursor(P, X), precursor(P, Y).
irmaos_total(A, B) :- pai(P, A), pai(P, B), mae(P, A), mae(P, B).
meio_irmao(A, B) :- pai(P, A), pai(P, B), \+ (mae(P, A), mae(P, B)).

erro_1(A) :- pai(A), fem(A).
erro_1(A) :- mae(A), masc(A).

erro_2(A) :- pai(A, _), mae(A, _).
erro_3(A) :- fem(A), masc(A).



depois_2010(F) :- filme(F, A), A > 2010.
atores_e_diretores(A) :- ator(_,_,A), diretor(_, A).
atores_atrizes_diretores(A) :- atores_e_diretores(A) ; (atriz(_,_,A),diretor(_,A)).
atriz_autodiretora(A) :- atriz(F,_,A),diretor(F,A).
coestrelas(A,B) :- atriz(F,_,A),ator(F,_,B).
si_proprio(A) :- ator(_, A, A) ; atriz(_, A, A).

antecessor_masc(A, B) :- masc(B), pai(A, B).

antecessor_masc(A, B) :- masc(B), pai(A, X), antecessor_masc(X, B).



antecessor_fem(A, B) :- mae(A, B).

antecessor_fem(A, B) :- mae(A, X), antecessor_fem(X, B).


count_nodes(vazia, 0).
count_nodes(arv(_, E, D), N) :- count_nodes(E, NE), count_nodes(D, ND), N is NE + ND + 1.

depth(vazia, 0).
depth(arv(_, E, D), R) :- depth(E, RE), depth(D, RD), R is max(RE, RD) + 1.

infix(vazia, []).
infix(arv(Node, E, D), L) :- infix(E, LE), infix(D, LD), concat(LE, [Node], Aux), concat(Aux, LD, L). 

prefix(vazia, []).
prefix(arv(Node, E, D), L) :- prefix(E, LE), prefix(D, LD), concat([Node], LE, Aux), concat(Aux, LD, L).

abb(vazia).
abb(arv(N, arv(E, EAE, EAD), arv(D, DAE, DAD))) :- 
    									   E < N, 
    									   N < D,
    									   extreme_left(arv(E, EAE, EAD), EL),
    									   extreme_right(arv(D, DAE, DAD), ER),
    									   EL < N,
    									   N < ER,
    								  	   abb(E), abb(D).

extreme_right(arv(N, _, vazia), N).
extreme_right(arv(_, _, arv(N, E, D)), R) :- extreme_right(arv(N, E, D), R).
              
extreme_left(arv(N, vazia, _), N).
extreme_left(arv(_, arv(N, E, D), _), R) :- extreme_left(arv(N, E, D), R).

exists_abb(arv(I, _, _), I).
exists_abb(arv(N, E, _), I) :- I < N, exists_abb(E, I).
exists_abb(arv(N, _, D), I) :- I > N, exists_abb(D, I).

insert_abb(vazia, I, arv(I, vazia, vazia)).
insert_abb(arv(I, E, D), I, arv(I, E, D)).
insert_abb(arv(N, E, D), I, arv(N, AE, D)) :- I < N, insert_abb(E, I, AE).
insert_abb(arv(N, E, D), I, arv(N, E, AD)) :- I > N, insert_abb(D, I, AD).

avl(vazia).
avl(arv(N, E, D)) :- abb(arv(N, E, D)), avl_aux(arv(N, E, D)).

avl_aux(vazia).
avl_aux(arv(_, E, D)) :- avl_aux(E), avl_aux(D), depth(E, DE), depth(D, DD), L is abs(DE - DD), L < 2.
    					 

remove_abb(vazia, _, vazia).
remove_abb(arv(N, E, D), I, arv(N, AE, D)) :- I < N, remove_abb(E, I, AE).
remove_abb(arv(N, E, D), I, arv(N, E, AD)) :- I > N, remove_abb(D, I, AD).

remove_abb(arv(I, vazia, vazia), I, vazia).
remove_abb(arv(I, vazia, D), I, R) :- D =/= vazia,
    			  	      extreme_left(D, LED),
    				      remove_abb(D, LED, AD), 
    				      R = arv(LED, vazia, AD).

remove_abb(arv(I, E, vazia), I, R) :- E =/= vazia,
    				      extreme_right(E, LED),
    				      remove_abb(E, LED, AE), 
    				      R = arv(LED, AE, vazia).

remove_abb(arv(I, E, D), I, R) :- E =/= vazia, D =/= vazia,
                                  extreme_right(E, LED),
                                  remove_abb(E, LED, AE), 
                                  R = arv(LED, AE, D).

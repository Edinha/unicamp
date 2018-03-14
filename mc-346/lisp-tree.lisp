
; Conta os nos de uma arvore
(defun tree_node_count (tree)
   (if (null tree) 0
       (+ 1 (tree_node_count (first (rest tree))) (tree_node_count (first (rest (rest tree)))))
   )
)

(print (tree_node_count '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Infixa
(defun infix (tree)
    (if (null tree) '()
        (append (infix (first (rest tree))) (list (first tree)) (append (infix (first (rest (rest tree))))) )
    )
)

(print (infix '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Posfixa
(defun posfix (tree)
    (if (null tree) '()
        (append (list (first tree)) (posfix (first (rest tree))) (append (posfix (first (rest (rest tree))))) )
    )
)

(print (posfix '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Descobrir se eh arvore binaria de busca
(defun is_binary_tree (tree)
    (if (null tree) T
        (let* ((node (first tree))
               (esq (first (rest tree)))
               (dir (first (rest (rest tree))))
               (esq_node (first esq))
               (dir_node (first dir))
               (esq_binary (is_binary_tree esq))
               (dir_binary (is_binary_tree dir))  )
       
               (if esq_binary
                   (if dir_binary
                       (if (null esq_node) (if (null dir_node) T (< node dir_node))
                           (if (null dir_node) (< esq_node node) (and (< esq_node node) (< node dir_node)) )
                       )
                    NIL
                   )
                NIL
               )
         )
     )
)

(print (is_binary_tree '(5 () (8 (4 () (7 () ())) (9 () ())))))

; Achar elemento arvore de busca binaria
(defun find_tree (tree item)
    (if (null tree) NIL
        (let ((node (first tree))
              (esq (first (rest tree)))
              (dir (first (rest (rest tree))))
             )
             (if (= node item) T
                 (if (< node item) (find_tree dir item) (find_tree esq item))
             )
        )
    )
)

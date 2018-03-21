(defun trans (l)
   (if (null (first l)) '()
       (cons (mapcar #'first l) (trans (mapcar #'rest l)))
   )
)

(print (trans '((1 2 3 4) (5 6 7 8) (9 10 11 12))))


(DEFUN trans_epic (l)
    (apply #'mapcar #'list l)
)

(print (trans_epic '((1 2 3 4) (5 6 7 8) (9 10 11 12))))

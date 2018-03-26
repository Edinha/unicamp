(defun invert_help (l acc)
   (if (null l) acc
       (invert_help (rest l) (cons (first l) acc ) )
   )
)

(defun inv (l) (invert_help l '()) )



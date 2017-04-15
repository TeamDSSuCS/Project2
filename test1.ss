(define (list_sumr mylist)
  (if (list? mylist)
      (if (null? mylist)
	  0
	  (if (number? (car mylist))
	      (+ (car mylist) (list_sumr (cdr mylist)))
	      (list_sumr (cdr mylist))))
      'list_sumr requires a list argument'
      )
  )


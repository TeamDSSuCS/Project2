(define (arithmetic a b c)
	(if (not (= 0 b))
		(+ (/ (* a (- b c)) 2) (- (/ a b) 2 c))
		(+ (/ (* a (- b c)) 2) (- (/ a 4) 2 c))
		)
	)

(define (concat l1 l2)
	(if (null? l1)
		l2
		(cons (car l1) (concat (cdr l1) l2))
		)
	)

(define (listops1 sym ls1 ls2)
	(cons sym (concat ls1 ls2))
	)

(define (listops2 ls)
	(if (not (list? ls))
		'argument_must_be_a_list
		(caddr (cdddr ls))
		)
	)

(define (main)

	(display (arithmetic 5 7 9))
	(newline)
	(display (arithmetic 5 0 9))
	(newline)
	(display (listops1 5 (aa bb cc) '(1 3 5 7 11 13)))
	(newline)
	(display (listops2 (a b c (d e f c) h i j) ))
	(newline)
	(display (listops2 'a))
	(newline)
		)
	
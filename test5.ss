(define (twothirds L)
	(if (list? L)
		(if (< (length L) 3)
			L
			(cons (car L) (cons (cadr L) (twothirds (cdddr L))))
		)
		'()
	)
)

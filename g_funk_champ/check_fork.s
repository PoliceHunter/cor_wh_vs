.name       "Batman"
.comment    "This city needs me"

loop:
        sti r1, %:live, %1

live:	live %66
	fork %:live

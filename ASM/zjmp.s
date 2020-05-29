.name "zork"
.comment "I'M ALIIIIVE"

l2:		zjmp %:live
		and r1, %0, r1

live:	live %1
		zjmp %:live

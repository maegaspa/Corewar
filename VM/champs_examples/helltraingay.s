#by zaz, still not as good as rainbowdash though
#2013

.name		"helltrain"
.comment	"choo-choo, motherf*****s !"

entry:
	sti		r1, %:beegees_gen, %1
	sti		r1, %:beegees, %1
	sti		r1, %:cc_spawn, %1
	sti		r1, %:wall, %1
	sti		r1, %:cc4, %1
	sti		r1, %:cc4, %9
	sti		r1, %:cc4, %17
	sti		r1, %:cc4l, %1
	sti		r1, %:cc4ld, %2
	add		r8, r9, r3
	ld		%0, r16
	#fork	%:cc_spawn

wall_prep:
	ld		%0, r2
	ld		%0, r16

wall:
	live	%4902343
	st		r2, -24
	st		r2, -33
	st		r2, -42
	st		r2, -51
	and		565, %9, r2
	ldi		%251823, r2, r10
	ldi		1, r3, r2
	and		565, 455, r2
	st		r2, -186
	st		r2, -195
	st		r2, -204
	add		r8, r9, r3
	st		r2, -213
	or		r1, r8, r3
	st		r2, -222
	lld		%251, r2
	lld		%38651, r3
	st		r2, -474
	or		r10, r2, r9
	lldi	%251823, r2, r1
	lldi	1, r3, r10
	zjmp	%:wall

beegees_gen:
	live	%4239423
	#fork	%:beegees_gen
	ld		%0, r16

beegees:
	live	%3442302
	zjmp	%:beegees
	xor		r1, r2, r3

cc_spawn:
	live	%4320423
	zjmp	%3
	#fork	%:cc_spawn

cc4:
	live	%4329034
	#fork	%:cc3
	live	%3401123
	sub		r1, r9, r3
	sub		r8, r1, r1
	#fork	%:cc2
	xor		r1, r2, r3
	live	%4590543
	#fork	%:cc1
cc4ld:
	ld		%0, r2
	ld		%251883523, r3
	ld		%0, r16
cc4l:
	live	%4930423	
	ld		%0, r16
	zjmp	%:choochoo

cc2:
	live	%4342342
	#fork	%:wall_prep
	ld		%0, r16
	ld		%0, r16
	xor		r1, r2, r3
	zjmp	%:choochoo

cc3:
	live	%4239013
	#fork	%:cc4
	live	%4093282
	#fork	%:beegees_gen
	ld		%0, r16
	ld		%0, r16
	ld		%0, r16
	zjmp	%:choochoo

cc1:
	ld		%0, r16
	zjmp	%:choochoo

choochoo:
	st		r2, 15
	st		r3, -1
cc_live:
	live	%0

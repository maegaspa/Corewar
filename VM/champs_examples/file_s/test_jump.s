.name "st"
.comment "st"

#test pb p3
ld %1409352240, r1
st r1, 6
sub r1, r2, r3
#test pb p2
ld %1409361155, r2
st r2, 6
sub r1, r2, r3
#test pb p1
ld %1411711491, r3
st r3, 6
sub r1, r2, r3
#ADV 14 mamene
#ld %-1476328957, r5
#st r5, 6
#and r1, r2, r3
#ocp bon, mais 3e arg, que pasa
ld %-1744830464, r5
st r5, 6
lld %8, r2
#test ocp == 11 11 11 11
#ld %-16711165, r4
#st r4, 6
#sub r1, r2, r3
#test ocp chimique 00 .. ..
#ld %335610371, r5
#st r5, 6
#sub r1, r2, r3
#test ocp chimique .. 00 ..
#ld %1140916739, r6
#st r6, 6
#sub r1, r2, r3
#test ocp chimique .. .. 00
#ld %1342243331, r7
#st r7, 6
#sub r1, r2, r3

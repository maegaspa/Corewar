#deassembler par msa 1.8, made by joe
.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

	 fork	%:label00          		
	 ld	%-272,r3           		
	 live	%0                 		
	 fork	%:label01          		
	 ld	%-272,r3           		
	 fork	%:label02          		
	 ld	%0,r2              		
	 ld    %0,r4              		
	 zjmp  %:label03          		

label02: ld    %4,r2              		
	 ld    %0,r4              		
	 zjmp  %:label03          		

label01: ld    %-202,r3           		
	 fork  %:label04          		
	 ld    %0,r2              		
	 ld    %0,r4              		
	 zjmp  %:label05          		

label04: ld    %4,r2              		
	 ld    %0,r4              		
	 zjmp  %:label05          		

label00: ld    %400,r3            		
	 live  %0                 		
	 fork  %:label06          		
	 fork  %:label07          		
	 ld    %0,r2              		
	 ld    %0,r4              		
	 zjmp  %:label08          		

label07: ld    %4,r2              		
	 ld    %0,r4              		
	 zjmp  %:label08          		
label06: fork  %:label09          		
	 ld    %0,r4              		
	 zjmp  %:label10          		

label09: ld    %0,r4              		
	 zjmp  %:label11          		

label03: ldi   r2,%:label12,r6    		
	 ld    %0,r4              		
	 live  %1                 		

label12: sti   r6,r2,r3           		
	 zjmp  %-277              		

label08: ldi   r2,%:label13,r6    		
	 ld    %0,r4              		
	 live  %1                 		

label13: sti   r6,r2,r3           		
	 zjmp  %395               		

label05: ldi   r2,%:label14,r6    		
	 ld    %0,r4              		
	 live  %1                 		

label14: sti   r6,r2,r3           		
	 zjmp  %-207              		

label10: live  %1                 		
	 fork  %:label10          		
	 zjmp  %:label10          		

label11: live  %1                 		
	 fork  %:label11          		
	 zjmp  %:label11          		

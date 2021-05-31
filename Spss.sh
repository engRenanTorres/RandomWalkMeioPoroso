#!/bin/bash
#script para compilar mais rápido
#para torna-lo executavel chmod +x Sps.sh



PP=10
typeset -F 2 PPP
PPP=$(echo "scale=6; 1 / $PP" | bc -l)
echo "$PPP"
U=1


		while [ $U -gt "0" ]; do

			TAL=3 #valor de 4 tal=524288 6tal=786432 metade do raio

			sed -e "s/\#define TAL (int)1/\#define TAL (int)${TAL}/g" pss.c > pssap.c 
			cp pssap.c pss00.c

			sed -e "s/\#define n (int)100/\#define n (int)${U}/g" pss00.c > pssap.c
			cp pssap.c pss00.c

			sed -e "s/\#define pp (double)0.1/\#define pp (double)${PPP}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
		
			echo "insira r= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r=11111111/r=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
	
			echo "insira r2= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r2=11111111/r2=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
	
			echo "insira r3= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r3=11111111/r3=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c



       		 	gcc -o u${U}ps${PPP}T${TAL}.out pss00.c -Wall -O3 -lm 
			./u${U}ps${PPP}T${TAL}.out&
			rm pssap.c pss00.c

			TAL=5 #valor de 4 tal=524288 6tal=786432 metade do raio

			sed -e "s/\#define TAL (int)1/\#define TAL (int)${TAL}/g" pss.c > pssap.c 
			cp pssap.c pss00.c

			sed -e "s/\#define n (int)100/\#define n (int)${U}/g" pss00.c > pssap.c
			cp pssap.c pss00.c

			sed -e "s/\#define pp (double)0.1/\#define pp (double)${PPP}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
		
			echo "insira r= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r=11111111/r=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
	
			echo "insira r2= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r2=11111111/r2=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c
	
			echo "insira r3= para U=${U} PPP=${PPP} TAL=${TAL}"
			read Rand
			sed -e "s/r3=11111111/r3=${Rand}/g" pss00.c > pssap.c
			cp pssap.c pss00.c



       		 	gcc -o u${U}ps${PPP}T${TAL}.out pss00.c -Wall -O3 -lm 
			./u${U}ps${PPP}T${TAL}.out&
		        #rm pssap.c pss00.c



        		U=$(expr $U / 10)
			typeset -F 2 PPP
			PPP=$(echo "scale=6; ${PPP} / 10" | bc -l)
		done


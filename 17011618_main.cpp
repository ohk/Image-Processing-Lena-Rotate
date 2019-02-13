#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"

using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*)malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			resimdizi[i*N + j] = (short)resim[i][j];

	int resimadres = (int)resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
	case 0:
		exit(0);
	case 1:
		sagaDondur(N, resimadres);
		strcpy(sonek, "_sag.pgm");
		break;
	case 2:
		solaDondur(N, resimadres);
		strcpy(sonek, "_sol.pgm");
		break;
	default:
		strcpy(sonek, "_orj.pgm");
		break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}

	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {

		/*
		
		for(i=1;i<n;i++){
			 for(j=0;j<i;j++){
				tmp=array[i*n +j];
				array[i*n +j]=array[j*n +i];
				array[j*n +i] = tmp;           
			}
		}
		
		
		*/
		//i: SI j: DI
			MOV CX,n
			DEC CX
			MOV ESI,1
			XOR EDI,EDI

		L2: PUSH CX
			XOR EDI, EDI
			MOV CX, SI
			/*
			 *
			 * Ýlk adým AX registerine n'i atýyorum.
			 */
		L1: XOR EAX,EAX	
			MOV AX,n
			MUL ESI
			ADD EAX,EDI //i*n +j
			SHL EAX,1
			ADD EAX,resim
			MOV BX,WORD PTR [EAX]
			PUSH EAX

			XOR EAX,EAX
			MOV AX,n
			MUL EDI
			ADD EAX,ESI //j*n+i
			SHL EAX,1
			ADD EAX, resim
			XCHG BX,WORD PTR [EAX]

			POP EAX
			MOV WORD PTR [EAX],BX
			INC DI
			LOOP L1
			
			POP CX
			INC SI
			LOOP L2

			/*
			 for(i=0;i<n/2;i++){
				for(j=0;j<n;j++){
					tmp=array[j*n +i];
					array[j*n +i]=array[j*n + n-i-1];
					array[j*n + n-i-1] = tmp;           
				}
			 }
 			 */


			 MOV CX, n
			 SHR CX,1
			 DEC CX

			 XOR ESI,ESI
			 XOR EDI, EDI

		L3 : PUSH CX
			 XOR EDI, EDI
			 MOV CX, n
		
		L4 : XOR EAX, EAX
		     MOV AX, n
			 MUL EDI
			 ADD EAX, ESI //J*N + Ý
			 SHL EAX, 1
			 ADD EAX, resim
			 MOV BX, WORD PTR[EAX]
			 PUSH EAX

			 XOR EAX, EAX
			 MOV AX, n
			 MUL EDI
			 PUSH DI
			 XOR EDI,EDI
			 MOV DI,n
			 ADD EAX,EDI
			 POP DI
			 DEC EAX
			 SUB EAX, ESI //j*n-i-1+n
			 SHL EAX, 1
			 ADD EAX, resim
			 XCHG BX, WORD PTR[EAX]

			 POP EAX
			 MOV WORD PTR[EAX], BX
			 INC DI
			 LOOP L4

			 POP CX
			 INC SI
			 LOOP L3









	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {

		/*

		for(i=1;i<n;i++){
			 for(j=0;j<i;j++){
				tmp=array[i*n +j];
				array[i*n +j]=array[j*n +i];
				array[j*n +i] = tmp;
			}
		}


		*/
		//i: SI j: DI

	
		
			 


		MOV CX, n
		DEC CX
		MOV ESI, 1
		XOR EDI, EDI

   L2 : PUSH CX
	    XOR EDI, EDI
		MOV CX, SI

   L1 : XOR EAX, EAX
		MOV AX, n
		MUL ESI
		ADD EAX, EDI //i*n +j
		SHL EAX, 1
		ADD EAX, resim
		MOV BX, WORD PTR[EAX]
		PUSH EAX

		XOR EAX, EAX
		MOV AX, n
		MUL EDI
		ADD EAX, ESI //j*n+i
		SHL EAX, 1
		ADD EAX, resim
		XCHG BX, WORD PTR[EAX]

		POP EAX
		MOV WORD PTR[EAX], BX
		INC DI
		LOOP L1

		POP CX
		INC SI
		LOOP L2

		/*
		 for(i=0;i<n/2;i++){
			for(j=0;j<n;j++){
				tmp=array[j*n +i];
				array[j*n +i]=array[j*n + n-i-1];
				array[j*n + n-i-1] = tmp;
			}
		 }
		 */

		 //i: SI j: DI
		 MOV CX, n
		 SHR CX, 1
		 DEC CX

		 XOR ESI, ESI
		 XOR EDI, EDI

	L3 : PUSH CX
		 XOR EDI, EDI
		 MOV CX, n

	L4 : XOR EAX, EAX
		 MOV AX, n
		 MUL ESI
		 ADD EAX, EDI //i*n +j
		 SHL EAX, 1
		 ADD EAX, resim
		 MOV BX, WORD PTR[EAX]
		 PUSH EAX
		
		
		
		 XOR EAX, EAX
		 MOV AX, n
		 SUB EAX,ESI
		 DEC EAX
		 PUSH EDI
		 MOV DI,n
		 MUL EDI
		 POP EDI
		 ADD EAX,EDI
		 SHL EAX, 1
		 ADD EAX, resim
		 XCHG BX, WORD PTR[EAX]

		 POP EAX
		 MOV WORD PTR[EAX], BX
		 INC DI
		 LOOP L4

		 POP CX
		 INC SI
		 LOOP L3
		
					
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}
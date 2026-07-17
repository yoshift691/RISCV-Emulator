#include <stdio.h>
#include <stdint.h>

// TP 2/3 de IN330 -- exercices préparatoires
// LG et SM pour IN330, 2024

uint32_t extract_field(uint32_t w, int p, int l)
{
	// TODO : Extraire de w la série de bits à la position p de longueur l
	uint32_t ws=w>>p;
	uint32_t masque=(1<<l)-1;
	return ws&masque;

}

// Extension de signe d'un entier de n-bits (n > 1), i, vers 32 bits
int32_t sign_extend(uint32_t i, int n)
{
	int32_t igauche=i<<32-n;
	int32_t idroite=igauche>>32-n;
	return idroite;

}

int main(void)
{
	uint32_t w = 0x00b60633;
	uint32_t test=0xfff;
	printf("w[6..0] = %u\n", extract_field(w, 0, 7));
	printf("w[19..15] = %u\n", extract_field(w, 15, 5));
	printf("%x",sign_extend(test,12));
}

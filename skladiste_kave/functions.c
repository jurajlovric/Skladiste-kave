#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

static int brojKava = 0, i, j, br = 0;

int izbornik() {

	int opcija = 0;
	static KAVA* polje = NULL;

	printf("----------------------------------------------------------------------------------\n");
	printf("Dobrodosli u aplikaciju!\nOdabirom jednih od opcija program ce napraviti sljedece:\n");
	printf("' 1 ' Dodaj kavu\n");
	printf("' 2 ' Uredi postojeci proizvod\n");
	printf("' 3 ' Ispis kave\n");
	printf("' 4 ' Trazilica\n");
	printf("' 5 ' Sortiraj kavu po cijeni\n");
	printf("' 6 ' Brisanje proizvoda\n");
	printf("' 7 ' Izlaz iz programa\n");

	scanf("%d", &opcija);
	system("cls");
	

	switch (opcija) {
	case 1:
		ucitavanjeKave();
		if (brojKava == 0) {
			kreiranjeDat();
		}
		dodavanjeKave();
		break;
	case 2:
		prepravljanje();
		break;
	case 3:
		if (polje != NULL) {
			free(polje);
			polje = NULL;
		}
		polje = (KAVA*)ucitavanjeKave();
		ispisivanje(polje);
		break;
	case 4:
		while (opcija != 90) {
			opcija = izbornikSrch();
		}
		break;
	case 5:
		while (opcija != 91)
			opcija = izbornikSrt();
		break;
	case 6:
		if (polje == NULL)
			printf("Nema kave u skladistu.");
		else
			brisanjeKave(polje);
		break;
	case 7:
		izlaz(polje);
		return 101;
		break;
	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

izbornikSrch() {
	int opcija = 0;
	KAVA* polje = NULL;
	polje = (KAVA*)ucitavanjeKave();
	printf("Pretrazi po:\n");
	printf("\t' 1 ' Imenu Tvrtke\n");
	printf("\t' 2 ' Imenu proizvoda\n");
	printf("\t' 3 ' Cijeni\n");
	printf("\t' 4 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		SearchImeTvrtke(polje);
		break;
	case 2:
		SearchImeProizvoda(polje);
		break;
	case 3:
		SearchCijena(polje);
		break;
	case 4:
		return 90;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

int izbornikSrt() {
	int opcija = 0;
	KAVA* polje = NULL;
	polje = (KAVA*)ucitavanjeKave();
	printf("Sortiraj prema:\n");
	printf("\t' 1 ' Cijeni uzlazno\n");
	printf("\t' 2 ' Cijeni silazno\n");
	printf("\t' 3 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		selectionSortCijenaUzl(polje);
		break;
	case 2:
		selectionSortCijenaSil(polje);
		break;
	case 3:
		return 91;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("kava.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje");
	}
	fwrite(&brojKava, sizeof(int), 1, fp);
	fclose(fp);
}

void dodavanjeKave() {
	FILE* fp = NULL;
	fp = fopen("kava.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojKava, sizeof(int), 1, fp);
	printf("Trenutni broj kava: %d\n", brojKava);

	KAVA kave;
	kave.id = brojKava;
	br++;
	getchar();
	printf("Unesite ime tvrtke: ");
	scanf("%24[^\n]", kave.ime_tvrtke);
	getchar();
	printf("Unesite ime proizvoda: ");
	scanf("%9[^\n]", kave.ime_proizvoda);
	getchar();
	printf("Unesite cijenu proizvoda: ");
	scanf("%d", &kave.cijena);
	getchar();
	fseek(fp, sizeof(KAVA) * brojKava, SEEK_CUR);
	fwrite(&kave, sizeof(KAVA), 1, fp);
	rewind(fp);
	brojKava++;
	fwrite(&brojKava, sizeof(int), 1, fp);
	fclose(fp);
}

void prepravljanje() {
	FILE* fp = NULL;
	int reload;
	fp = fopen("kava.bin", "rb+");
	if (fp == NULL)
		printf("Niste unijeli niti jedan proizvod.\n");
	else {
		printf("Unesi id kave koje zelite ispraviti:\n");
		scanf("%d", &reload);
		fseek(fp, sizeof(int) + (sizeof(KAVA) * (reload - 1)), SEEK_SET);
		KAVA ispravljenProizvod;
		ispravljenProizvod.id = reload;
		getchar();
		printf("Unesite ispravljeno ime Tvrtke: ");
		scanf("%24[^\n]", ispravljenProizvod.ime_tvrtke);
		getchar();
		printf("Unesite ispravljenu ime proizvoda: ");
		scanf("%14[^\n]", ispravljenProizvod.ime_proizvoda);
		getchar();
		printf("Unesite ispravljenu cijenu proizvoda: ");
		scanf("%d", &ispravljenProizvod.cijena);
		getchar();
		fwrite(&ispravljenProizvod, sizeof(KAVA), 1, fp);
		rewind(fp);
		fwrite(&brojKava, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void* ucitavanjeKave() {
	FILE* fp = fopen("kava.bin", "rb");
	if (fp == NULL) {
		printf("Niste unijeli niti jedan proizvod.\n");
		return NULL;
	}
	fread(&brojKava, sizeof(int), 1, fp);
	KAVA* polje = NULL;
	polje = (KAVA*)calloc(brojKava, sizeof(KAVA));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(KAVA), brojKava, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(KAVA* polje) {
	for (i = 0; i < brojKava; i++) {
		printf("Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
	}
}

void* SearchImeTvrtke(KAVA* polje) {
	char reqName[25];
	int br = 0;

	printf("Upisite ime tvrtke trazenog proizvoda:\n");
	getchar();
	scanf("%24[^\n]", reqName);

	for (i = 0; i < brojKava; i++) {
		if (!strcmp(reqName, (polje + i)->ime_tvrtke)) {
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nProizvod pod ovim imenom tvrtke nije pronaden.\n");
	return NULL;
}

void* SearchImeProizvoda(KAVA* polje) {
	char reqNam[25];
	int br = 0;

	printf("Upisite ime proizvoda kojeg trazite:\n");
	getchar();
	scanf("%14[^\n]", reqNam);

	for (i = 0; i < brojKava; i++) {
		if (!strcmp(reqNam, (polje + i)->ime_proizvoda)) {
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nNema proizvoda pod ovim imenom.\n");
	return NULL;
}

void* SearchCijena(KAVA* polje) {
	int reqPrice, br = 0;

	printf("Unesite broj cijene koju trazite:\n");
	scanf("%d", &reqPrice);

	for (i = 0; i < brojKava; i++) {
		if (reqPrice == (polje + i)->cijena) {
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena cijena nije pronadjena.\n");
	return NULL;
}

void subs(KAVA* veci, KAVA* manji) {
	KAVA temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}

void subs2(KAVA* manji, KAVA* veci) {
	KAVA temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortCijenaUzl(KAVA* polje) {
	for (int j = 0; j < brojKava; j++) {
		for (int i = 0; i < brojKava - 1; i++) {
			if (polje[i].cijena > polje[i + 1].cijena) {
				subs2((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojKava; i++) {
		printf("\nID: %d Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
	}
	printf("\n");
}

void selectionSortCijenaSil(KAVA* polje) {
	for (int j = 0; j < brojKava; j++) {
		for (int i = 0; i < brojKava - 1; i++) {
			if (polje[i].cijena < polje[i + 1].cijena) {
				subs((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojKava; i++) {
		printf("\nID: %d Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->ime_tvrtke, (polje + i)->ime_proizvoda, (polje + i)->cijena);
	}
	printf("\n");
}
void brisanjeKave(KAVA* polje) {
	FILE* fp = NULL;
	fp = fopen("kava.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje kave");
	}
	rewind(fp);
	fseek(fp, sizeof(int), SEEK_CUR);

	int br = 0, reqId;

	printf("Unesite ID kave kojeg zelite obrisati:");
	scanf("%d", &reqId);

	for (i = 0; i < brojKava; i++) {
		if (reqId != (polje + i)->id) {
			fwrite((polje + i), sizeof(KAVA), 1, fp);
			br++;
		}
	}
	rewind(fp);
	fwrite(&br, sizeof(int), 1, fp);
	fclose(fp);
}

void izlaz(KAVA* polje) {
	printf("Zelite li pri izlasku programa izbrisati datoteku ili zadrzati?\n");
	printf("Ako zelite izbrisati datoteku napisite obrisi, ako ne zelite napisite zadrzi\n");

	char uvjet[7] = { '\0' };
	scanf("%6s", uvjet);
	if (!strcmp("obrisi", uvjet)) {
		remove("kava.bin") == 0 ? printf("Izbrisali ste datoteku kava.bin.\n") : printf("Datoteka neuspjesno izbrisani ili ona ne postoji.\n");
		printf("\nIzlaz iz programa.\n");
		free(polje);
	}
	else printf("\nZadrzali ste datoteku.\nIzlaz iz programa\n");
}
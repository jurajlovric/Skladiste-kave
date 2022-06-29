#ifndef Header_H
#define Header_H

typedef struct kava {
	int cijena;
	char ime_tvrtke[25];
	char ime_proizvoda[15];
	int id;
}KAVA;

int izbornik();
int izbornikSrch();
int izbornikSrt();
void kreiranjeDat();
void dodavanjeKave();
void prepravljanje();
void* ucitavanjeKave();
void ispisivanje(KAVA*);
void* SearchImeTvrtke(KAVA*);
void* SearchImeProizvoda(KAVA*);
void* SearchCijena(KAVA*);
void subs(KAVA*, KAVA*);
void subs2(KAVA*, KAVA*);
void selectionSortCijenaUzl(KAVA*);
void selectionSortCijenaSil(KAVA*);
void brisanjeKave(KAVA*);
void izlaz(KAVA*);

#endif //Header_H

//ALEXANDRU Ioana | 314CB

typedef struct celula
{
  void *info;
  struct celula *urm;
} TCelula, *TLista, **ALista;

typedef struct
{
	int id;
	char tip;
}TInfo;

#define dime(s)	sizeof(TInfo)

int compare(void *a, void *b)
{
	return ((TInfo*)a)->id - ((TInfo*)b)->id;
}
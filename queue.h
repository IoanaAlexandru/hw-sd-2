//ALEXANDRU Ioana | 314CB

typedef struct
{
	TLista first, last;
}TQueue;

#define emptyQ(q)	((q).first == NULL)
#define first(q)	((q).first)->info
#define last(q)		((q).last)->info

//intrq returnează 1 dacă s-a adăugat un element cu succes şi 0 în caz contrar
int intrq(TQueue *q, void* ae)
{
	TLista aux = malloc(sizeof(TCelula));
	if (!aux)
		return 0;
	aux->urm = NULL;
	aux->info = (TInfo*)malloc(sizeof(TInfo));
	if (!aux->info) {
		free(aux);
		return 0;
	}
	memcpy(aux->info, ae, dime(*q));
	if (emptyQ(*q)) {
		q->first = aux;
	}
	else {
		q->last->urm = aux;
	}
	q->last = aux;
	return 1;
}

//pop returnează 1 dacă s-a eliminat un element şi 0 dacă coada este goală
int extrq(TQueue *q, void *ae)
{
	TLista aux = q->first;
	if (!aux)
		return 0;
	memcpy(ae, aux->info, dime(*q));
	if (q->first == q->last) { //dacă coada mai are doar un element
		free(q->first->info);
		free(q->first);
		q->first = NULL;
		q->last = NULL;
	}
	else {
		q->first = q->first->urm;
		free(aux->info);
		free(aux);
	}
	return 1;
}

TQueue* copyq(TQueue *q)
{
	TQueue *copie = calloc(1, sizeof(TQueue)),
		   *aux = calloc(1, sizeof(TQueue));
	if (!copie)
		return NULL;
	if (!aux) {
		free(copie);
		return NULL;
	}
	void *e = calloc(1, dime(*s));
	if (!e) {
		free(copie);
		free(aux);
		return NULL;
	}
	while (extrq(q, e))
		intrq(aux, e);
	while (extrq(aux, e)) {
		intrq(copie, e);
		intrq(q, e);
	}
	free(aux);
	free(e);
	return copie;
}

//URMĂTOARELE FUNCŢII NU FOLOSESC STRUCTURA DE LISTĂ A COZII

void sortedInsert(TQueue *q, void *ae)
{
	if (emptyQ(*q)) {
		intrq(q, ae);
		return;
	}
	TQueue *aux = calloc(1, sizeof(TQueue));
	if (!aux)
		return;
	void *el = calloc(1, dime(*q));
	if (!el)
		return;
	while (!emptyQ(*q)) {
		if (compare(first(*q), ae) < 0) {
			extrq(q, el);
			intrq(aux, el);
		}
		else
			break;
	}
	intrq(aux, ae);
	while (extrq(q, el))
		intrq(aux, el);
	free(el);
	q->first = aux->first;
	q->last = aux->last;
	free(aux);
	return;
}

void sortq(TQueue *q)
{
	TQueue *aux = calloc(1, sizeof(TQueue));
	if (!aux)
		return;
	void *el = calloc(1, dime(*q));
	if (!aux)
		return;
	while (extrq(q, el))
		sortedInsert(aux, el);
	q->first = aux->first;
	q->last = aux->last;
	free(aux);
	free(el);
	return;
}

void printq(TQueue q, FILE *out)
{
	void *e = calloc(1, dime(q));
	if (!e)
		return;
	while (extrq(&q, e))
		fprintf(out, "%c", ((TInfo*)e)->tip);
	free(e);
}

//correctq
int correctq(TQueue *q)
{
	TStack *s = calloc(1, sizeof(TStack));
	if (!s)
		return 0;
	void *ae = calloc(1, dime(*q));
	if (!ae)
		return 0;
	while (extrq(q, ae))
		push(s, ae);
	int max = corrects(s);
	while (pop(s, ae))
		intrq(q, ae);
	free(s);
	free(ae);
	return max;
}
//ALEXANDRU Ioana | 314CB

#define TStack TLista
//practic o stivă este pur şi simplu o listă,
//cu primul element în vârful stivei

#define emptyS(s)	((s) == NULL)
#define top(s)		(s)->info
//pentru a putea fi modificate uşor, în cazul unei implementări diferite a stivei

//push returnează 1 dacă s-a adăugat un element cu succes şi 0 în caz contrar
int push(TStack *s, void *ae)
{
	TLista aux = malloc(sizeof(TCelula));
	if (!aux)
		return 0;
	aux->urm = *s;
	aux->info = (TInfo*)malloc(sizeof(TInfo));
	if (!aux->info) {
		free(aux);
		return 0;
	}
	memcpy(aux->info, ae, dime(*s));
	*s = aux;
	return 1;
}

//pop returnează 1 dacă s-a eliminat un element şi 0 dacă stiva este goală
int pop(TStack *s, void *ae)
{
	if (!(*s))
		return 0;
	TLista aux = *s;
	memcpy(ae, top(*s), dime(*s));
	*s = (*s)->urm;
	free(aux->info);
	free(aux);
	return 1;
}

TStack* copys(TStack *s)
{
	TStack *aux = calloc(1, sizeof(TStack)),
		   *copie = calloc(1, sizeof(TStack));
	if (!aux)
		return NULL;
	if (!copie) {
		free(aux);
		return NULL;
	}
	void *e = calloc(1, dime(*s));
	if (!e) {
		free(aux);
		free(copie);
		return NULL;
	}
	while (pop(s, e))
		push(aux, e);
	while (pop(aux, e)) {
		push(copie, e);
		push(s, e);
	}
	free(aux);
	free(e);
	return copie;
}

//URMĂTOARELE FUNCŢII NU FOLOSESC STRUCTURA DE LISTĂ A STIVEI

int sorts(TStack *s)
{
	if (emptyS(*s))
		return 0;
	void *e1 = calloc(1, dime(*s)),
		 *e2 = calloc(1, dime(*s));
	if (!e1)
		return 0;
	if (!e2) {
		free(e1);
		return 0;
	}
	TStack aux = NULL;
	while(!emptyS(*s)) {
		pop(s, e1);
		while (!emptyS(aux))
			if (compare(top(aux), e1) > 0) {
				pop(&aux, e2);
				push(s, e2);
			}
			else
				break;
		push(&aux, e1);
	}
	*s = aux;
	free(e1);
	free(e2);
	return 1;
}

void prints(TStack s, FILE *out)
{
	void *e = calloc(1, dime(s));
	if (!e)
		return;
	if (pop(&s, e)) {
		prints(s, out);
		fprintf(out, "%c", ((TInfo*)e)->tip);
		free(e);
	}
	else {
		free(e);
		return;
	}
}

char bracket(char c)
{
	switch (c) {
	case '(':
		return ')';
	case '[':
		return ']';
	case '{':
		return '}';
	case ')':
		return '(';
	case ']':
		return '[';
	case '}':
		return '{';
	default:
		return 0;
	}
}

int corrects(TStack *s)
{
	TStack *aux = calloc(1, sizeof(TStack)),
		   *removed = calloc(1, sizeof(TStack));
	if (!aux)
		return 0;
	if (!removed) {
		free(aux);
		return 0;
	}
	char open[] = "([{", close[] = ")]}";
	int len = 0, max = 0, nr = 0, i, again = 0;
	void *e = calloc(1, sizeof(TInfo));
	if (!e) {
		free(aux);
		free(removed);
		return 0;
	}
	while(!emptyS(*s)) {
		pop(s, e);
		push(removed, e);
		nr++;
		if (strchr(close, ((TInfo*)e)->tip) != NULL) {
			push(aux, e);
		}
		else if (strchr(open, ((TInfo*)e)->tip) != NULL) {
			if (!emptyS(*aux)) {
				if (bracket(((TInfo*)top(*aux))->tip) == ((TInfo*)e)->tip) {
					pop(aux, e);
					len += 2;
					if (emptyS(*aux) && len > max) {
						max = len;
					}
				}
				else {
					again = 1;
				}
			}
			else {
				again = 1;
			}
		}
		if (emptyS(*s) || again) {
			while (pop(aux, e)); //şterg toate elementele din aux
			len = 0;
			for (i = 1; i < nr; i++) {
				pop(removed, e);
				push(s, e);
			}
			nr = 0;
			again = 0;
		}
	}
	while (pop(aux, e));
	free(aux);
	while (pop(removed, e));
	free(removed);
	free(e);
	return max;
}
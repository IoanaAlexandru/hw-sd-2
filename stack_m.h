#define TStack TLista
//practic o stivă este pur şi simplu o listă,
//cu primul element în vârful stivei

#define emptyS(s)	((s) == NULL)
#define top(s)		(s)->info
//^ pentru a putea fi modificate uşor, în cazul unei
//implementări diferite a stivei

int compare(void *a, void *b)
{
	return ((TInfo*)a)->id - ((TInfo*)b)->id;
}

//push
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

//pop
int pop(TStack *s, void *ae)
{
	TLista aux = *s;
	if (!aux)
		return 0;
	memcpy(ae, top(*s), dime(*s));
	*s = (*s)->urm;
	free(aux->info);
	free(aux);
	return 1;
}

//URMĂTOARELE FUNCŢII NU FOLOSESC STRUCTURA DE LISTĂ A STIVEI

//sorts
int sorts(TStack *s)
{
	if (emptyS(*s))
		return 0;
	void *e1 = calloc(1, dime(*s)),
		 *e2 = calloc(1, dime(*s));
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
	return 1;
}

//prints
void prints(TStack stack, FILE *out)
{
	TInfo e;
	if (pop(&stack, &e)) {
		prints(stack, out);
		fprintf(out, "%c", e.tip);
	}
	else
		return;
}

//corrects

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

int corrects(TStack s)
{
	TStack aux = NULL, removed = NULL;
	char open[] = "([{", close[] = ")]}";
	int len = 0, max = 0, nr = 0, i;
	void *e = calloc(1, sizeof(TInfo));
	while(!emptyS(s)) {
		pop(&s, e);
		//printf("%c\t", ((TInfo*)e)->tip);
		push(&removed, e);
		nr++;
		if (strchr(close, ((TInfo*)e)->tip) != NULL) {
			push(&aux, e);
			//printf("1 ");
		}
		else if (strchr(open, ((TInfo*)e)->tip) != NULL) {
			if (!emptyS(aux)) {
				if (bracket(((TInfo*)top(aux))->tip) == ((TInfo*)e)->tip) {
					pop(&aux, e);
					len += 2;
					if (emptyS(aux))
						//printf("da\n");
					if (emptyS(aux) && len > max) {
						max = len;
						//printf("2 ");
					}
				}
				else {
					//printf("3 ");
					while (pop(&aux, e));
					len = 0;
					for (i = 1; i < nr; i++) {
						pop(&removed, e);
						push(&s, e);
					}
					nr = 0;
				}
			}
			else {
				//printf("4 ");
				len = 0;
				for (i = 1; i < nr; i++) {
					pop(&removed, e);
					push(&s, e);
				}
				nr = 0;
			}
		}
		if (emptyS(s)) {
			while (pop(&aux, e));
				len = 0;
				for (i = 1; i < nr; i++) {
				pop(&removed, e);
				push(&s, e);
			}
			nr = 0;
		}
		//printf("max = %d len = %d\n", max, len);
	}
	return max;
}
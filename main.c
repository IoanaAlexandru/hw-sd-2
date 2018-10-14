//ALEXANDRU Ioana | 314CB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "stack.h"
#include "queue.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s in_file out_file\n", argv[0]);
		return -1;
	}
	FILE *in = fopen(argv[1], "r");
	if (!in) {
		printf("Could not open input file\n");
		return -1;
	}
	FILE *out = fopen(argv[2], "w");
	if (!out) {
		printf("Could not open output file\n");
		return -1;
	}

	int N, S, C, i;
	fscanf(in, "%d %d %d", &N, &S, &C);

	TQueue *queue = (TQueue*)calloc(C, sizeof(TQueue)), *qc;
	if (!queue)
		return -1;
	TLista *stack = (TLista*)calloc(S, sizeof(TLista)), *sc;
	if (!stack)
		return -1;

	char op[10];
	int id_stiva, id_coada;
	void *ae = (TInfo*)calloc(1, sizeof(TInfo));
	if (!ae)
		return -1;

	for (; N; N--) {
		fscanf(in, "%s ", op);
		if (!strcmp(op, "push")) {
			fscanf(in, "%d %d %c", &id_stiva, &(((TInfo*)ae)->id), &(((TInfo*)ae)->tip));
			push(&(stack[id_stiva]), ae);
		}
		else if (!strcmp(op, "intrq")) {
			fscanf(in, "%d %d %c", &id_coada, &(((TInfo*)ae)->id), &(((TInfo*)ae)->tip));
			intrq(&(queue[id_coada]), ae);
		}
		else if (!strcmp(op, "pop")) {
			fscanf(in, "%d", &id_stiva);
			pop(&(stack[id_stiva]), ae);
		}
		else if (!strcmp(op, "extrq")) {
			fscanf(in, "%d", &id_coada);
			extrq(&(queue[id_coada]), ae);
		}
		else if (!strcmp(op, "sorts")) {
			fscanf(in, "%d", &id_stiva);
			sorts(&stack[id_stiva]);
		}
		else if (!strcmp(op, "sortq")) {
			fscanf(in, "%d", &id_coada);
			sortq(&queue[id_coada]);
		}
		else if (!strcmp(op, "prints")) {
			for (i = 0; i < S; i++) {
				sc = copys(&stack[i]);
				fprintf(out, "\"");
				prints(*sc, out);
				fprintf(out, "\"\n");
				free(sc);
			}
		}
		else if (!strcmp(op, "printq")) {
			for (i = 0; i < C; i++) {
				qc = copyq(&queue[i]);
				fprintf(out, "\"");
				printq(*qc, out);
				fprintf(out, "\"\n");
				free(qc);
			}
		}
		else if (!strcmp(op, "corrects")) {
			fscanf(in, "%d", &id_stiva);
			sc = copys(&stack[id_stiva]);
			fprintf(out, "%d\n", corrects(sc));
			free(sc);
		}
		else if (!strcmp(op, "correctq")) {
			fscanf(in, "%d", &id_coada);
			qc = copyq(&queue[id_coada]);
			fprintf(out, "%d\n", correctq(qc));
			free(qc);
		}
		else {
			printf("Invalid operation\n");
			return -1;
		}
	}

	for (i = 0; i < S; i++)
		while(pop(&stack[i], ae));
	for (i = 0; i < C; i++)
		while(extrq(&queue[i], ae));
	free(queue);
	free(stack);
	free(ae);

	fclose(out);
	fclose(in);
	return 0;
}
#include <stdlib.h>
#include <string.h>
#include "cite.h"

static void strindent(char *str, int c);

static void
strindent(char *str, int c)
{
	int i;

	for (i = 0; i < c; ++i) {
		str[i] = '\t';
	}
	str[i] = '\0';
}

struct htmles *
htmlesalloc(char *tag, char *text, int contentc)
{
	struct htmles *htmlesp;

	if ((htmlesp = malloc(sizeof(struct htmles))) == NULL) {
		return NULL;
	}
	if ((htmlesp->tag = malloc((strlen(tag) + 1) * sizeof(char))) == NULL) {
		return NULL;
	}
	strcpy(htmlesp->tag, tag);
	if (contentc > 0) {
		if ((htmlesp->contentv = malloc(contentc * sizeof(struct htmles))) == NULL) {
			return NULL;
		}
	}
	htmlesp->contentc = contentc;
	if (text != NULL) {
		if ((htmlesp->text = malloc ((strlen(text) + 1) * sizeof(char))) == NULL) {
			return NULL;
		}
		strcpy(htmlesp->text, text);
	} else {
		htmlesp->text = NULL;
	}

	return htmlesp;
}

void
htmlesfree(struct htmles *htmlesp) {
	int i;

	free(htmlesp->tag);
	free(htmlesp->text);
	for (i = 0; i < htmlesp->contentc; ++i) {
		htmlesfree(htmlesp->contentv + i);
	}
	free(htmlesp->contentv);
}

int
htmlelen(struct htmles *htmlep, int indent)
{
	int i, l;

	l = (strlen(htmlep->tag) + indent + 3) * 2 + 1;
	if (htmlep->text) {
		l += strlen(htmlep->text + indent + 1);
	} else {
		for (i = 0; i < htmlep->contentc; ++i) {
			l += htmlelen(htmlep->contentv + i, indent + 1);
		}
	}
	l += 1;

	return l;
}

char *
htmlstralloc(struct htmles *htmlep)
{
	char *str;
	int l;

	l = htmlelen(htmlep, 0);
	str = malloc(l * sizeof(char));

	return str;
}

int
htmlestostr(struct htmles *htmlep, char *str, int indent)
{
	int i, j;

	strindent(str, indent);
	strcat(str, "<");
	strcat(str, htmlep->tag);
	strcat(str, ">\n");
	i = strlen(htmlep->tag) + indent + 3;
	if (htmlep->text) {
		strindent(str + i, indent + 1);
		strcat(str, htmlep->text);
		strcat(str, "\n");
		i += strlen(htmlep->text) + indent + 2;
	} else {
		for (j = 0; j < htmlep->contentc; ++j) {
			i += htmlestostr(htmlep->contentv + j, str + i, indent + 1);
		}
	}
	strindent(str + i, indent);
	strcat(str, "</");
	strcat(str, htmlep->tag);
	strcat(str, ">\n");
	i += strlen(htmlep->tag) + indent + 4;

	return i;
}

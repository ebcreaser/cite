#include <stdlib.h>
#include <string.h>
#include "cite.h"

static void strindent(char *str, int c);

int
htmlesalloc(struct htmles *htmlesp, char *tag, char *text, int contentc)
{
	if ((htmlesp->tag = malloc((strlen(tag) + 1) * sizeof(char))) == NULL) {
		return -1;
	}
	strcpy(htmlesp->tag, tag);
	if (contentc > 0) {
		if ((htmlesp->contentv = malloc(contentc * sizeof(struct htmles))) == NULL) {
			return -1;
		}
	}
	htmlesp->contentc = contentc;
	if (text != NULL) {
		if ((htmlesp->text = malloc ((strlen(text) + 1) * sizeof(char))) == NULL) {
			return -1;
		}
		strcpy(htmlesp->text, text);
	} else {
		htmlesp->text = NULL;
	}

	return 0;
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
htmlelen(struct htmles *htmlesp, int indent)
{
	int i, l;

	l = (strlen(htmlesp->tag) + indent + 3) * 2 + 1;
	if (htmlesp->text) {
		l += strlen(htmlesp->text) + indent + 1;
	} else {
		for (i = 0; i < htmlesp->contentc; ++i) {
			l += htmlelen(htmlesp->contentv + i, indent + 1);
		}
	}
	l += 1;

	return l;
}

char *
htmlstralloc(struct htmles *htmlesp)
{
	char *str;
	int l;

	l = htmlelen(htmlesp, 0);
	str = malloc(l * sizeof(char));

	return str;
}

int
makeules(struct htmles *ulesp, int listc, char **listv)
{
	int i;

	if ((htmlesalloc(ulesp, "ul", NULL, listc)) < 0) {
		return -1;
	}
	for (i = 0; i < listc; ++i) {
		if ((htmlesalloc(ulesp->contentv + i, "li", listv[i], 0)) < 0) {
			return -1;
		}
	}

	return 0;
}

static void
strindent(char *str, int c)
{
	int i;

	for (i = 0; i < c; ++i) {
		str[i] = '\t';
	}
	str[i] = '\0';
}

char *
htmlestostr(struct htmles *htmlesp, char *str, int indent)
{
	int i, tagl;

	tagl = strlen(htmlesp->tag);
	strindent(str, indent);
	str += indent;
	*str = '<';
	str += 1;
	strcpy(str, htmlesp->tag);
	str += tagl;
	strcpy(str, ">\n");
	str += 2;
	if (htmlesp->text) {
		strindent(str, indent + 1);
		str += indent + 1;
		strcpy(str, htmlesp->text);
		str += strlen(htmlesp->text);
		*str = '\n';
		str += 1;
	} else {
		for (i = 0; i < htmlesp->contentc; ++i) {
			str = htmlestostr(htmlesp->contentv + i, str, indent + 1);
		}
	}
	strindent(str, indent);
	str += indent;
	strcpy(str, "</");
	str += 2;
	strcpy(str, htmlesp->tag);
	str += tagl;
	strcpy(str, ">\n");
	str += 2;
	*str = '\0';

	return str;
}

#include <stdlib.h>
#include <string.h>
#include "cite.h"

void
strindent(char *str, int c)
{
	int i;

	for (i = 0; i < c; ++i) {
		str[i] = '\t';
	}
	str[i] = '\0';
}

int
htmlelen(struct html_element *htmlep, int indent)
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
htmlstralloc(struct html_element *htmlep)
{
	char *str;
	int l;

	l = htmlelen(htmlep, 0);
	str = malloc(l * sizeof(char));

	return str;
}

int
htmletostr(struct html_element *htmlep, char *str, int indent)
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
			i += htmletostr(htmlep->contentv + j, str + i, indent + 1);
		}
	}
	strindent(str + i, indent);
	strcat(str, "</");
	strcat(str, htmlep->tag);
	strcat(str, ">\n");
	i += strlen(htmlep->tag) + indent + 4;

	return i;
}

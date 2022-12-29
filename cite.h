#ifndef CITE_H
#define CITE_H

struct html_element
{
	char *tag;
	char *args;
	char *text;
	struct html_element *contentv;
	int contentc;
};

void indent(char *str, int c);
int htmlelen(struct html_element *htmlep, int indent);
char *htmlstralloc(struct html_element *htmlep);
int htmletostr(struct html_element *htmlep, char *str, int indent);

#endif

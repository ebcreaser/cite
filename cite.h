#ifndef CITE_H
#define CITE_H

struct htmles
{
	char *tag;
	char *args;
	char *text;
	struct htmles *contentv;
	int contentc;
};

struct htmles *htmlesalloc(char *tag, char *text, int contentc);
void htmlesfree(struct htmles *htmlesp);
struct htmles *gethtmlules(int listc, char **listv);
int htmlelen(struct htmles *htmlep, int indent);
char *htmlstralloc(struct htmles *htmlep);
int htmlestostr(struct htmles *htmlep, char *str, int indent);

#endif

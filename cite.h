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

int htmlesalloc(struct htmles *htmlesp, char *tag, char *text, int contentc);
int makeules(struct htmles *ulesp, int listc, char **listv);
void htmlesfree(struct htmles *htmlesp);
struct htmles *gethtmlules(int listc, char **listv);
int htmlelen(struct htmles *htmlep, int indent);
char *htmlstralloc(struct htmles *htmlep);
char *htmlestostr(struct htmles *htmlesp, char *str, int indent);

#endif

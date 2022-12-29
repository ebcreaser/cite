#include <stdio.h>
#include <stdlib.h>
#include "cite.h"

int
main()
{
	struct htmles *htmlesp;
	char *listv[] =
	{
		"1",
		"2",
		"3"
	};
	char *str;

	if ((htmlesp = malloc(sizeof(struct htmles))) == NULL) {
		return -1;
	}
	if ((makeules(htmlesp, 3, listv)) < 0) {
		return -1;
	}
	if ((str = htmlstralloc(htmlesp)) == NULL) {
		return -1;
	}
	htmlestostr(htmlesp, str, 0);
	puts(str);
	free(str);
	htmlesfree(htmlesp);

	return 0;
}

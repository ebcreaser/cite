#include <stdio.h>
#include <stdlib.h>
#include "cite.h"

int
main()
{
	struct htmles *htmlesp;

	htmlesp = htmlesalloc("div", NULL, 3);
	puts(htmlesp->tag);
	htmlesfree(htmlesp);

	return 0;
}

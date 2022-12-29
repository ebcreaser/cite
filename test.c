#include <stdio.h>
#include <stdlib.h>
#include "cite.h"

int
main()
{
	char *str;
	int i = 0;

	struct html_element htmle;
	struct html_element contentv[3];

	htmle.tag = "html";
	htmle.text = NULL;
	htmle.contentv = contentv;
	htmle.contentc = 3;
	for (i = 0; i < 3; ++i) {
		contentv[i].tag = "p";
		contentv[i].text = "text";
		puts(contentv[i].text);
	}
	contentv[0].text = NULL;
	contentv[0].contentc = 1;
	contentv[0].contentv = contentv + 1;
	str = htmlstralloc(&htmle);
	htmletostr(&htmle, str, 0);
	puts(str);
	free(str);

	return 0;
}

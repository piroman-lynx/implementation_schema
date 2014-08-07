#include <stdio.h>
#include <stdlib.h>

#include "module.h"

void is_cc_register(const struct module_description is_cc_module_for_explore)
{
    unsigned char max=(is_cc_module_for_explore).exports_argc(), i, j, k, offset;
    struct call_description cd;

    for (i=0; i<max; i++) {
	cd = (is_cc_module_for_explore).exports_argv(i);
	printf("[module]%s ", cd.call);
	for (j=0; j<cd.args; j++) {
	    printf("ARG%d",j);
	    if (j+1 < cd.args) {
		printf(",");
	    }
	}
	printf("	:%s(", cd.function);
	for (j=0; j<cd.args; j++) {
	    int arg=0;
	    char *str = malloc(sizeof(char) * strlen(cd.args_array[j])+1+ 10);
	    memset(str, '\0', strlen(cd.args_array[j])+1+10);
	    offset=0;
	    for (k=0; k<strlen(cd.args_array[j]); k++) {
		str[k+offset] = cd.args_array[j][k];
		if ((arg==0)&&(cd.args_array[j][k] == 'A')) {
		    arg++;
		} else if ((arg==1)&&(cd.args_array[j][k] == 'R')) {
		    arg++;
		} else if ((arg==2)&&(cd.args_array[j][k] == 'G')) {
		    arg=0;
		    char *append = malloc(sizeof(char)*11);
		    memset(append, '\0', 11);
		    sprintf(append, "%d", j);
		    memcpy(str+sizeof(char)*k+1, append, strlen(append)*sizeof(char));
		    offset+=strlen(append);
		    free(append);
		}
	    }
	    printf("%s", str);
	    free(str);
	    if (j+1 < cd.args) {
		printf(",");
	    }
	}
	printf(");\n");
    }
}

void is_cc_call_translation_error(char *moduleName, char *message)
{
    printf("ERROR IN BUILD MODULE: [%s] %s", moduleName, message);
    exit(1);
}

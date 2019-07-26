#include <stdio.h>
#include <string.h>
#include "intro.h"

int main() {
	t_intro *myStruct = new(t_intro, .aString="This is a string !", .anInteger=42, .aDouble=3.14159265357);
	const struct meta_type *metatype = NULL;

	cmeta_print_types((const t_object *)myStruct);

	printf("Setting \"anInteger\" value to 1337. Return code %d\n", CMETA_SET(Int, myStruct, "anInteger", 1337));

	printf("Reading \"anInteger\" value: %d\n", CMETA_READ(Int, myStruct, "anInteger", &metatype));

	if (metatype == NULL)
		printf("Metatype is NULL, the \"anInteger\" member of type \"int\" is not found in the object !\n");

	cmeta_print_types((const t_object *)myStruct);

	delete(myStruct); //Not necessary.
	return 0;
}

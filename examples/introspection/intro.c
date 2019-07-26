#include "intro.h"
#include <string.h>
/**
 * After a call to this macro, we can get the meta struct by
 * using CMETA(t_intro), or get it directly in an object of
 * t_intro type...
 */
CMETA_STRUCT_BUILD(t_intro_DEFINITION)
CMETA_DEFAULT_BUILD(t_intro_DEFINITION)
/*
{
	t_intro *intro = newObject(t_intro);
	if (intro) {
		intro->aDouble = args.aDouble;
		intro->aString = args.aString;
		intro->anInteger = args.anInteger;
	}
	return intro;
}
*/

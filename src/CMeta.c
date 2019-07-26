#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

const struct linked_meta *cmeta_metastructures = NULL;

CMETA_FUNC_READ_GEN(CMETA_ALL_TYPES);
CMETA_FUNC_SET_GEN(CMETA_ALL_TYPES);

const char *const cmeta_type_print_associations[][2] = {
    {"Char",        "%hhi"},
    {"pChar",       "%s"},
    {"Short",       "%hi"},
    {"pShort",      "%p"},
    {"Int",         "%i"},
    {"pInt",        "%p"},
    {"Long",        "%li"},
    {"pLong",       "%p"},
    {"Longlong",    "%lli"},
    {"pLonglong",   "%p"},
    {"uChar",       "%hhu"},
    {"puChar",      "%p"},
    {"uShort",      "%hu"},
    {"puShort",     "%p"},
    {"uInt",        "%u"},
    {"puInt",       "%p"},
    {"uLong",       "%lu"},
    {"puLong",      "%p"},
    {"uLonglong",   "%llu"},
    {"puLonglong",  "%p"},
    {"Float",       "%.7f"},
    {"pFloat",      "%p"},
    {"Double",      "%.14f"},
    {"pDouble",     "%p"},
    {"Longdouble",  "%le"},
    {"pLongdouble", "%p"},
    {"Pointer",     "%p"}
};

static void cmeta_print_type(const t_object *obj, unsigned int typeId)
{
	if (obj && typeId < obj->meta->memCount)
		printf(" - Member %d: '%s' of type '%s'. The type size is %u bytes and the struct offset is %u bytes.\n",
				typeId, obj->meta->members[typeId].name, obj->meta->members[typeId].type, obj->meta->members[typeId].size, obj->meta->members[typeId].offset);
}

static void cmeta_print_value(const t_object *obj, unsigned int typeId)
{
	unsigned int i;
	if (obj && typeId < obj->meta->memCount)
	{
		char val[32];
		for (i = 0; i < sizeof(cmeta_type_print_associations)/sizeof(*cmeta_type_print_associations); i++) {
			if (!strcmp(obj->meta->members[typeId].type, cmeta_type_print_associations[i][0])) {
				snprintf(val, sizeof(val), "    - It's value is : %s\n", cmeta_type_print_associations[i][1]);
				break;
			}
		}
		if (i == sizeof(cmeta_type_print_associations)/sizeof(*cmeta_type_print_associations))
			fprintf(stderr, "Undefined type : '%s' for member '%s.%s'.\n", obj->meta->members[typeId].type, OBJ_NAME(obj), obj->meta->members[typeId].name);
		else
		{
			if (!strcmp(cmeta_type_print_associations[i][0], "float"))
				printf(val, *((float *)(((char *)obj) + obj->meta->members[typeId].offset)));
			else if (!strcmp(cmeta_type_print_associations[i][0], "double"))
				printf(val, *((double *)(((char *)obj) + obj->meta->members[typeId].offset)));
			else
				printf(val, *((size_t *)(((char *)obj) + obj->meta->members[typeId].offset)));
		}
	}
}

void cmeta_print_types(const t_object *obj)
{
    unsigned int i;
    const struct meta_struct *meta;

    if (!obj)
        fprintf(stderr, "%s: no meta given : NULL pointer.\n", __PRETTY_FUNCTION__);
    else {
    	meta = obj->meta;
		printf("Object '%s' has %u Members :\n", OBJ_NAME(obj), meta->memCount);
		for (i = 0; i < meta->memCount; i++) {
			cmeta_print_type(obj, i);
			cmeta_print_value(obj, i);
		}
    }
}

void cmeta_print_all_symbols()
{
/*
	const struct linked_meta *ptr = cmeta_metastructures;
    printf("Printing all registered cmeta symbols:\n");
    while (ptr != NULL) {
        cmeta_print_types(ptr->meta);
        ptr = ptr->next;
    }
    printf("End of registered cmeta symbols.\n");
*/
}

void cmeta_do_nothing()
{

}

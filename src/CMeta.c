#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CMeta.h"
#include "object.h"

const struct linked_meta *cmeta_metastructures = NULL;

CMETA_FUNC_READ_GEN(CMETA_ALL_TYPES);
CMETA_FUNC_SET_GEN(CMETA_ALL_TYPES);

const char *const cmeta_type_print_associations[][2] = {
    {"char",        "%hhi"},
    {"pchar",       "%s"},
    {"short",       "%hi"},
    {"pshort",      "%p"},
    {"int",         "%i"},
    {"pint",        "%p"},
    {"long",        "%li"},
    {"plong",       "%p"},
    {"longlong",    "%lli"},
    {"plonglong",   "%p"},
    {"uchar",       "%hhu"},
    {"puchar",      "%p"},
    {"ushort",      "%hu"},
    {"pushort",     "%p"},
    {"uint",        "%u"},
    {"puint",       "%p"},
    {"ulong",       "%lu"},
    {"pulong",      "%p"},
    {"ulonglong",   "%llu"},
    {"pulonglong",  "%p"},
    {"float",       "%e"},
    {"pfloat",      "%p"},
    {"double",      "%e"},
    {"pdouble",     "%p"},
    {"longdouble",  "%le"},
    {"plongdouble", "%p"},
    {"pointer",     "%p"}
};

int cmeta_get_meta(const struct meta_struct **meta)
{
    if (meta && *meta) {
        if (IS_OBJ(*meta) && (OBJ_MAGIC(*meta) & 0xFFFF0000) == CMETA_MAGIC) {
            return 0; //This is the meta structure
        } else {
            (*meta) = *(struct meta_struct **)(*meta);
            if (IS_OBJ(*meta) && (OBJ_MAGIC(*meta) & 0xFFFF0000) == CMETA_MAGIC) {
                return 1; //The struct given is a data structure
            }
        }
        *meta = NULL;
    }
    return -1; //This pointer does not contain meta structure
}

void cmeta_print_types(const void *ptr)
{
    unsigned int i, j;
    int data;
    const struct meta_struct *meta = (const struct meta_struct *)ptr;
    if (!ptr)
        fprintf(stderr, "%s: no meta given : NULL pointer.\n", __PRETTY_FUNCTION__);
    else {
        data = cmeta_get_meta(&meta);
        if (data >= 0) {
            printf("%s structure '%s' has %u Members :\n", data == 0 ? "Meta" : "Data", OBJ_NAME(meta), meta->memCount);
            for (i = 0; i < meta->memCount; i++) {
                printf(" - Member %d: '%s' of type '%s'. The type size is %u bytes and the struct offset is %u bytes.\n",
                        i, meta->members[i].name, meta->members[i].type, meta->members[i].size, meta->members[i].offset);
                char val[32];
                if (data) {
                    for (j = 0; j < sizeof(cmeta_type_print_associations)/sizeof(*cmeta_type_print_associations); j++) {
                        if (!strcmp(meta->members[i].type, cmeta_type_print_associations[j][0])) {
                            snprintf(val, sizeof(val), "    - It's value is : %s\n", cmeta_type_print_associations[j][1]);
                            break;
                        }
                    }
                    if (j == sizeof(cmeta_type_print_associations)/sizeof(*cmeta_type_print_associations))
                        fprintf(stderr, "Undefined type : '%s' for member '%s.%s'.\n", meta->members[i].type, OBJ_NAME(meta), meta->members[i].name);
                    else
                    {
                        if (!strcmp(cmeta_type_print_associations[j][0], "float"))
                            printf(val, *((float *)(((char *)ptr) + meta->members[i].offset)));
                        else if (!strcmp(cmeta_type_print_associations[j][0], "double"))
                            printf(val, *((double *)(((char *)ptr) + meta->members[i].offset)));
                        else
                            printf(val, *((size_t *)(((char *)ptr) + meta->members[i].offset)));
                    }
                }
            }
        } else {
            fprintf(stderr, "%s: no meta given : Invalid pointer.\n", __PRETTY_FUNCTION__);
        }
    }
}

void cmeta_print_all_symbols()
{
    const struct linked_meta *ptr = cmeta_metastructures;
    printf("Printing all registered cmeta symbols:\n");
    while (ptr != NULL) {
        cmeta_print_types(ptr->meta);
        ptr = ptr->next;
    }
    printf("End of registered cmeta symbols.\n");
}

void cmeta_do_nothing()
{

}

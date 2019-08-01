#include <stdio.h>
#include "get_opt.h"


int main()
{
	char 	*av_ml[] = {
			"binary_options",
			"-i",
			"42",
			"-f",
			"3.141593",
			"-s",
			"This is a string !"
	};

	char 	*av_mf[] = {
			"binary_options",
			"-s",
			"This is a string !",
			"-i",
			"42",
			"-f",
			"3.141593"
	};
	int ac = sizeof(av_ml) / sizeof(*av_ml);
	t_getopt *opt = new(t_getopt);
	opt_register(opt, 's', ePCHAR, MANDATORY);
	opt_register(opt, 'i', eINT, OPTION);
	opt_register(opt, 'f', eFLOAT, OPTION);

	printf("Error codes:\n"
			"OPT_NOERR	(0)\n"
			"OPT_PARAMS	(1)\n"
			"OPT_FUNC	(2)\n"
			"OPT_EXIST	(3)\n"
			"OPT_NOTFOUND	(4)\n"
			"OPT_NOTSET	(5)\n"
			"OPT_MANDAT	(6)\n"
			"OPT_OPTERROR	(7)\n");
	printf("ML(%d) Param parsing result - All: %d\n", ac, opt_parse_params(opt, ac, av_ml));
	printf("ML(%d) Param parsing result - Missing mandat value: %d\n", ac-1, opt_parse_params(opt, ac-1, av_ml));
	printf("ML(%d) Param parsing result - Missing mandat option and value: %d\n", ac-2, opt_parse_params(opt, ac-2, av_ml));

	printf("MF(%d) Param parsing result - All: %d\n", ac, opt_parse_params(opt, ac, av_mf));
	printf("MF(%d) Param parsing result - Missing optional value: %d\n", ac-1, opt_parse_params(opt, ac-1, av_mf));
	printf("MF(%d) Param parsing result - Missing optional option and value: %d\n", ac-2, opt_parse_params(opt, ac-2, av_mf));

	return 0;
}

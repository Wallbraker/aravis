#include <arvexpression.h>
#include <arvdebug.h>
#include <stdlib.h>

static char **arv_option_expressions = NULL;
static int arv_option_debug_level;

static const GOptionEntry arv_option_entries[] =
{
	{ G_OPTION_REMAINING,	' ', 0, G_OPTION_ARG_STRING_ARRAY,
		&arv_option_expressions,		NULL, NULL},
	{ "debug", 		'd', 0, G_OPTION_ARG_INT,
		&arv_option_debug_level, 	"Debug mode", NULL },
	{ NULL }
};

int
main (int argc, char **argv)
{
	GOptionContext *context;
	GError *error = NULL;
	int i;

	g_type_init ();

	context = g_option_context_new (NULL);
	g_option_context_add_main_entries (context, arv_option_entries, NULL);

	if (!g_option_context_parse (context, &argc, &argv, &error)) {
		g_option_context_free (context);
		g_print ("Option parsing failed: %s\n", error->message);
		g_error_free (error);
		return EXIT_FAILURE;
	}

	g_option_context_free (context);

	arv_debug_enable (arv_option_debug_level);

	if (arv_option_expressions == NULL) {
		g_print ("Missing expression.\n");
		return EXIT_FAILURE;
	}

	for (i = 0; arv_option_expressions[i] != NULL; i++) {
		parse_expression (arv_option_expressions[i]);
	}

	return EXIT_SUCCESS;
}
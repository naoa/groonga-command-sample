#include <string.h>
#include <stdlib.h>
#include <groonga/plugin.h>

#ifdef __GNUC__
# define GNUC_UNUSED __attribute__((__unused__))
#else
# define GNUC_UNUSED
#endif

static grn_obj *
command_echo(grn_ctx *ctx, GNUC_UNUSED int nargs, GNUC_UNUSED grn_obj **args,
             grn_user_data *user_data)
{
  const char *arg_str = GRN_TEXT_VALUE(grn_plugin_proc_get_var_by_offset(ctx, user_data, 0));
  int arg_length = GRN_TEXT_LEN(grn_plugin_proc_get_var_by_offset(ctx, user_data, 0));

  grn_ctx_output_array_open(ctx, "RESULT", 2);
  grn_ctx_output_cstr(ctx, arg_str);
  grn_ctx_output_int64(ctx, arg_length);
  grn_ctx_output_array_close(ctx);

  return NULL;
}

/* lib/proc.c */
#define GRN_STRLEN(s) ((s) ? strlen(s) : 0)
#define DEF_VAR(v,name_str) do {\
(v).name = (name_str);\
(v).name_size = GRN_STRLEN(name_str);\
GRN_TEXT_INIT(&(v).value, 0);\
} while (0)

#define DEF_COMMAND(name, func, nvars, vars)\
(grn_proc_create(ctx, (name), (sizeof(name) - 1),\
GRN_PROC_COMMAND, (func), NULL, NULL, (nvars), (vars)))

grn_rc
GRN_PLUGIN_INIT(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  grn_expr_var vars[1];
  DEF_VAR(vars[0], "echo");
  DEF_COMMAND("echo", command_echo, 1, vars);

  return ctx->rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

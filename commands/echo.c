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
  grn_obj *var;

  char *input = NULL;
  unsigned int input_len = 0;

  var = grn_plugin_proc_get_var(ctx, user_data, "input", -1);

  GRN_PLUGIN_LOG(ctx, GRN_LOG_NOTICE, "[echo] input = %.*s",
                 GRN_TEXT_LEN(var), GRN_TEXT_VALUE(var));

  if(GRN_TEXT_LEN(var) != 0) {
    input = GRN_TEXT_VALUE(var);
    input_len = GRN_TEXT_LEN(var);
  }

  grn_ctx_output_array_open(ctx, "RESULT", 2);
  grn_ctx_output_cstr(ctx, input);
  grn_ctx_output_int64(ctx, input_len);
  grn_ctx_output_array_close(ctx);

  return NULL;
}

grn_rc
GRN_PLUGIN_INIT(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  grn_expr_var vars[1];

  grn_plugin_expr_var_init(ctx, &vars[0], "input", -1);
  grn_plugin_command_create(ctx, "echo", -1, command_echo, 1, vars);

  return ctx->rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

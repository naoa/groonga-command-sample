#include <string.h>
#include <stdlib.h>
#include <groonga/plugin.h>

#ifdef __GNUC__
# define GNUC_UNUSED __attribute__((__unused__))
#else
# define GNUC_UNUSED
#endif

/* lib/db.h include/groonga/plugin.h */
#define GRN_PROC_GET_VAR_BY_OFFSET(offset) (grn_plugin_proc_get_var_by_offset(ctx, user_data, offset))

/* lib/proc.c */
#define VAR GRN_PROC_GET_VAR_BY_OFFSET

/* lib/output.h */
#define GRN_OUTPUT_ARRAY_OPEN(name,nelements) \
(grn_ctx_output_array_open(ctx, name, nelements))
#define GRN_OUTPUT_ARRAY_CLOSE() \
(grn_ctx_output_array_close(ctx))
#define GRN_OUTPUT_MAP_OPEN(name,nelements) \
(grn_ctx_output_map_open(ctx, name, nelements))
#define GRN_OUTPUT_MAP_CLOSE() \
(grn_ctx_output_map_close(ctx))
#define GRN_OUTPUT_INT32(value) \
(grn_ctx_output_int32(ctx, value))
#define GRN_OUTPUT_INT64(value) \
(grn_ctx_output_int64(ctx, value))
#define GRN_OUTPUT_FLOAT(value) \
(grn_ctx_output_float(ctx, value))
#define GRN_OUTPUT_CSTR(value)\
(grn_ctx_output_cstr(ctx, value))
#define GRN_OUTPUT_STR(value,value_len)\
(grn_ctx_output_str(ctx, value, value_len))
#define GRN_OUTPUT_BOOL(value)\
(grn_ctx_output_bool(ctx, value))
#define GRN_OUTPUT_OBJ(obj,format)\

static grn_obj *
command_echo(grn_ctx *ctx, GNUC_UNUSED int nargs, GNUC_UNUSED grn_obj **args,
                  grn_user_data *user_data)
{
  const char *arg_str = GRN_TEXT_VALUE(VAR(0));
  int arg_length = GRN_TEXT_LEN(VAR(0));

  GRN_OUTPUT_ARRAY_OPEN("RESULT", 2);
  GRN_OUTPUT_CSTR(arg_str);
  GRN_OUTPUT_INT64(arg_length);
  GRN_OUTPUT_ARRAY_CLOSE();

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

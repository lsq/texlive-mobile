/*4:*/
#line 115 "./mplibdir/mp.w"

#ifndef MPMP_H
#define MPMP_H 1
#include "avl.h"
#include "mplib.h"
#include <setjmp.h> 
typedef struct psout_data_struct*psout_data;
typedef struct svgout_data_struct*svgout_data;
typedef struct pngout_data_struct*pngout_data;
#ifndef HAVE_BOOLEAN
typedef int boolean;
#endif
#ifndef INTEGER_TYPE
typedef int integer;
#endif
/*167:*/
#line 2750 "./mplibdir/mp.w"

extern void mp_xfree(void*x);
extern void*mp_xrealloc(MP mp,void*p,size_t nmem,size_t size);
extern void*mp_xmalloc(MP mp,size_t nmem,size_t size);
extern void mp_do_snprintf(char*str,int size,const char*fmt,...);
extern void*do_alloc_node(MP mp,size_t size);

/*:167*/
#line 130 "./mplibdir/mp.w"
;
/*187:*/
#line 3145 "./mplibdir/mp.w"

typedef enum{
mp_start_tex= 1,
mp_etex_marker,
mp_mpx_break,
mp_if_test,
mp_fi_or_else,
mp_input,
mp_iteration,
mp_repeat_loop,
mp_exit_test,
mp_relax,
mp_scan_tokens,
mp_runscript,
mp_maketext,
mp_expand_after,
mp_defined_macro,
mp_save_command,
mp_interim_command,
mp_let_command,
mp_new_internal,
mp_macro_def,
mp_ship_out_command,
mp_add_to_command,
mp_bounds_command,
mp_tfm_command,
mp_protection_command,
mp_show_command,
mp_mode_command,
mp_random_seed,
mp_message_command,
mp_every_job_command,
mp_delimiters,
mp_special_command,

mp_write_command,
mp_type_name,
mp_left_delimiter,
mp_begin_group,
mp_nullary,
mp_unary,
mp_str_op,
mp_cycle,
mp_primary_binary,
mp_capsule_token,
mp_string_token,
mp_internal_quantity,
mp_tag_token,
mp_numeric_token,
mp_plus_or_minus,
mp_tertiary_secondary_macro,
mp_tertiary_binary,
mp_left_brace,
mp_path_join,
mp_ampersand,
mp_expression_tertiary_macro,
mp_expression_binary,
mp_equals,
mp_and_command,
mp_secondary_primary_macro,
mp_slash,
mp_secondary_binary,
mp_param_type,
mp_controls,
mp_tension,
mp_at_least,
mp_curl_command,
mp_macro_special,
mp_right_delimiter,
mp_left_bracket,
mp_right_bracket,
mp_right_brace,
mp_with_option,
mp_thing_to_add,

mp_of_token,
mp_to_token,
mp_step_token,
mp_until_token,
mp_within_token,
mp_lig_kern_token,

mp_assignment,
mp_skip_to,
mp_bchar_label,
mp_double_colon,
mp_colon,

mp_comma,
mp_semicolon,
mp_end_group,
mp_stop,
mp_outer_tag,
mp_undefined_cs,
}mp_command_code;

/*:187*//*188:*/
#line 3255 "./mplibdir/mp.w"

typedef enum{
mp_undefined= 0,
mp_vacuous,
mp_boolean_type,
mp_unknown_boolean,
mp_string_type,
mp_unknown_string,
mp_pen_type,
mp_unknown_pen,
mp_path_type,
mp_unknown_path,
mp_picture_type,
mp_unknown_picture,
mp_transform_type,
mp_color_type,
mp_cmykcolor_type,
mp_pair_type,
mp_numeric_type,
mp_known,
mp_dependent,
mp_proto_dependent,
mp_independent,
mp_token_list,
mp_structured,
mp_unsuffixed_macro,
mp_suffixed_macro,

mp_symbol_node,
mp_token_node_type,
mp_value_node_type,
mp_attr_node_type,
mp_subscr_node_type,
mp_pair_node_type,
mp_transform_node_type,
mp_color_node_type,
mp_cmykcolor_node_type,

mp_fill_node_type,
mp_stroked_node_type,
mp_text_node_type,
mp_start_clip_node_type,
mp_start_bounds_node_type,
mp_stop_clip_node_type,
mp_stop_bounds_node_type,
mp_dash_node_type,
mp_dep_node_type,
mp_if_node_type,
mp_edge_header_node_type,
}mp_variable_type;

/*:188*//*191:*/
#line 3470 "./mplibdir/mp.w"

typedef enum{
mp_root= 0,
mp_saved_root,
mp_structured_root,
mp_subscr,
mp_attr,
mp_x_part_sector,
mp_y_part_sector,
mp_xx_part_sector,
mp_xy_part_sector,
mp_yx_part_sector,
mp_yy_part_sector,
mp_red_part_sector,
mp_green_part_sector,
mp_blue_part_sector,
mp_cyan_part_sector,
mp_magenta_part_sector,
mp_yellow_part_sector,
mp_black_part_sector,
mp_grey_part_sector,
mp_capsule,
mp_token,

mp_normal_sym,
mp_internal_sym,
mp_macro_sym,
mp_expr_sym,
mp_suffix_sym,
mp_text_sym,
/*192:*/
#line 3518 "./mplibdir/mp.w"

mp_true_code,
mp_false_code,
mp_null_picture_code,
mp_null_pen_code,
mp_read_string_op,
mp_pen_circle,
mp_normal_deviate,
mp_read_from_op,
mp_close_from_op,
mp_odd_op,
mp_known_op,
mp_unknown_op,
mp_not_op,
mp_decimal,
mp_reverse,
mp_make_path_op,
mp_make_pen_op,
mp_oct_op,
mp_hex_op,
mp_ASCII_op,
mp_char_op,
mp_length_op,
mp_turning_op,
mp_color_model_part,
mp_x_part,
mp_y_part,
mp_xx_part,
mp_xy_part,
mp_yx_part,
mp_yy_part,
mp_red_part,
mp_green_part,
mp_blue_part,
mp_cyan_part,
mp_magenta_part,
mp_yellow_part,
mp_black_part,
mp_grey_part,
mp_font_part,
mp_text_part,
mp_path_part,
mp_pen_part,
mp_dash_part,
mp_prescript_part,
mp_postscript_part,
mp_sqrt_op,
mp_m_exp_op,
mp_m_log_op,
mp_sin_d_op,
mp_cos_d_op,
mp_floor_op,
mp_uniform_deviate,
mp_char_exists_op,
mp_font_size,
mp_ll_corner_op,
mp_lr_corner_op,
mp_ul_corner_op,
mp_ur_corner_op,
mp_arc_length,
mp_angle_op,
mp_cycle_op,
mp_filled_op,
mp_stroked_op,
mp_textual_op,
mp_clipped_op,
mp_bounded_op,
mp_plus,
mp_minus,
mp_times,
mp_over,
mp_pythag_add,
mp_pythag_sub,
mp_or_op,
mp_and_op,
mp_less_than,
mp_less_or_equal,
mp_greater_than,
mp_greater_or_equal,
mp_equal_to,
mp_unequal_to,
mp_concatenate,
mp_rotated_by,
mp_slanted_by,
mp_scaled_by,
mp_shifted_by,
mp_transformed_by,
mp_x_scaled,
mp_y_scaled,
mp_z_scaled,
mp_in_font,
mp_intersect,
mp_double_dot,
mp_substring_of,
mp_subpath_of,
mp_direction_time_of,
mp_point_of,
mp_precontrol_of,
mp_postcontrol_of,
mp_pen_offset_of,
mp_arc_time_of,
mp_version,
mp_envelope_of,
mp_glyph_infont,
mp_kern_flag

/*:192*/
#line 3500 "./mplibdir/mp.w"

}mp_name_type_type;

/*:191*/
#line 131 "./mplibdir/mp.w"
;
/*33:*/
#line 731 "./mplibdir/mp.w"

typedef unsigned char ASCII_code;

/*:33*//*34:*/
#line 739 "./mplibdir/mp.w"

typedef unsigned char text_char;

/*:34*//*41:*/
#line 827 "./mplibdir/mp.w"

typedef unsigned char eight_bits;

/*:41*//*163:*/
#line 2693 "./mplibdir/mp.w"

typedef struct mp_value_node_data*mp_value_node;
typedef struct mp_node_data*mp_node;
typedef struct mp_symbol_entry*mp_sym;
typedef short quarterword;
typedef int halfword;
typedef struct{
integer scale;
integer serial;
}mp_independent_data;
typedef struct{
mp_independent_data indep;
mp_number n;
mp_string str;
mp_sym sym;
mp_node node;
mp_knot p;
}mp_value_data;
typedef struct{
mp_variable_type type;
mp_value_data data;
}mp_value;
typedef struct{
quarterword b0,b1,b2,b3;
}four_quarters;
typedef union{
integer sc;
four_quarters qqqq;
}font_data;


/*:163*//*194:*/
#line 3947 "./mplibdir/mp.w"

enum mp_given_internal{
mp_output_template= 1,
mp_output_filename,
mp_output_format,
mp_output_format_options,
mp_number_system,
mp_number_precision,
mp_job_name,

mp_tracing_titles,
mp_tracing_equations,
mp_tracing_capsules,
mp_tracing_choices,
mp_tracing_specs,
mp_tracing_commands,
mp_tracing_restores,
mp_tracing_macros,
mp_tracing_output,
mp_tracing_stats,
mp_tracing_lost_chars,
mp_tracing_online,
mp_year,
mp_month,
mp_day,
mp_time,
mp_hour,
mp_minute,
mp_char_code,
mp_char_ext,
mp_char_wd,
mp_char_ht,
mp_char_dp,
mp_char_ic,
mp_design_size,
mp_pausing,
mp_showstopping,
mp_fontmaking,
mp_linejoin,
mp_linecap,
mp_miterlimit,
mp_warning_check,
mp_boundary_char,
mp_prologues,
mp_true_corners,
mp_default_color_model,
mp_restore_clip_color,
mp_procset,
mp_hppp,
mp_vppp,
mp_gtroffmode,
};
typedef struct{
mp_value v;
char*intname;
}mp_internal;


/*:194*//*217:*/
#line 4520 "./mplibdir/mp.w"

typedef struct mp_symbol_entry{
halfword type;
mp_value v;
mp_string text;
void*parent;
}mp_symbol_entry;

/*:217*//*252:*/
#line 5483 "./mplibdir/mp.w"

typedef enum{
mp_general_macro,
mp_primary_macro,
mp_secondary_macro,
mp_tertiary_macro,
mp_expr_macro,
mp_of_macro,
mp_suffix_macro,
mp_text_macro,
mp_expr_param,
mp_suffix_param,
mp_text_param
}mp_macro_info;

/*:252*//*294:*/
#line 6789 "./mplibdir/mp.w"

typedef struct mp_save_data{
quarterword type;
mp_internal value;
struct mp_save_data*link;
}mp_save_data;

/*:294*//*387:*/
#line 9179 "./mplibdir/mp.w"

enum mp_bb_code{
mp_x_code= 0,
mp_y_code
};

/*:387*//*482:*/
#line 11565 "./mplibdir/mp.w"

typedef struct mp_dash_node_data*mp_dash_node;

/*:482*//*677:*/
#line 17023 "./mplibdir/mp.w"

typedef struct{
char*long_name_field;
halfword start_field,loc_field,limit_field;
mp_node nstart_field,nloc_field;
mp_string name_field;
quarterword index_field;
}in_state_record;

/*:677*//*751:*/
#line 18659 "./mplibdir/mp.w"

typedef struct mp_subst_list_item{
mp_name_type_type info_mod;
quarterword value_mod;
mp_sym info;
halfword value_data;
struct mp_subst_list_item*link;
}mp_subst_list_item;

/*:751*//*829:*/
#line 20406 "./mplibdir/mp.w"

typedef struct mp_loop_data{
mp_sym var;
mp_node info;
mp_node type;

mp_node list;
mp_node list_start;
mp_number old_value;
mp_number value;
mp_number step_size;
mp_number final_value;
struct mp_loop_data*link;
}mp_loop_data;

/*:829*//*900:*/
#line 21651 "./mplibdir/mp.w"

typedef unsigned int readf_index;
typedef unsigned int write_index;

/*:900*//*1066:*/
#line 29691 "./mplibdir/mp.w"

typedef struct File{
FILE*f;
}File;

/*:1066*//*1234:*/
#line 33430 "./mplibdir/mp.w"

typedef unsigned int font_number;

/*:1234*/
#line 132 "./mplibdir/mp.w"
;
/*23:*/
#line 645 "./mplibdir/mp.w"

#define bistack_size 1500       


/*:23*/
#line 133 "./mplibdir/mp.w"
;
typedef struct MP_instance{
/*26:*/
#line 659 "./mplibdir/mp.w"

int error_line;
int half_error_line;

int halt_on_error;
int max_print_line;
void*userdata;
char*banner;
int ini_version;

/*:26*//*43:*/
#line 857 "./mplibdir/mp.w"

mp_file_finder find_file;
mp_file_opener open_file;
mp_script_runner run_script;
mp_text_maker make_text;
mp_file_reader read_ascii_file;
mp_binfile_reader read_binary_file;
mp_file_closer close_file;
mp_file_eoftest eof_file;
mp_file_flush flush_file;
mp_file_writer write_ascii_file;
mp_binfile_writer write_binary_file;

/*:43*//*50:*/
#line 942 "./mplibdir/mp.w"

int print_found_names;

/*:50*//*52:*/
#line 960 "./mplibdir/mp.w"

int file_line_error_style;

/*:52*//*68:*/
#line 1201 "./mplibdir/mp.w"

char*command_line;

/*:68*//*101:*/
#line 1794 "./mplibdir/mp.w"

int interaction;
int noninteractive;
int extensions;

/*:101*//*121:*/
#line 2029 "./mplibdir/mp.w"

mp_editor_cmd run_editor;

/*:121*//*153:*/
#line 2527 "./mplibdir/mp.w"

int random_seed;

/*:153*//*165:*/
#line 2737 "./mplibdir/mp.w"

int math_mode;

/*:165*//*197:*/
#line 4036 "./mplibdir/mp.w"

int troff_mode;

/*:197*//*861:*/
#line 21044 "./mplibdir/mp.w"

char*mem_name;

/*:861*//*874:*/
#line 21239 "./mplibdir/mp.w"

char*job_name;

/*:874*//*895:*/
#line 21604 "./mplibdir/mp.w"

mp_makempx_cmd run_make_mpx;

/*:895*//*1285:*/
#line 34431 "./mplibdir/mp.w"

mp_backend_writer shipout_backend;

/*:1285*/
#line 135 "./mplibdir/mp.w"

/*14:*/
#line 306 "./mplibdir/mp.w"

void*math;

/*:14*//*25:*/
#line 652 "./mplibdir/mp.w"

int pool_size;

int max_in_open;

int param_size;

/*:25*//*29:*/
#line 694 "./mplibdir/mp.w"

integer bad;

/*:29*//*37:*/
#line 753 "./mplibdir/mp.w"

ASCII_code xord[256];
text_char xchr[256];

/*:37*//*49:*/
#line 935 "./mplibdir/mp.w"

char*name_of_file;

/*:49*//*62:*/
#line 1102 "./mplibdir/mp.w"

size_t buf_size;

ASCII_code*buffer;
size_t first;
size_t last;
size_t max_buf_stack;

/*:62*//*67:*/
#line 1176 "./mplibdir/mp.w"

void*term_in;
void*term_out;
void*err_out;

/*:67*//*75:*/
#line 1337 "./mplibdir/mp.w"

avl_tree strings;
unsigned char*cur_string;
size_t cur_length;
size_t cur_string_size;

/*:75*//*78:*/
#line 1351 "./mplibdir/mp.w"

integer pool_in_use;
integer max_pl_used;
integer strs_in_use;
integer max_strs_used;


/*:78*//*79:*/
#line 1410 "./mplibdir/mp.w"

void*log_file;
void*output_file;
unsigned int selector;
integer tally;
unsigned int term_offset;

unsigned int file_offset;

ASCII_code*trick_buf;
integer trick_count;
integer first_count;

/*:79*//*107:*/
#line 1870 "./mplibdir/mp.w"

int history;
int error_count;

/*:107*//*111:*/
#line 1899 "./mplibdir/mp.w"

boolean use_err_help;
mp_string err_help;

/*:111*//*113:*/
#line 1915 "./mplibdir/mp.w"

jmp_buf*jump_buf;

/*:113*//*140:*/
#line 2365 "./mplibdir/mp.w"

integer interrupt;
boolean OK_to_interrupt;
integer run_state;
boolean finished;
boolean reading_preload;

/*:140*//*144:*/
#line 2424 "./mplibdir/mp.w"

boolean arith_error;

/*:144*//*152:*/
#line 2523 "./mplibdir/mp.w"

mp_number randoms[55];
int j_random;

/*:152*//*168:*/
#line 2765 "./mplibdir/mp.w"

mp_node token_nodes;
int num_token_nodes;
mp_node pair_nodes;
int num_pair_nodes;
mp_knot knot_nodes;
int num_knot_nodes;
mp_node value_nodes;
int num_value_nodes;
mp_node symbolic_nodes;
int num_symbolic_nodes;

/*:168*//*177:*/
#line 2917 "./mplibdir/mp.w"

size_t var_used;
size_t var_used_max;

/*:177*//*183:*/
#line 3059 "./mplibdir/mp.w"

mp_dash_node null_dash;
mp_value_node dep_head;
mp_node inf_val;
mp_node zero_val;
mp_node temp_val;
mp_node end_attr;
mp_node bad_vardef;
mp_node temp_head;
mp_node hold_head;
mp_node spec_head;

/*:183*//*196:*/
#line 4031 "./mplibdir/mp.w"

mp_internal*internal;
int int_ptr;
int max_internal;

/*:196*//*210:*/
#line 4342 "./mplibdir/mp.w"

unsigned int old_setting;

/*:210*//*212:*/
#line 4382 "./mplibdir/mp.w"

#define digit_class 0 
int char_class[256];

/*:212*//*218:*/
#line 4528 "./mplibdir/mp.w"

integer st_count;
avl_tree symbols;
avl_tree frozen_symbols;
mp_sym frozen_bad_vardef;
mp_sym frozen_colon;
mp_sym frozen_end_def;
mp_sym frozen_end_for;
mp_sym frozen_end_group;
mp_sym frozen_etex;
mp_sym frozen_fi;
mp_sym frozen_inaccessible;
mp_sym frozen_left_bracket;
mp_sym frozen_mpx_break;
mp_sym frozen_repeat_loop;
mp_sym frozen_right_delimiter;
mp_sym frozen_semicolon;
mp_sym frozen_slash;
mp_sym frozen_undefined;
mp_sym frozen_dump;


/*:218*//*227:*/
#line 4657 "./mplibdir/mp.w"

mp_sym id_lookup_test;

/*:227*//*295:*/
#line 6796 "./mplibdir/mp.w"

mp_save_data*save_ptr;

/*:295*//*329:*/
#line 7497 "./mplibdir/mp.w"

mp_knot path_tail;

/*:329*//*344:*/
#line 7811 "./mplibdir/mp.w"

int path_size;
mp_number*delta_x;
mp_number*delta_y;
mp_number*delta;
mp_number*psi;

/*:344*//*349:*/
#line 7966 "./mplibdir/mp.w"

mp_number*theta;
mp_number*uu;
mp_number*vv;
mp_number*ww;

/*:349*//*371:*/
#line 8576 "./mplibdir/mp.w"

mp_number st;
mp_number ct;
mp_number sf;
mp_number cf;

/*:371*//*388:*/
#line 9191 "./mplibdir/mp.w"

mp_number bbmin[mp_y_code+1];
mp_number bbmax[mp_y_code+1];


/*:388*//*434:*/
#line 10447 "./mplibdir/mp.w"

mp_number half_cos[8];
mp_number d_cos[8];

/*:434*//*451:*/
#line 10774 "./mplibdir/mp.w"

mp_number cur_x;
mp_number cur_y;

/*:451*//*547:*/
#line 13144 "./mplibdir/mp.w"

integer spec_offset;

/*:547*//*549:*/
#line 13245 "./mplibdir/mp.w"

mp_knot spec_p1;
mp_knot spec_p2;

/*:549*//*608:*/
#line 15122 "./mplibdir/mp.w"

unsigned int tol_step;

/*:608*//*609:*/
#line 15189 "./mplibdir/mp.w"

mp_number*bisect_stack;
integer bisect_ptr;

/*:609*//*614:*/
#line 15276 "./mplibdir/mp.w"

mp_number cur_t;
mp_number cur_tt;
integer time_to_go;
mp_number max_t;

/*:614*//*618:*/
#line 15395 "./mplibdir/mp.w"

mp_number delx;
mp_number dely;
integer tol;
integer uv;
integer xy;
integer three_l;
mp_number appr_t;
mp_number appr_tt;

/*:618*//*627:*/
#line 15631 "./mplibdir/mp.w"

integer serial_no;

/*:627*//*638:*/
#line 15831 "./mplibdir/mp.w"

boolean fix_needed;
boolean watch_coefs;
mp_value_node dep_final;

/*:638*//*671:*/
#line 16970 "./mplibdir/mp.w"

mp_node cur_mod_;

/*:671*//*678:*/
#line 17032 "./mplibdir/mp.w"

in_state_record*input_stack;
integer input_ptr;
integer max_in_stack;
in_state_record cur_input;
int stack_size;

/*:678*//*683:*/
#line 17139 "./mplibdir/mp.w"

integer in_open;
integer in_open_max;
unsigned int open_parens;
void**input_file;
integer*line_stack;
char**inext_stack;
char**iname_stack;
char**iarea_stack;
mp_string*mpx_name;

/*:683*//*689:*/
#line 17268 "./mplibdir/mp.w"

mp_node*param_stack;
integer param_ptr;
integer max_param_stack;

/*:689*//*695:*/
#line 17323 "./mplibdir/mp.w"

integer file_ptr;

/*:695*//*723:*/
#line 17921 "./mplibdir/mp.w"

#define tex_flushing 7 
integer scanner_status;
mp_sym warning_info;

integer warning_line;
mp_node warning_info_node;

/*:723*//*734:*/
#line 18287 "./mplibdir/mp.w"

boolean force_eof;

/*:734*//*766:*/
#line 19105 "./mplibdir/mp.w"

mp_sym bg_loc;
mp_sym eg_loc;

/*:766*//*770:*/
#line 19159 "./mplibdir/mp.w"

int expand_depth_count;
int expand_depth;

/*:770*//*815:*/
#line 20122 "./mplibdir/mp.w"

mp_node cond_ptr;
integer if_limit;
quarterword cur_if;
integer if_line;

/*:815*//*830:*/
#line 20421 "./mplibdir/mp.w"

mp_loop_data*loop_ptr;

/*:830*//*849:*/
#line 20869 "./mplibdir/mp.w"

char*cur_name;
char*cur_area;
char*cur_ext;

/*:849*//*852:*/
#line 20897 "./mplibdir/mp.w"

integer area_delimiter;

integer ext_delimiter;
boolean quoted_filename;

/*:852*//*873:*/
#line 21235 "./mplibdir/mp.w"

boolean log_opened;
char*log_name;

/*:873*//*901:*/
#line 21655 "./mplibdir/mp.w"

readf_index max_read_files;
void**rd_file;
char**rd_fname;
readf_index read_files;
write_index max_write_files;
void**wr_file;
char**wr_fname;
write_index write_files;

/*:901*//*907:*/
#line 21798 "./mplibdir/mp.w"

mp_value cur_exp;

/*:907*//*934:*/
#line 22726 "./mplibdir/mp.w"

mp_number max_c[mp_proto_dependent+1];
mp_value_node max_ptr[mp_proto_dependent+1];
mp_value_node max_link[mp_proto_dependent+1];


/*:934*//*937:*/
#line 22767 "./mplibdir/mp.w"

int var_flag;

/*:937*//*994:*/
#line 26456 "./mplibdir/mp.w"

mp_string eof_line;

/*:994*//*1007:*/
#line 27639 "./mplibdir/mp.w"

mp_number txx;
mp_number txy;
mp_number tyx;
mp_number tyy;
mp_number tx;
mp_number ty;

/*:1007*//*1065:*/
#line 29684 "./mplibdir/mp.w"

mp_run_data run_data;

/*:1065*//*1138:*/
#line 31306 "./mplibdir/mp.w"

quarterword last_add_type;


/*:1138*//*1149:*/
#line 31565 "./mplibdir/mp.w"

mp_sym start_sym;

/*:1149*//*1158:*/
#line 31696 "./mplibdir/mp.w"

boolean long_help_seen;

/*:1158*//*1166:*/
#line 31853 "./mplibdir/mp.w"

void*tfm_file;
char*metric_file_name;

/*:1166*//*1175:*/
#line 32112 "./mplibdir/mp.w"

#define TFM_ITEMS 257
eight_bits bc;
eight_bits ec;
mp_node tfm_width[TFM_ITEMS];
mp_node tfm_height[TFM_ITEMS];
mp_node tfm_depth[TFM_ITEMS];
mp_node tfm_ital_corr[TFM_ITEMS];
boolean char_exists[TFM_ITEMS];
int char_tag[TFM_ITEMS];
int char_remainder[TFM_ITEMS];
char*header_byte;
int header_last;
int header_size;
four_quarters*lig_kern;
short nl;
mp_number*kern;
short nk;
four_quarters exten[TFM_ITEMS];
short ne;
mp_number*param;
short np;
short nw;
short nh;
short nd;
short ni;
short skip_table[TFM_ITEMS];
boolean lk_started;
integer bchar;
short bch_label;
short ll;
short lll;
short label_loc[257];
eight_bits label_char[257];
short label_ptr;

/*:1175*//*1205:*/
#line 32814 "./mplibdir/mp.w"

mp_number perturbation;
integer excess;

/*:1205*//*1213:*/
#line 32964 "./mplibdir/mp.w"

mp_node dimen_head[5];

/*:1213*//*1219:*/
#line 33111 "./mplibdir/mp.w"

mp_number max_tfm_dimen;
integer tfm_changed;

/*:1219*//*1233:*/
#line 33421 "./mplibdir/mp.w"

void*tfm_infile;

/*:1233*//*1235:*/
#line 33437 "./mplibdir/mp.w"

font_number font_max;
size_t font_mem_size;
font_data*font_info;
char**font_enc_name;
boolean*font_ps_name_fixed;
size_t next_fmem;
font_number last_fnum;
integer*font_dsize;
char**font_name;
char**font_ps_name;
font_number last_ps_fnum;
eight_bits*font_bc;
eight_bits*font_ec;
int*char_base;
int*width_base;
int*height_base;
int*depth_base;
mp_node*font_sizes;

/*:1235*//*1255:*/
#line 33753 "./mplibdir/mp.w"

integer ten_pow[10];
integer scaled_out;

/*:1255*//*1263:*/
#line 34021 "./mplibdir/mp.w"

char*first_file_name;
char*last_file_name;
integer first_output_code;
integer last_output_code;

integer total_shipped;

/*:1263*//*1271:*/
#line 34094 "./mplibdir/mp.w"

mp_node last_pending;


/*:1271*//*1287:*/
#line 34437 "./mplibdir/mp.w"

psout_data ps;
svgout_data svg;
pngout_data png;

/*:1287*//*1290:*/
#line 34464 "./mplibdir/mp.w"

void*mem_file;

/*:1290*/
#line 136 "./mplibdir/mp.w"

}MP_instance;
/*10:*/
#line 259 "./mplibdir/mp.w"

/*869:*/
#line 21191 "./mplibdir/mp.w"

void mp_str_scan_file(MP mp,mp_string s);

/*:869*//*871:*/
#line 21211 "./mplibdir/mp.w"

extern void mp_ptr_scan_file(MP mp,char*s);

/*:871*/
#line 260 "./mplibdir/mp.w"



/*:10*//*85:*/
#line 1481 "./mplibdir/mp.w"

void mp_print(MP mp,const char*s);
void mp_printf(MP mp,const char*ss,...);
void mp_print_ln(MP mp);
void mp_print_char(MP mp,ASCII_code k);
void mp_print_str(MP mp,mp_string s);
void mp_print_nl(MP mp,const char*s);
void mp_print_two(MP mp,mp_number x,mp_number y);

/*:85*//*95:*/
#line 1712 "./mplibdir/mp.w"

void mp_print_int(MP mp,integer n);
void mp_print_pointer(MP mp,void*n);

/*:95*//*110:*/
#line 1896 "./mplibdir/mp.w"

void mp_normalize_selector(MP mp);

/*:110*//*115:*/
#line 1929 "./mplibdir/mp.w"

void mp_jump_out(MP mp);

/*:115*//*136:*/
#line 2293 "./mplibdir/mp.w"

void mp_overflow(MP mp,const char*s,integer n);


/*:136*//*138:*/
#line 2324 "./mplibdir/mp.w"

void mp_confusion(MP mp,const char*s);

/*:138*//*156:*/
#line 2547 "./mplibdir/mp.w"

void mp_new_randoms(MP mp);

/*:156*//*174:*/
#line 2875 "./mplibdir/mp.w"

#  define mp_snprintf (void)snprintf

/*:174*//*182:*/
#line 3050 "./mplibdir/mp.w"

void mp_free_node(MP mp,mp_node p,size_t siz);
void mp_free_symbolic_node(MP mp,mp_node p);
void mp_free_value_node(MP mp,mp_node p);

/*:182*//*333:*/
#line 7594 "./mplibdir/mp.w"

void mp_make_choices(MP mp,mp_knot knots);

/*:333*//*860:*/
#line 21041 "./mplibdir/mp.w"

void mp_pack_file_name(MP mp,const char*n,const char*a,const char*e);

/*:860*//*878:*/
#line 21284 "./mplibdir/mp.w"

void mp_pack_job_name(MP mp,const char*s);

/*:878*//*880:*/
#line 21306 "./mplibdir/mp.w"

void mp_prompt_file_name(MP mp,const char*s,const char*e);

/*:880*//*1104:*/
#line 30397 "./mplibdir/mp.w"

void mp_grow_internals(MP mp,int l);

/*:1104*//*1239:*/
#line 33521 "./mplibdir/mp.w"

void mp_reallocate_fonts(MP mp,font_number l);


/*:1239*//*1258:*/
#line 33777 "./mplibdir/mp.w"

void mp_open_output_file(MP mp);
char*mp_get_output_file_name(MP mp);
char*mp_set_output_file_name(MP mp,integer c);

/*:1258*//*1261:*/
#line 34002 "./mplibdir/mp.w"

void mp_store_true_output_filename(MP mp,int c);

/*:1261*//*1269:*/
#line 34082 "./mplibdir/mp.w"

boolean mp_has_font_size(MP mp,font_number f);

/*:1269*/
#line 138 "./mplibdir/mp.w"

/*6:*/
#line 185 "./mplibdir/mp.w"

#define DEBUG 0
#if DEBUG
#define debug_number(A) printf("%d: %s=%.32f (%d)\n", __LINE__, #A, number_to_double(A), number_to_scaled(A))
#else
#define debug_number(A)
#endif
#if DEBUG> 1
void do_debug_printf(MP mp,const char*prefix,const char*fmt,...);
#  define debug_printf(a1,a2,a3) do_debug_printf(mp, "", a1,a2,a3)
#  define FUNCTION_TRACE1(a1) do_debug_printf(mp, "FTRACE: ", a1)
#  define FUNCTION_TRACE2(a1,a2) do_debug_printf(mp, "FTRACE: ", a1,a2)
#  define FUNCTION_TRACE3(a1,a2,a3) do_debug_printf(mp, "FTRACE: ", a1,a2,a3)
#  define FUNCTION_TRACE3X(a1,a2,a3) (void)mp
#  define FUNCTION_TRACE4(a1,a2,a3,a4) do_debug_printf(mp, "FTRACE: ", a1,a2,a3,a4)
#else
#  define debug_printf(a1,a2,a3)
#  define FUNCTION_TRACE1(a1) (void)mp
#  define FUNCTION_TRACE2(a1,a2) (void)mp
#  define FUNCTION_TRACE3(a1,a2,a3) (void)mp
#  define FUNCTION_TRACE3X(a1,a2,a3) (void)mp
#  define FUNCTION_TRACE4(a1,a2,a3,a4) (void)mp
#endif

/*:6*//*36:*/
#line 749 "./mplibdir/mp.w"

#define xchr(A) mp->xchr[(A)]
#define xord(A) mp->xord[(A)]

/*:36*//*69:*/
#line 1218 "./mplibdir/mp.w"

#define update_terminal()  (mp->flush_file)(mp,mp->term_out)      
#define clear_terminal()          
#define wake_up_terminal() (mp->flush_file)(mp,mp->term_out)


/*:69*//*84:*/
#line 1464 "./mplibdir/mp.w"

#define mp_fputs(b,f) (mp->write_ascii_file)(mp,f,b)
#define wterm(A)     mp_fputs((A), mp->term_out)
#define wterm_chr(A) { unsigned char ss[2]; ss[0]= (A); ss[1]= '\0'; wterm((char *)ss);}
#define wterm_cr     mp_fputs("\n", mp->term_out)
#define wterm_ln(A)  { wterm_cr; mp_fputs((A), mp->term_out); }
#define wlog(A)        mp_fputs((A), mp->log_file)
#define wlog_chr(A)  { unsigned char ss[2]; ss[0]= (A); ss[1]= '\0'; wlog((char *)ss);}
#define wlog_cr      mp_fputs("\n", mp->log_file)
#define wlog_ln(A)   { wlog_cr; mp_fputs((A), mp->log_file); }


/*:84*//*176:*/
#line 2896 "./mplibdir/mp.w"

#define NODE_BODY                       \
  mp_variable_type type;                \
  mp_name_type_type name_type;          \
  unsigned short has_number;  \
  struct mp_node_data *link
typedef struct mp_node_data{
NODE_BODY;
mp_value_data data;
}mp_node_data;
typedef struct mp_node_data*mp_symbolic_node;

/*:176*//*195:*/
#line 4005 "./mplibdir/mp.w"

#define internal_value(A) mp->internal[(A)].v.data.n
#define set_internal_from_number(A,B) do { \
  number_clone (internal_value ((A)),(B));\
} while (0)
#define internal_string(A) (mp_string)mp->internal[(A)].v.data.str
#define set_internal_string(A,B) mp->internal[(A)].v.data.str= (B)
#define internal_name(A) mp->internal[(A)].intname
#define set_internal_name(A,B) mp->internal[(A)].intname= (B)
#define internal_type(A) (mp_variable_type)mp->internal[(A)].v.type
#define set_internal_type(A,B) mp->internal[(A)].v.type= (B)
#define set_internal_from_cur_exp(A) do { \
  if (internal_type ((A)) == mp_string_type) { \
      add_str_ref (cur_exp_str ()); \
      set_internal_string ((A), cur_exp_str ()); \
  } else { \
      set_internal_from_number ((A), cur_exp_value_number ()); \
  } \
} while (0)



/*:195*//*239:*/
#line 5123 "./mplibdir/mp.w"

typedef struct mp_node_data*mp_token_node;

/*:239*//*255:*/
#line 5617 "./mplibdir/mp.w"

typedef struct mp_value_node_data{
NODE_BODY;
mp_value_data data;
mp_number subscript_;
mp_sym hashloc_;
mp_node parent_;
mp_node attr_head_;
mp_node subscr_head_;
}mp_value_node_data;

/*:255*//*266:*/
#line 5901 "./mplibdir/mp.w"

typedef struct mp_pair_node_data{
NODE_BODY;
mp_node x_part_;
mp_node y_part_;
}mp_pair_node_data;
typedef struct mp_pair_node_data*mp_pair_node;

/*:266*//*271:*/
#line 5980 "./mplibdir/mp.w"

typedef struct mp_transform_node_data{
NODE_BODY;
mp_node tx_part_;
mp_node ty_part_;
mp_node xx_part_;
mp_node yx_part_;
mp_node xy_part_;
mp_node yy_part_;
}mp_transform_node_data;
typedef struct mp_transform_node_data*mp_transform_node;

/*:271*//*274:*/
#line 6046 "./mplibdir/mp.w"

typedef struct mp_color_node_data{
NODE_BODY;
mp_node red_part_;
mp_node green_part_;
mp_node blue_part_;
}mp_color_node_data;
typedef struct mp_color_node_data*mp_color_node;

/*:274*//*277:*/
#line 6096 "./mplibdir/mp.w"

typedef struct mp_cmykcolor_node_data{
NODE_BODY;
mp_node cyan_part_;
mp_node magenta_part_;
mp_node yellow_part_;
mp_node black_part_;
}mp_cmykcolor_node_data;
typedef struct mp_cmykcolor_node_data*mp_cmykcolor_node;

/*:277*//*459:*/
#line 10936 "./mplibdir/mp.w"

#define mp_fraction mp_number
#define mp_angle mp_number
#define new_number(A) (((math_data *)(mp->math))->allocate)(mp, &(A), mp_scaled_type)
#define new_fraction(A) (((math_data *)(mp->math))->allocate)(mp, &(A), mp_fraction_type)
#define new_angle(A) (((math_data *)(mp->math))->allocate)(mp, &(A), mp_angle_type)
#define free_number(A) (((math_data *)(mp->math))->free)(mp, &(A))

/*:459*//*462:*/
#line 11065 "./mplibdir/mp.w"

typedef struct mp_fill_node_data{
NODE_BODY;
halfword color_model_;
mp_number red;
mp_number green;
mp_number blue;
mp_number black;
mp_string pre_script_;
mp_string post_script_;
mp_knot path_p_;
mp_knot pen_p_;
unsigned char ljoin;
mp_number miterlim;
}mp_fill_node_data;
typedef struct mp_fill_node_data*mp_fill_node;

/*:462*//*466:*/
#line 11146 "./mplibdir/mp.w"

typedef struct mp_stroked_node_data{
NODE_BODY;
halfword color_model_;
mp_number red;
mp_number green;
mp_number blue;
mp_number black;
mp_string pre_script_;
mp_string post_script_;
mp_knot path_p_;
mp_knot pen_p_;
unsigned char ljoin;
mp_number miterlim;
unsigned char lcap;
mp_node dash_p_;
mp_number dash_scale;
}mp_stroked_node_data;
typedef struct mp_stroked_node_data*mp_stroked_node;


/*:466*//*473:*/
#line 11346 "./mplibdir/mp.w"

typedef struct mp_text_node_data{
NODE_BODY;
halfword color_model_;
mp_number red;
mp_number green;
mp_number blue;
mp_number black;
mp_string pre_script_;
mp_string post_script_;
mp_string text_p_;
halfword font_n_;
mp_number width;
mp_number height;
mp_number depth;
mp_number tx;
mp_number ty;
mp_number txx;
mp_number txy;
mp_number tyx;
mp_number tyy;
}mp_text_node_data;
typedef struct mp_text_node_data*mp_text_node;

/*:473*//*477:*/
#line 11447 "./mplibdir/mp.w"

typedef struct mp_start_clip_node_data{
NODE_BODY;
mp_knot path_p_;
}mp_start_clip_node_data;
typedef struct mp_start_clip_node_data*mp_start_clip_node;
typedef struct mp_start_bounds_node_data{
NODE_BODY;
mp_knot path_p_;
}mp_start_bounds_node_data;
typedef struct mp_start_bounds_node_data*mp_start_bounds_node;
typedef struct mp_stop_clip_node_data{
NODE_BODY;
}mp_stop_clip_node_data;
typedef struct mp_stop_clip_node_data*mp_stop_clip_node;
typedef struct mp_stop_bounds_node_data{
NODE_BODY;
}mp_stop_bounds_node_data;
typedef struct mp_stop_bounds_node_data*mp_stop_bounds_node;


/*:477*//*481:*/
#line 11556 "./mplibdir/mp.w"

typedef struct mp_dash_node_data{
NODE_BODY;
mp_number start_x;
mp_number stop_x;
mp_number dash_y;
mp_node dash_info_;
}mp_dash_node_data;

/*:481*//*486:*/
#line 11612 "./mplibdir/mp.w"

typedef struct mp_edge_header_node_data{
NODE_BODY;
mp_number start_x;
mp_number stop_x;
mp_number dash_y;
mp_node dash_info_;
mp_number minx;
mp_number miny;
mp_number maxx;
mp_number maxy;
mp_node bblast_;
int bbtype;
mp_node list_;
mp_node obj_tail_;
halfword ref_count_;
}mp_edge_header_node_data;
typedef struct mp_edge_header_node_data*mp_edge_header_node;

/*:486*//*813:*/
#line 20104 "./mplibdir/mp.w"

typedef struct mp_if_node_data{
NODE_BODY;
int if_line_field_;
}mp_if_node_data;
typedef struct mp_if_node_data*mp_if_node;

/*:813*/
#line 139 "./mplibdir/mp.w"

#endif

/*:4*/
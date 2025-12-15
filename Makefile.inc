# Definitions to include in chapter-specific makefiles

SPL_INCLUDE_DIR = ../include
SPL_LIB_DIR     = ../lib
SPL_LIB         = $(SPL_LIB_DIR)/libspl.a
VPATH           = ../include:../common
SPL_HDRS        = \
common_hdrs.h\
error_exits.h\
get_nums.h\
sys_hdrs.h\
CC := gcc

CFILES_DIR := ./src
CFILES := $(wildcard $(CFILES_DIR)/*.c)
HFILES_DIR := ./inc
HFILES := $(wildcard $(HFILES_DIR)/*.h)
UDIR := ./unit_tests
UNITS := $(wildcard $(UDIR)/*.c)

OBJS_DIR := ./out
OBJS := $(CFILES:$(CFILES_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_UNIT := $(UNITS:$(UDIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_UNIT += $(filter-out $(OBJS_DIR)/main.o, $(OBJS))

CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -g3
UFLAGS := -lcheck -lm -lsubunit

APP = app.exe
UNIT_TEST = unit_tests.exe

.PHONY : clean func unit

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

$(APP) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OBJS_DIR) :
	@mkdir -p $@

$(OBJS_DIR)/%.o : $(CFILES_DIR)/%.c $(HFILES) $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o : $(UDIR)/%.c $(HFILES) $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UNIT_TEST) : $(OBJS_UNIT)
	$(CC) $(OBJS_UNIT) -o $@ $(UFLAGS)

clean :
	@rm -rf ./out *.exe ./func_tests/data/out.txt .c.gcov .exe.dSYM *.gcda *.gcno

unit : $(UNIT_TEST)
	@./$(UNIT_TEST)

func : app.exe
	@cd ./func_tests/scripts; ./func_tests.sh

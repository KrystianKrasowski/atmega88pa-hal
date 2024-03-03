PATH_INC		= include
PATH_SRC		= src
PATH_TEST		= test
PATH_BUILD		= build
PATH_RELEASE_BUILD	= build/release
PATH_RELEASE_OBJS	= build/release/objs
PATH_TEST_BIN		= build/test/bin
PATH_TEST_OBJS		= build/test/objs
PATH_TEST_RESULTS	= build/test/results
PATH_DIST		= dist

INCS = $(wildcard $(PATH_INC)/*.h)
SRCS = $(wildcard $(PATH_SRC)/*.c)
OBJS = $(patsubst $(PATH_SRC)/%.c, $(PATH_RELEASE_OBJS)/%.o, $(SRCS))
LIBS = $(patsubst $(PATH_SRC)/%.c, $(PATH_DIST)/libavrhal-%.a, $(SRCS))

TEST_SRCS	= $(wildcard $(PATH_TEST)/*.c)
TEST_RESULTS	= $(patsubst $(PATH_TEST)/%_test.c, $(PATH_TEST_RESULTS)/%_test.txt, $(TEST_SRCS))

# Release toolchain
CC_RELEASE	= avr-gcc
AR		= avr-ar
CFLAGS_RELEASE	= -mmcu=atmega88pa -Wall -Os -fshort-enums --param=min-pagesize=0 -I./include

# Test toolchain
CC_TEST		= gcc
CFLAGS_TEST	= -I./test/include -I./include
CC_TEST_LIBS	= -lunity

# Test Summary
MSG_INF	= \\033[0m
MSG_WRN	= \\033[1;33m
MSG_ERR = \\033[0;31m
MSG_SCC = \\033[0;32m

SUM_PASSED	= `grep :PASS $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_IGNORED	= `grep :IGNORE $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_FAILED	= `grep :FAIL $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_FAILED_DET	= `cat $(PATH_TEST_RESULTS)/*.txt | grep FAIL`

all: $(LIBS)

$(PATH_DIST)/libavrhal-%.a: $(PATH_RELEASE_OBJS)/%.o
	@mkdir -p $(PATH_DIST)
	@$(AR) rcs $@ $<

$(PATH_RELEASE_OBJS)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(PATH_RELEASE_OBJS)
	@$(CC_RELEASE) $(CFLAGS_RELEASE) -c $< -o $@

test: $(TEST_RESULTS)
	@printf "Test results:\n"
	@printf "PASSED:  $(SUM_PASSED)\n"
	@printf "IGNORED: $(SUM_IGNORED)\n"
	@printf "FAILED:  $(SUM_FAILED)\n"
	@printf "$(SUM_FAILED_DET)\n"

$(PATH_TEST_RESULTS)/%.txt: $(PATH_TEST_BIN)/%.out
	@mkdir -p $(@D)
	@-./$< > $@ 2>&1

$(PATH_TEST_BIN)/%_test.out: $(PATH_TEST_OBJS)/%_test.o $(PATH_TEST_OBJS)/%.o
	@mkdir -p $(@D)
	@$(CC_TEST) $^ -o $@ $(CC_TEST_LIBS)

$(PATH_TEST_OBJS)/%.o:: $(PATH_TEST)/%.c
	@mkdir -p $(@D)
	@$(CC_TEST) $(CFLAGS_TEST) -c $< -o $@

$(PATH_TEST_OBJS)/%.o:: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC_TEST) $(CFLAGS_TEST) -c $< -o $@

clean:
	@rm -rf $(PATH_BUILD) $(PATH_DIST)

install: $(LIBS)
	@mkdir -p /usr/local/include/avrhal
	@cp $(INCS) /usr/local/include/avrhal
	@cp $(LIBS) /usr/local/lib

.PHONY: all test clean install
.PRECIOUS: $(PATH_TEST_BIN)/%.out $(PATH_TEST_RESULTS)/%.txt

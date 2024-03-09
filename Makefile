VERSION_MAJOR 	= 1
VERSION_MINOR 	= 0
VERSION_PATCH 	= 0
VERSION			= $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

PATH_INC			= include
PATH_SRC			= src
PATH_TEST			= test
PATH_BUILD			= build
PATH_RELEASE_BUILD	= build/release
PATH_RELEASE_OBJS	= build/release/objs
PATH_TEST_BIN		= build/test/bin
PATH_TEST_OBJS		= build/test/objs
PATH_TEST_RESULTS	= build/test/results
PATH_DIST			= dist

INCS = $(wildcard $(PATH_INC)/*.h)
SRCS = $(wildcard $(PATH_SRC)/*.c)
OBJS = $(patsubst $(PATH_SRC)/%.c, $(PATH_RELEASE_OBJS)/%.o, $(SRCS))
LIBS = $(patsubst $(PATH_SRC)/%.c, $(PATH_DIST)/libavrhal-%-$(VERSION).a, $(SRCS))

TEST_SRCS		= $(wildcard $(PATH_TEST)/*.c)
TEST_RESULTS	= $(patsubst $(PATH_TEST)/%_test.c, $(PATH_TEST_RESULTS)/%_test.txt, $(TEST_SRCS))
TEST_BINS		= $(patsubst $(PATH_TEST)/%_test.c, $(PATH_TEST_BIN)/%_test.out, $(TEST_SRCS)))

# Symbols
CC_SYMBOLS = \
	-DAVRHAL_VER_MAJOR=$(VERSION_MAJOR) \
	-DAVRHAL_VER_MINOR=$(VERSION_MINOR) \
	-DAVRHAL_VER_PATCH=$(VERSION_PATCH)

# Release toolchain
DEVICE 			= atmega88pa
CC_RELEASE		= avr-gcc
AR				= avr-ar
CFLAGS_RELEASE	= \
	-mmcu=$(DEVICE) \
	-Wall \
	-Os \
	-fshort-enums \
	--param=min-pagesize=0

# Release paths
INCLUDE_RELEASE	= -I./include

# Test toolchain
CC_TEST			= gcc
CFLAGS_TEST		= -I./test/include -I./include
CC_TEST_LIBS	= -lunity

# Test Summary
MSG_INF	= \\033[0m
MSG_WRN	= \\033[1;33m
MSG_ERR = \\033[0;31m
MSG_SCC = \\033[0;32m

SUM_PASSED		= `grep :PASS $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_IGNORED		= `grep :IGNORE $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_FAILED		= `grep :FAIL $(PATH_TEST_RESULTS)/*.txt | wc -l`
SUM_FAILED_DET	= `cat $(PATH_TEST_RESULTS)/*.txt | grep FAIL`

all: $(LIBS)

$(PATH_DIST)/libavrhal-%-$(VERSION).a: $(PATH_RELEASE_OBJS)/%.o
	@mkdir -p $(PATH_DIST)
	@$(AR) rcs $@ $<

$(PATH_RELEASE_OBJS)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(PATH_RELEASE_OBJS)
	@$(CC_RELEASE) $(CFLAGS_RELEASE) $(INCLUDE_RELEASE) $(CC_SYMBOLS) -c $< -o $@

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
	@$(CC_TEST) $(CFLAGS_TEST) $(CC_SYMBOLS) -c $< -o $@

$(PATH_TEST_OBJS)/%.o:: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	@$(CC_TEST) $(CFLAGS_TEST) $(CC_SYMBOLS) -c $< -o $@

clean:
	@rm -rf $(PATH_BUILD) $(PATH_DIST)

install: $(LIBS)
	@mkdir -p /usr/local/include/avrhal
	@cp $(INCS) /usr/local/include/avrhal
	@cp $(LIBS) /usr/local/lib

.PHONY: all test clean install
.PRECIOUS: $(TEST_BINS) $(TEST_RESULTS)

PATH_SRC 			= src
PATH_TEST 			= test
PATH_TEST_INC 		= test/include
PATH_BUILD 			= build
PATH_RELEASE_BUILD 	= build/release
PATH_RELEASE_OBJS 	= build/release/objs
PATH_TEST_BIN 		= build/test/bin
PATH_TEST_OBJS 		= build/test/objs
PATH_TEST_RESULTS 	= build/test/results
PATH_DIST 			= dist

SRCS = $(wildcard $(PATH_SRC)/*.c)
OBJS = $(patsubst $(PATH_SRC)/%.c, $(PATH_RELEASE_OBJS)/%.o, $(SRCS))
LIBS = $(patsubst $(PATH_SRC)/%.c, $(PATH_DIST)/libavrhal-%.a, $(SRCS))

TEST_SRCS		= $(wildcard $(PATH_TEST)/*.c)
TEST_RESULTS 	= $(patsubst $(PATH_TEST)/%_test.c, $(PATH_TEST_RESULTS)/%_test.txt, $(TEST_SRCS))
TEST_PASSED 	= `grep -s PASS $(PATH_TEST_RESULTS)/*.txt`
TEST_FAILED 	= `grep -s FAIL $(PATH_TEST_RESULTS)/*.txt`
TEST_IGNORED 	= `grep -s IGNORE $(PATH_TEST_RESULTS)/*.txt`

# Release toolchain
CC_RELEASE 		= avr-gcc
AR 				= avr-ar
CFLAGS_RELEASE	= -mmcu=atmega88pa -Wall -Os

# Test toolchain
CC_TEST			= gcc
CFLAGS_TEST		= -I$(PATH_TEST_INC)
CC_TEST_LIBS	= -lunity

all: $(LIBS)

$(PATH_DIST)/libavrhal-%.a: $(PATH_RELEASE_OBJS)/%.o
	@mkdir -p $(PATH_DIST)
	@$(AR) rcs $@ $<

$(PATH_RELEASE_OBJS)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(PATH_RELEASE_OBJS)
	@$(CC_RELEASE) $(CFLAGS_RELEASE) -c $< -o $@

test: $(TEST_RESULTS)
	@printf "=======================\nIGNORES:\n======================="
	@printf "\n$(TEST_IGNORED)\n"
	@printf "=======================\nFAILURES:\n======================="
	@printf "\n$(TEST_FAILED)\n"
	@printf "=======================\nPASSED:\n======================="
	@printf "\n$(TEST_PASSED)\n"
	@printf "\nDONE\n"

$(PATH_TEST_RESULTS)/%.txt: $(PATH_TEST_BIN)/%.out
	@mkdir -p $(@D)
	-./$< > $@ 2>&1

$(PATH_TEST_BIN)/%_test.out: $(PATH_TEST_OBJS)/%_test.o $(PATH_TEST_OBJS)/%.o
	@mkdir -p $(@D)
	$(CC_TEST) $^ -o $@ $(CC_TEST_LIBS)

$(PATH_TEST_OBJS)/%.o:: $(PATH_TEST)/%.c
	@mkdir -p $(@D)
	$(CC_TEST) $(CFLAGS_TEST) -c $< -o $@

$(PATH_TEST_OBJS)/%.o:: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	$(CC_TEST) $(CFLAGS_TEST) -c $< -o $@

clean:
	@rm -rf $(PATH_BUILD) $(PATH_DIST)

.PHONY: all test clean
.PRECIOUS: $(PATH_TEST_BIN)/%.out $(PATH_TEST_RESULTS)/%.txt
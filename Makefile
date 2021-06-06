TARGET = main.out
HDRS_DIR = project/include
CC = cc

SRCS = \
		project/src/main.c \
		project/src/masterwrite.c \
		project/src/blackrecord.c \
		project/src/transactionwrite.c \
		project/src/file_input_output.c

TEST_TARGET = test_main.out
TEST_HDR = project/include
TEST_SRCS = project/src/file_input_output.c \
			project/test/test_functions.c \
			project/test/main.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)

test: $(TEST_SRCS)
	$(CC) -Wall -Wextra -Werror -I $(TEST_HDR) -o $(TEST_TARGET) $(TEST_SRCS)

test_clean:
	rm -fr $(TEST_TARGET)

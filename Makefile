TARGET = main.out
HDRS_DIR = project/include

SRCS = \
		project/src/main.c \
		project/src/masterwrite.c \
		project/src/blackrecord.c \
		project/src/transactionwrite.c \
		project/src/file_open_read_check.c

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)

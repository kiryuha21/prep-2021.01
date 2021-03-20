#include "/home/kiryuha21/prep-2021.01/project/include/file_open_read_check.h"

int main() {
	if (file_open_read_check("io_test")) {
		puts("success");
	} else {
		puts("input/output error");
	}
	return 0;
}
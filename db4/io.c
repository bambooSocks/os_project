#include "io.h"

#define MAX_DIGITS_INT32  10


int syscall_read(char *dest, int len) {

	// At -O3 GCC was optimizing dest and len away.
	//  Volatile is to prevent that.
	volatile int bytes_read = 0, _len = len;
	volatile char *_dest = dest;

	// Read system call:
	//  eax contains the system call number, 3 for read
	//  ebx contains the file descriptor to read from, 0 for stdin
	//  ecx contains the location to read into
	//  edx contains the number of bytes to read
	__asm__ ("int $0x80"
			: "=a" (bytes_read)
			: "a" (0x03),
			  "b" (0x0),
			  "c" (_dest),
			  "d" (_len)
			:
			  );

	return bytes_read;
}


int syscall_write(char *data, int len) {

	// At -O3 GCC was optimizing these away.  Added volatile
	//  to prevent that from happening
	volatile int bytes_written = 0, _len = len;
	volatile char *_data = data;

	// Read system call:
	//  eax contains the system call number, 4 for write
	//  ebx contains the fd to read from, 1 for stdout, 2 for stderr
	//  ecx contains the location to read into
	//  edx contains the number of bytes to read
	__asm__ ("int $0x80"
			: "=a" (bytes_written)
			: "a" (0x04),
			  "b" (0x01),
			  "c" (_data),
			  "d" (_len)
			:
			  );
	return bytes_written;
}

// Helper function to print out a single char
int write_char(char c) {
	return (syscall_write(&c, 1) == 1);
}

// write NULL terminated string
int write_NTS(char *s) {
	int len = 0;
	char *p = s;
	while (*p != 0) { p++; len++; }
	return syscall_write(s, len);
}

int write_int(int i) {
    char digits[MAX_DIGITS_INT32] = {0};
    
	int written = 0;
    if (i < 0) {
        if (!write_char('-')) {
            return 0;
        }
        written++;
        i *= -1;
    }

    int iterate_over = i;
    for (int d = MAX_DIGITS_INT32 - 1; d > 0 && iterate_over != 0; d--) {
        digits[d] = iterate_over % 10;
        iterate_over /= 10;
    }
    
    int found_non_zero = 0;

    for (int d = 0; d < MAX_DIGITS_INT32; d++) {
        if (found_non_zero || digits[d] != 0 || d == (MAX_DIGITS_INT32 - 1)) {
            found_non_zero = 1;
            if (!write_char('0' + digits[d])) {
                return written;
            }
            written++;
        }
    }

    return written;
}


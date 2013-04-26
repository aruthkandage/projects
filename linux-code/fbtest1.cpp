#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FB "/dev/fb0"

int main(int argc, char** argv) {
	int fd;

	fd = open(FB, O_RDWR);
	if(fd == -1) {
		printf("Could not open frame buffer for I/O.\n");
		exit(1);
	}

	close(fd);
	return 0;
}

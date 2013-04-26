#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FB "/dev/fb0"

int main(int argc, char** argv) {
	int retval;
	int fd;

	fb_var_screeninfo screen_info;
	
	fd = open(FB, O_RDWR);
	if(fd == -1) {
		printf("Could not open frame buffer for I/O.\n");
		exit(1);
	}
	
	retval = ioctl(fd, FBIOGET_VSCREENINFO, &screen_info);
	if(retval == -1) {
		printf("Error while querying frame buffer info.\n");
		exit(1);
	}

	printf("%dx%d\n", screen_info.xres, screen_info.yres);
	
	close(fd);
	return 0;
}

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
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
	fb_fix_screeninfo fscreen_info;
	char* fb_map;
	int xres,xres_v,yres,yres_v,xoffset,yoffset,bps,line_length;
	size_t fb_map_size;


	// Open the framebuffer
	fd = open(FB, O_RDWR);
	if(fd == -1) {
		printf("Could not open frame buffer for I/O.\n");
		exit(1);
	}
	
	// Query for frame buffer resolution, bits-per-pixel
	retval = ioctl(fd, FBIOGET_VSCREENINFO, &screen_info);
	if(retval == -1) {
		printf("Error while querying frame buffer info.\n");
		exit(1);
	}

	retval = ioctl(fd, FBIOGET_FSCREENINFO, &fscreen_info);
	if(retval == -1) {
		printf("Error while querying frame buffer info.\n");
		exit(1);
	}

	xres = screen_info.xres;
	xres_v = screen_info.xres_virtual;
	yres = screen_info.yres;
	yres_v = screen_info.yres_virtual;
	xoffset = screen_info.xoffset;
	yoffset = screen_info.yoffset;
	bps = screen_info.bits_per_pixel;
	line_length = fscreen_info.line_length;

	// Memory map the frame buffer
	fb_map_size = xres_v * yres_v * (bps / 8);
	fb_map = (char*) mmap(NULL, fb_map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(fb_map == (char*)-1) {
		printf("Could not memory map the frame buffer.\n");
		exit(1);
	}

	// Activate the framebuffer
	screen_info.activate |= FB_ACTIVATE_NOW | FB_ACTIVATE_ALL | FB_ACTIVATE_FORCE;
	retval = ioctl(fd, FBIOPUT_VSCREENINFO, &screen_info);
	if(retval == -1) {
		printf("Could not activate frame buffer.\n");
		exit(1);
	}

	// Fill the screen
	for(int y=0; y < yres; y++) {
		for(int x=0; x < xres; x++) {
			int ho_byte = (x + xoffset) * (bps / 8) + (y + yoffset) * line_length;

			if(bps == 24) {
				fb_map[ho_byte] = 0xff;
				fb_map[ho_byte + 1] = 0;
				fb_map[ho_byte + 2] = 0;
			} else if(bps == 32) {
				fb_map[ho_byte] = 0xff;
				fb_map[ho_byte + 1] = 0;
				fb_map[ho_byte + 2] = 0;
				fb_map[ho_byte + 3] = 0;
			}					
		}
	}
	msync(fb_map, fb_map_size, MS_SYNC);
	sleep(2);

	munmap(fb_map, fb_map_size);
	close(fd);
	return 0;
}

/* main.c -- Read the back blocks on Linux
 *
 * Adopted from busybox. Inspired by Valentine R.
 * (http://lists.infradead.org/pipermail/linux-mtd/2007-November/019830.html)
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>


char* exe_name = NULL;
char *mtd_device = NULL;

int get_bb_number(int fd, const mtd_info_t *meminfo, int verbose) {
	int isNAND = meminfo->type == MTD_NANDFLASH ? 1 : 0;
	int ibbCounter = 0;
	__u32 offset;

	if (verbose) {
		printf("%s: Checking 0x%08x-0x%08x for bad blocks:\n", mtd_device, 0, meminfo->size);
	}

	for (offset= 0; offset < meminfo->size; offset += meminfo->erasesize) {
		loff_t loffset = offset;
		int ret = ioctl(fd, MEMGETBADBLOCK, &loffset);
		if (ret > 0) {
			if (verbose) {
				printf("  Found bad block at 0x%08x\n", offset);
			}
			ibbCounter++;
			continue;
		}
		else if (ret < 0)
		{
			if (errno == EOPNOTSUPP) {
				if (isNAND) {
					printf("\n\n%s: %s: Bad block check not available\n", exe_name, mtd_device);
					exit(1);
				}
			}
			else
			{
				printf("\n%s: %s: MTD get bad block failed: %s\n",
				exe_name, mtd_device, strerror(errno));
				exit(1);
			}
		}
		else if (verbose) {
			printf("  0x%08x is clean.\n", offset);
		}
	}
	return ibbCounter;
}

void print_help() {
	fprintf(stderr, "Usage: %s [OPTIONS] MTD_DEVICE\n", exe_name);
	fprintf(stderr, "\n");
	fprintf(stderr, "  OPTIONS:\n");
	fprintf(stderr, "    -h  Shows this help\n");
	fprintf(stderr, "    -v  Verbose output\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  Example:\n");
	fprintf(stderr, "    %s -v /dev/mtd4\n", exe_name);
}

int main(int argc, char *argv[]) {
	int md_fd, cnt;
	int iNumOfBadBlocks = 0;
	int verbose = 0;
	mtd_info_t mtd_meminfo;

	for (cnt=0; cnt < argc; cnt++) {
		if (cnt==0) {
			exe_name = argv[cnt];
		}
		else if (argv[cnt][0] == '-') {
			if (strcmp(argv[cnt], "-h") == 0) {
				print_help();
				exit(1);
			}
			else if (strcmp(argv[cnt], "-v") == 0) {
				verbose = 1;
			}
			else {
				fprintf(stderr, "Ignoring unknown option '%s'!\n", argv[cnt]);
			}
		}
		else {
			mtd_device = argv[cnt];
		}
	}

	if (mtd_device == NULL) {
		fprintf(stderr, "Error: Missing argument MTD_DEVICE!\n\n");
		print_help();
		exit(1);
	}

	if ((md_fd = open(mtd_device, O_RDONLY)) < 0) {
		printf("\n\n%s: %s: %s\n", exe_name, mtd_device, strerror(errno));
		exit(1);
	}

	if (ioctl(md_fd, MEMGETINFO, &mtd_meminfo) != 0) {
		printf("\n\n%s: %s: unable to get MTD device info\n", exe_name, mtd_device);
		exit(1);
	}

	iNumOfBadBlocks = get_bb_number( md_fd, &mtd_meminfo, verbose);
	printf("%s has %d bad blocks.\n", exe_name, iNumOfBadBlocks);
	return 0;
}



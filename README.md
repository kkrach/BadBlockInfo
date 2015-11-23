Reading the Bad-Block-Table on Linux

Adopted from busybox. Inspired by Valentine R.
(http://lists.infradead.org/pipermail/linux-mtd/2007-November/019830.html)


Cross-compile with:

$ CROSS_COMPILE="/opt/cl-ng-powerpc/bin/powerpc-e500v2-linux-gnuspe-" make
/opt/cl-ng-powerpc/bin/powerpc-e500v2-linux-gnuspe-gcc -Wall -Werror -c -o main.o main.c
/opt/cl-ng-powerpc/bin/powerpc-e500v2-linux-gnuspe-gcc -Wall -Werror -o bbinfo main.o
$ 



Example Output:

# ./bbinfo -v /dev/mtd5
/dev/mtd5: Checking 0x00000000-0x00500000 for bad blocks:
  0x00000000 is clean.
  0x00020000 is clean.
  0x00040000 is clean.
  0x00060000 is clean.
  0x00080000 is clean.
  0x000a0000 is clean.
  0x000c0000 is clean.
  0x000e0000 is clean.
  0x00100000 is clean.
  0x00120000 is clean.
  0x00140000 is clean.
  0x00160000 is clean.
  0x00180000 is clean.
  0x001a0000 is clean.
  0x001c0000 is clean.
  0x001e0000 is clean.
  0x00200000 is clean.
  0x00220000 is clean.
  0x00240000 is clean.
  0x00260000 is clean.
  0x00280000 is clean.
  0x002a0000 is clean.
  0x002c0000 is clean.
  0x002e0000 is clean.
  0x00300000 is clean.
  0x00320000 is clean.
  0x00340000 is clean.
  0x00360000 is clean.
  0x00380000 is clean.
  0x003a0000 is clean.
  0x003c0000 is clean.
  0x003e0000 is clean.
  0x00400000 is clean.
  0x00420000 is clean.
  0x00440000 is clean.
  0x00460000 is clean.
  0x00480000 is clean.
  0x004a0000 is clean.
  0x004c0000 is clean.
  0x004e0000 is clean.
Number of the bad blocks is 0
#

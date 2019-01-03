/* Author: Saumya Saxena
Assignment 4 - Computing in the Small
Date: June 9, 2018
*/
#include <u.h>
#include <libc.h>

void
main()
{
	int fd, fd1;
	int i;
	uchar buf[34];

	bind("#G","/dev",MAFTER); 
	fd1=open("/dev/gpio",ORDWR);
	fprint(fd1, "function 24 out\n");
	fprint(fd1, "function 23 out\n");
	fprint(fd1,"set 24 1\n");
	sleep(70);
	fprint(fd1,"set 24 0\n");

	bind("#pi", "/dev", MAFTER);
	fd = open("/dev/spi0", ORDWR);
	if(fd < 0) {
		bind("#pi", "/dev", MAFTER);
		fd = open("/dev/spi0", ORDWR);
		if(fd < 0)
			print("open error: %r\n");
	}

	fprint(fd1,"set 23 0\n");
	//buf[0] = 0x20;
	//pwrite(fd, buf, 1,0);
	buf[0] = 0x21; //extended addressing
	pwrite(fd, buf, 1,0);
	buf[0] = 0x14;
	pwrite(fd, buf, 1,0);
	buf[0] = 0xB2;
	pwrite(fd, buf, 1,0);
	buf[0] = 0x20;
	pwrite(fd, buf, 1,0);
	buf[0] = 0x0C;
	pwrite(fd, buf, 1,0);
	buf[0] = 0x40;
	pwrite(fd, buf, 1,0);
	buf[0] = 0x80;
	pwrite(fd, buf, 1,0);

	fprint(fd1,"set 23 1\n");
	for(i=0; i<50; i++){
	buf[0] = 0x1F;
	pwrite(fd, buf, 1,0);
	}

	fprint(fd1,"set 23 0\n");
	buf[0] = 0x22; //vertical addressing
	pwrite(fd, buf, 1,0);

	fprint(fd1,"set 23 1\n");
	for(i=0; i<50; i++){
	buf[0] = 0x1F;
	pwrite(fd, buf, 1,0);
	}
}

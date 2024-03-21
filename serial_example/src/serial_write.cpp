#include "serial_help.h"

#define DATA_LEN 8

int main(int argc, char** argv)
{
	int fd,nByte;
	char *uart3 = "/dev/pts/21";
	unsigned char data[DATA_LEN];
	data[0] = 0xff;
	data[1] = 0xee;
	data[2] = 0xdd;
	data[3] = 0xcc;
	data[4] = 0xbb;
	data[5] = 0xaa;
	data[6] = 0x99;
	data[7] = 0x88;
	char buff[512];
	memset(buff,0,sizeof(buff));
	if((fd=open(uart3,O_RDWR | O_NOCTTY))<0)
	{
		printf("open failed!\n");
	}else
	{
		set_opt(fd,115200,8,'N',1);
		while(1)
		{
			write(fd,data,DATA_LEN);
			sleep(1);
		}
	}
	return 0;
}

#include "serial_help.h"


int main(int argc, char** argv)
{
	int fd,nByte;
	char *uart3 = "/dev/pts/23";
	unsigned char buff[512];
	memset(buff,0,sizeof(buff));
	if((fd=open(uart3,O_RDWR | O_NOCTTY))<0)
	{
		printf("open failed!\n");
	}else
	{
		set_opt(fd,115200,8,'N',1);
		while(1)
		{
			while((nByte=read(fd,buff,512))>0)
			{
				print(buff, nByte);
			}
			
		}
	}
	return 0;
}

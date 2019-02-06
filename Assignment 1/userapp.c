// C program to illustrate 
// I/O system Calls 
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include<stdint.h>
#include <fcntl.h>
#include<sys/types.h>

int main (void) 
{ 
int c;
printf("Run as superuser/root or give 777 permission\n"); 
printf("enter x,y or z to get corresponding axis data"); 
c = getchar( );
printf( "\nYou entered: ");
putchar( c );
printf("\n");


uint16_t buf;
 int fd;

switch (c){
case 'x':
fd = open("/dev/adxl_x",  O_RDWR);  
if (fd==-1){
	printf("file %s doesnot exist or has benn locked by another process\n","/dev/accx");
	exit(-1);
}
//printf("");
read(fd, &buf,sizeof(buf));
printf("accleration is %d\n",buf);
close(fd);

break;

case 'y':
 fd = open("/dev/adxl_y",O_RDWR);  
if (fd==-1){
	printf("file %s doesnot exist or has benn locked by another process\n","/dev/accy");
	exit(-1);
}
//printf("");
read(fd, &buf,sizeof(buf));
printf("accleration is %d\n",buf);
close(fd);

break;

case 'z':
 
fd = open("/dev/adxl_z", O_RDWR);  
if (fd==-1){
	printf("file %s doesnot exist or has benn locked by another process\n","/dev/accz");
	exit(-1);
}
//printf("");
read(fd, &buf,sizeof(buf));
printf("accleration is %d\n",buf);
close(fd);

break;

}

    
} 

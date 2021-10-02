#include <stdio.h>
#include <stdlib.h>
#include  <fcntl.h>

int main() {

	int dev = open("/dev/mydevice",O_RDONLY);
	if(dev == -1){
		printf("opening was not possible\n");
		return -1;
		}
	return 0;


}

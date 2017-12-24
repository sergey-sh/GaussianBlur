/*
GausianBlur width x height = 9 x 9 gamma = 2.0

*/
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "blur_lib.h"


// ffmpeg -i c0.jpg -pix_fmt gray -f rawvideo c0.gray
// display -size 512x512 -depth 8 c0.gray

int main(int argc, char** argv) {
	if(argc<4) {
		fprintf(stderr,"Usage: blur filegray width height\n");
		return 1;
	}
	int width = atoi(argv[2]);
	int height = atoi(argv[3]);
	int src_size = width*height;
	FILE *h = fopen(argv[1],"r");
	
	BYTE src_gray[src_size];
	BYTE a[src_size];
	
	size_t readed = fread(src_gray,1,src_size,h);
	fclose(h);
	if(readed!=src_size) {
		fprintf(stderr,"readed from file != size gray (%d != %d)\n",readed,src_size);
		return 1;
	}
	
	clock_t Start = clock();
	
	GaussianBlur_9_2(src_gray,width,height,a);
	
	printf("Time Gaussian: %f ms\n",(double)(clock() - Start)/CLOCKS_PER_SEC*1000);

	h = fopen("test.gray","w");
	fwrite(src_gray,1,src_size,h);
	fclose(h);
	
	return 0;
}


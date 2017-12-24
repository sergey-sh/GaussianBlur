/*
GausianBlur by Sergey Shckuliov sergey.sckuliov@gmail.com 2017-12-24
*/
#include <iostream>
#include <cstdio>
#include "blur_lib.h"

void GaussianBlur_9_2_1Dblur(BYTE *src_gray,int width,int height,BYTE *a) {
	const int k0 = 13380, k1 = 11808, k2 = 8115, k3 = 4344, k4 = 1811;
	int src_size = width*height;
	int width4 = width-4,height4 = height-4;
	int i,j;
	BYTE *p;
	BYTE* src_p;
	
	i = 0;
	while(i<src_size) {
		src_p = &src_gray[i];
		p = &a[i];
		*p =
			((src_p[4])*k4+(src_p[3])*k3+(src_p[2])*k2+(src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[4])*k4+(src_p[3])*k3+(src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[4])*k4+(src_p[3])*k3+(src_p[-2]+src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[4])*k4+(src_p[-3]+src_p[3])*k3+(src_p[-2]+src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		j = 4;
		while(j<width4) {
			*p = 
				((src_p[-4]+src_p[4])*k4+(src_p[-3]+src_p[3])*k3+(src_p[-2]+src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
				src_p[0]*k0) >> 16
				;
			j++;
			p++;
			src_p++;
		}
		*p =
			((src_p[-4])*k4+(src_p[-3]+src_p[3])*k3+(src_p[-2]+src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[-4])*k4+(src_p[-3])*k3+(src_p[-2]+src_p[2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[-4])*k4+(src_p[-3])*k3+(src_p[-2])*k2+(src_p[-1]+src_p[1])*k1+
			src_p[0]*k0) >> 16
			;
		p++;
		src_p++;
		*p =
			((src_p[-4])*k4+(src_p[-3])*k3+(src_p[-2])*k2+(src_p[-1])*k1+
			src_p[0]*k0) >> 16
			;
		i+=width;
	}
}

void rotate_gray(BYTE *src_gray,int width,int height,BYTE *a) {
	int i,j,z;
	BYTE *p;
	BYTE* src_p;
	int src_size = width*height;
	i = 0;
	j = 0;
	while(i<src_size) {
		src_p = &src_gray[j];
		p = &a[i];
		z = 0;
		while(z<width) {
			*src_p = *p;
			src_p+=height;
			p++;
			z++;
		}
		i+=width;
		j++;
	}
}	

void GaussianBlur_9_2(BYTE *src_gray,int width,int height,BYTE *a) {
	// Horizontal Blur
	GaussianBlur_9_2_1Dblur(src_gray,width,height,a);
	// Rotate 90
	rotate_gray(src_gray,width,height,a);
	// Vertical Blur
	GaussianBlur_9_2_1Dblur(src_gray,height,width,a);
	// Rotate 90
	rotate_gray(src_gray,height,width,a);
}



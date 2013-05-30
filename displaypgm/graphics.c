/*
 *  graphics.c
 *  
 *
 *  Created by Rob Mitchelmore on 30/03/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

int screenwidth  = 640;
int screenheight = 480;

void scanline(int y, int x, int width, char col) {
	int yoffset = (y * screenwidth);
	int xoffset = (x);
	memset(screen_fb + yoffset + xoffset, col, width * 2);
}

void cls() {
	memset(screen_fb, 0, screenwidth * screenheight * 2);
}

void rectangle(int x, int y, int width, int height, int col) {
	int i = 0;
	for (i = 0; i < height; i++) {
		scanline(y+i, x, width, col);
	}
}

void setpixel(int x, int y, uint16_t pixel) {
	int yoffset = (y * screenwidth);
	int xoffset = (x);
	*(screen_fb + yoffset + xoffset) = pixel;
}
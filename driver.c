#include "library.c"
typedef unsigned short color_t;

void init_graphics();
void exit_graphics();
void clear_screen();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void fill_circle(int x, int y, int r, color_t c);
void draw_text(int x, int y, const char *text, color_t c);

int main(){
	//Initialize the graphics library
	init_graphics();

	//Draw 3 rectangles and 1 pixel instantly
	draw_rect(100, 100, 50, 100, 10); //red
	draw_rect(150, 100, 50, 50,15); //blue-ish
	draw_rect(0, 0, 100, 100,60); //white
	draw_pixel(200, 250, 70); //green

	sleep_ms(5000); //test the sleep function
	draw_rect(-150, 300, 80000, 300, 40); //yellow-ish rectangle mostly off-screen; almost looks like a line

	sleep_ms(5000);
	clear_screen(); //test the function that clears the screen
	sleep_ms(2000);

	draw_rect(300, 300, 100, 50,70); //maroon/brown/purple
	sleep_ms(1000);
	draw_rect(100, 150, 200, 200, 40); //yellow/gold
	sleep_ms(500);

	//test a 500ms interval between text, centered in large rectang

	exit_graphics(); //restore default settings and exit from graphics library
}

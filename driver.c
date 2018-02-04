#include "library.c"

int main(){
	//Initialize the graphics library
	init_graphics();

	//Draw 3 rectangles and 1 pixel instantly
	draw_rect(100, 100, 50, 100, (color_t) MAKE_COLOR(30, 0, 0)); //red
	draw_rect(150, 100, 50, 50, MAKE_COLOR(15, 50, 10)); //blue-ish
	draw_rect(0, 0, 100, 100, MAKE_COLOR(30, 60, 30)); //white
	draw_pixel(200, 250, MAKE_COLOR(0, 60, 0)); //green

	sleep_ms(5000); //test the sleep function
	draw_rect(-150, 300, 80000, 300, MAKE_COLOR(23, 54, 1)); //yellow-ish rectangle mostly off-screen; almost looks like a line

	sleep_ms(5000);
	clear_screen(); //test the function that clears the screen
	sleep_ms(2000);

	draw_rect(300, 300, 100, 50, MAKE_COLOR(10, 10, 10)); //maroon/brown/purple
	sleep_ms(1000);
	draw_rect(100, 150, 200, 200, MAKE_COLOR(30, 50, 5)); //yellow/gold
	sleep_ms(500);

	//test a 500ms interval between text, centered in large rectangle

	while(getkey() != 'c'){} //test to see if input works; basically acts as an exit for the user

	exit_graphics(); //restore default settings and exit from graphics library
}

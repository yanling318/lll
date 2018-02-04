#include <stdio.h>
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

int main (int argc, char** argv)
{
    printf("Press keys \"rentangle\" to draw a unfill rectangle.\n");
    printf("Press keys \"circle\" to draw a filled circle.\n");
    printf("Press the \"q\" to quit the program.\n");
    printf("use \"WASD\" keys to move the shape around.\n");
    char key;
    int x = (640-20)/2;
    int y = (480-20)/2;
    int choice;
    scanf("%d", &choice);
 
    if(choice == "rentangle")
    {  init_graphics();
        clear_screen();
        draw_rect(x, y, 200, 100, 20);
        do
        {
            key = getkey();
            if(key == 'w') y-=10;
            else if(key == 's') y+=10;
            else if(key == 'a') x-=10;
            else if(key == 'd') x+=10;
            clear_screen();
            draw_rect(x, y, 200, 100, 20);
            sleep_ms(20);
        } while(key != 'q');
        clear_screen();
        exit_graphics();
    }
    
    if(choice == 'circle')
    {
        init_graphics();
        clear_screen();
        draw_circle(x, y, 75, 20);
        do
        {
            key = getkey();
            if(key == 'w') y-=10;
            else if(key == 's') y+=10;
            else if(key == 'a') x-=10;
            else if(key == 'd') x+=10;
            clear_screen();
            draw_circle(x, y, 75, 20);
            sleep_ms(20);
        } while(key != 'q');
        clear_screen();
        exit_graphics();
    }
    return 0;
}

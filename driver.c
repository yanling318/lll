#include <stdio.h>

typedef unsigned short color_t;

void init_graphics();
void exit_graphics();
void clear_screen();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_circle(int x, int y, int r, color_t c);
#define BLUE  30
#define GREEN 2016
#define RED   63488

int main (int argc, char** argv)
{
    printf("Press key \"1\" to draw a unfill blue rectangle.\n");
    printf("Press key \"2\" to draw a filled blue circle.\n");
    printf("Press key \"q\" to quit the program.\n");
    printf("use \"WASD\" keys to move the shape around.\n");
    char key;
    int x = (640-20)/2;
    int y = (480-20)/2;
    int choice;
    scanf("%d", &choice);
 
    if(choice == 1)
    {  init_graphics();
        clear_screen();
        draw_rect(x, y, 200, 100, 60);
        do
        {
            key = getkey();
            if(key == 'w') y-=10;
            else if(key == 's') y+=10;
            else if(key == 'a') x-=10;
            else if(key == 'd') x+=10;
            clear_screen();
            draw_rect(x, y, 200, 100, 60);
            sleep_ms(20);
        } while(key != 'q');
        clear_screen();
        exit_graphics();
    }
    
    if(choice == 2)
    {
        init_graphics();
        clear_screen();
        draw_circle(x, y, 75, 80);
        do
        {
            key = getkey();
            if(key == 'w') y-=10;
            else if(key == 's') y+=10;
            else if(key == 'a') x-=10;
            else if(key == 'd') x+=10;
            clear_screen();
            draw_circle(x, y, 75, 80);
            sleep_ms(20);
        } while(key != 'q');
        clear_screen();
        exit_graphics();
    }
    
    if(choice ==3)
    {
        init_graphics();
        clear_screen();
        draw_rect(100,100,30,30, RED  );
        sleep_ms(250);
        draw_rect(110,110,10,10, GREEN);
        sleep_ms(250);
        draw_rect( 90, 90,50,50, BLUE );
        
        sleep_ms(1000);
        
        draw_circle(200,200, 50, BLUE);
        
        draw_rect(150,150,100,100,RED);
        
        sleep_ms(250);
        draw_circle(200,200,20,GREEN);
        
        sleep_ms(250);
        draw_circle(400,200,10, GREEN);
        key = getkey();
        if (key == 'q') {
            clear_screen();
            exit_graphics();
        }
    }
    return 0;
}

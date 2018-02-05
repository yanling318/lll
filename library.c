#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int op;
unsigned short *fb_ptr;
unsigned long size;
unsigned long x_len;
unsigned long y_len;
typedef unsigned short color_t;
void init_graphics();
void exit_graphics();
void clear_screen();
char getkey();
void sleep_ms(long ms);
void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_circle(int x, int y, int r, color_t c);

void init_graphics()
{
    struct fb_var_screeninfo var_info;
    struct fb_fix_screeninfo fix_info;
    struct termios term;
     op = open("/dev/fb0", O_RDWR);
    ioctl(op, FBIOGET_VSCREENINFO, &var_info);
    ioctl(op, FBIOGET_FSCREENINFO, &fix_info);
    x_len = var_info.xres_virtual;
    y_len = var_info.yres_virtual;
    size = fix_info.line_length;
    fb_ptr = (unsigned short *)mmap(NULL, x_len * size,
                                    PROT_WRITE, MAP_SHARED, op, 0);
    ioctl(STDIN_FILENO, TCGETS, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    ioctl(STDIN_FILENO, TCSETS, &term);
}

void exit_graphics()
{
    munmap(fb_ptr, y_len * size);
    struct termios term;
    ioctl(STDIN_FILENO, TCGETS, &term);
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    ioctl(STDIN_FILENO, TCSETS, &term);
    close(op);
}

void clear_screen()
{
    write(1, "\033[2J", 8);
}

char getkey()
{
    char input_key;
    fd_set a;
    struct timeval c;
    FD_ZERO(&a);
    FD_SET(0, &a);
    c.tv_sec = 5;
    c.tv_usec = 0;
    int select_r = select(STDIN_FILENO+1, &a, NULL, NULL, &c);
    if (select_r > 0)
    {
        read(0, &input_key, sizeof(input_key));
    }
    return input_key;
}

void sleep_ms(long ms)
{
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;
    nanosleep(&t, NULL);
}

void draw_pixel(int x, int y, color_t color)
{
    if (x < 0 || x >= x_len || y < 0 || y >= y_len)
    {
        return;
    }
    unsigned long v = (size/2) * y;
    unsigned long h = x;
    unsigned short *ptr = ( fb_ptr + v + h);
    *ptr = color;
}


void draw_rect(int x1, int y1, int width, int height, color_t c)
{
    int x, y;
    for (x = x1; x < x1+width; x++)
    {
        for (y = y1; y < y1+height; y++)
        {
            if (x == x1 || x == x1+width-1)
            {
                draw_pixel(x, y, c);
            }
            if (y == y1 || y == y1+height-1)
            {
                draw_pixel(x, y, c);
            }
        }
    }
}


void draw_circle(int x, int y, int r, color_t c)
{
    int i;
    for (i = r; i > 0; i--)
    {
        int xx = i;
        int yy = 0;
        int x0 = x;
        int y0 = y;
        int b = 1 - xx;
   
        while (yy <= xx)
        {
            draw_pixel( xx+x0, yy+y0, c);
            draw_pixel( yy+x0, xx+y0, c);
            draw_pixel( -xx+x0, yy+y0, c);
            draw_pixel( -yy+x0, xx+y0, c);
            draw_pixel( -xx+x0, -yy+y0, c);
            draw_pixel( -yy+x0, -xx+y0, c);
            draw_pixel( xx+x0, -yy+y0, c);
            draw_pixel( yy+x0, -xx+y0, c);
            yy++;
            if (b <= 0)
            {
                b += 2 * yy + 1;
            }
            else
            {
                xx--;
                b+= 2 * (yy - xx) +1;
            }
        }
    }
}


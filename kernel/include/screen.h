// vga_driver.h
// The driver for the VGA screen

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile* char VRAM = (volatile * char)0xB8000;

// print_string:
// print a string to a specifc position on the screen
extern void print_string(char* text, int x, int y)
{
	
    for (char* c = text; c != '\0'; c++)
	{
		*(VRAM + 2*x + 2*(y * VGA_WIDTH)) = c; 
    }
}

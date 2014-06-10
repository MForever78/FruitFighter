#include <graphics.h>

void clear_display(void)
{
   setvisualpage(1);
   cleardevice();
   setvisualpage(0);
   cleardevice();
}

void prepare_display(void)
{
   setactivepage(!_visual_page);
   cleardevice();
}

void flip_display(void)
{
   setvisualpage(!_visual_page);
}

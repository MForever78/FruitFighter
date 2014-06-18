#include "var.h"

void interrupt int_9h(void)
{
   int k;
   k = inportb(0x60);
   disable();
   if(k != 0xE0 && k != 0xE1) // 0xE0 and 0xE1 are prefixing key codes
   {
      if((k & 0x80) != 0) { // KeyUp
         key[k&0x7F] = 0; // This key is released
         anykey = 0;
      }
      else {                // KeyDown
         key[k] = 1;      // This key is held down
         anykey = 1;
      }
   }
   if(k == 0x81) /* if Esc is released */
       stop = 1;
   enable();
   outportb(0x20, 0x20);
}

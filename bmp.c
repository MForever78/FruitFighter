#include <graphics.h>
#include <stdio.h>

int load_24bit_bmp(int x, int y, char *filename)
{
   FILE *fp = NULL;
   byte *p = NULL; /* pointer to a line of bmp data */
   byte *vp = _vp + (_active_page*_page_gap + y*_width + x) * (_color_bits/8);
   dword width, height, bmp_data_offset, bytes_per_line, offset;
   int i;
   p = malloc(1024L * 3);  /* memory for holding a line of bmp data */
   if(p == NULL)  /* cannot allocate enough memory for drawing 1 line */
      goto display_bmp_error;
   fp = fopen(filename, "rb");
   if(fp == NULL) /* cannot open bmp file */
      goto display_bmp_error;
   fread(p, 1, 0x36, fp);     /* read BMP head */
   if(*(word *)p != 0x4D42)   /* check BMP signature */
      goto display_bmp_error; /* not a BMP file */
   if(*(word *)(p+0x1C) != 24)
      goto display_bmp_error; /* not a 24-bit-color BMP file */
   width = *(dword *)(p+0x12);
   height = *(dword *)(p+0x16);
   bmp_data_offset = *(dword *)(p+0x0A);
   fseek(fp, bmp_data_offset, SEEK_SET); /* skip BMP head */
   bytes_per_line = (width * 3 + 3) / 4 * 4; /* must be multiple of 4 */
   for(i=height-1; i>=0; i--)          /* draw from bottom to top */
   {
      fread(p, 1, bytes_per_line, fp); /* read a line of bmp data */
      offset = i * 1024 * 3;
      memcpy(vp+offset, p, width*3);
   }
   free(p);
   fclose(fp);
   return 1;
display_bmp_error:
   if(p != NULL)
      free(p);
   if(fp != NULL)
      fclose(fp);
   return 0;
}
#include "var.h"

int  build_pic_from_bmp(char *dir, PIC ppic[])
{
   struct _finddata_t fileinfo;
   long handle, h;
   int i;
   char filename[256];
   handle = _findfirst( "bmp\\*.bmp", &fileinfo );
   if(handle == -1)
      return 0;
   h = handle;
   i = 0;
   while(h != -1)
   {
      sprintf(filename, "bmp\\%s", fileinfo.name);
      build_this_pic(filename, &ppic[i]);
      h = _findnext(handle, &fileinfo);
      i++;
   }
   _findclose(handle);
   return i;
}

void build_this_pic(char *filename, PIC *p)
{
   FILE *fp;
   long len;
   byte *pbuf, *q;
   long *color;
   dword bmp_data_offset;
   int width, height, bytes_per_line, i;
   fp = fopen(filename, "rb");
   len = get_file_len(fp);
   pbuf = malloc(len);
   fread(pbuf, 1, len, fp);
   fclose(fp);
   width = *(dword *)(pbuf+0x12);
   height = *(dword *)(pbuf+0x16);
   bmp_data_offset = *(dword *)(pbuf+0x0A);
   bytes_per_line = (width * 3 + 3) / 4 * 4;
   p->mask = malloc(imagesize(0, 0, width-1, height-1));
   p->img = malloc(imagesize(0, 0, width-1, height-1));
   p->mask->picwidth = width;
   p->mask->picheight = height;
   p->img->picwidth = width;
   p->img->picheight = height;
   q = &p->img->buffer;
   for(i=height-1; i>=0; i--)
   {
      memcpy(q, pbuf+bmp_data_offset+i*bytes_per_line, width * 3);
      q += width * 3;
   }
   memcpy(&p->mask->buffer, &p->img->buffer, width*height*3);
   q = &p->mask->buffer;
   for(i=0; i<width*height; i++)
   {
      color = (long *)q;
      if ((*color & 0xFFFFFF00) != 0xFFFFFF00) {
         *color |= 0xFFFFFF00;
      } else {
         *color &= 0x000000FF;
      }
      q += 3;
   }
   free(pbuf);
}

long get_file_len(FILE *fp)
{
   long len;
   fseek(fp, 0, SEEK_END);
   len = ftell(fp);
   fseek(fp, 0, SEEK_SET);
   return len;
}

void draw_picture(PIC p, int x, int y)
{
   if(x<0 || y < 0 || x>=_width || y>=_height) return;
   putimage(x, y, p.mask, OR_PUT);
   putimage(x, y, p.img, AND_PUT);
}

void clear_picture(struct picture *p)
{
   memset(&p->buffer, 0, p->picwidth * p->picheight * 3);
}

void destroy_pictures(void)
{
   int c;
   for (c=0; c < pictures; c++)
   {
      free(pic[c].img);
      free(pic[c].mask);
   }
}

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <io.h>

typedef struct _RGB
{
    byte red, green, blue;
} RGB;

typedef struct _PIC
{
    struct picture *img;
    struct picture *mask;
} PIC;

int  build_pic_from_bmp(char *dir, PIC ppic[]);
void build_this_pic(char *filename, PIC *p);
long get_file_len(FILE *fp);
void get_palette_from_bmp(char *filename, RGB palette[]);
void set_palette(RGB palette[]);

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
   bytes_per_line = (width + 3) / 4 * 4;
   p->mask = malloc(imagesize(0, 0, width-1, height-1));
   p->img = malloc(imagesize(0, 0, width-1, height-1));
   p->mask->picwidth = width;
   p->mask->picheight = height;
   p->img->picwidth = width;
   p->img->picheight = height;
   q = &p->img->buffer;
   for(i=height-1; i>=0; i--)
   {
      memcpy(q, pbuf+bmp_data_offset+i*bytes_per_line, width);
      q += width;
   }
   memcpy(&p->mask->buffer, &p->img->buffer, width*height);
   q = &p->mask->buffer;
   for(i=0; i<width*height; i++)
   {
      if(*q != 0)
         *q = 0;
      else
         *q = 0x00;
      q++;
   }
   free(pbuf);
}

void get_palette_from_bmp(char *filename, RGB palette[])
{
   FILE *fp;
   long len;
   byte *p;
   int i;
   BMP_PALETTE *pbmp_pal;
   fp = fopen(filename, "rb");
   if(fp == NULL)
      return;
   fseek(fp, 0, SEEK_END);
   len = ftell(fp);
   fseek(fp, 0, SEEK_SET);
   p = malloc(len);
   fread(p, 1, len, fp);
   fclose(fp);
   pbmp_pal = (BMP_PALETTE *)(p+0x36);
   for(i=0; i<256; i++)
   {
      palette[i].red = pbmp_pal[i].red >> 2;
      palette[i].green = pbmp_pal[i].green >> 2;
      palette[i].blue = pbmp_pal[i].blue >> 2;
   }
   free(p);
}

void set_palette(RGB palette[])
{
   int i;
   for(i=0; i<256; i++)
   {
      outportb(0x3C8, i);
      outportb(0x3C9, palette[i].red);
      outportb(0x3C9, palette[i].green);
      outportb(0x3C9, palette[i].blue);
   }
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
   putimage(x, y, p.mask, AND_PUT);
   putimage(x, y, p.img, OR_PUT);
}

void clear_picture(struct picture *p)
{
   memset(&p->buffer, 0, p->picwidth * p->picheight);
}

struct picture * build_mask_from_pic(struct picture *p)
{
   struct picture *q;
   int w, h, i;
   byte *pdot;
   w = p->picwidth;
   h = p->picheight;
   q = malloc(imagesize(0, 0, w-1, h-1));
   q->picwidth = w;
   q->picheight = h;
   memcpy(&q->buffer, &p->buffer, w*h);
   pdot = &q->buffer;
   for(i=0; i<w*h; i++)
   {
      if(*pdot != 0)
         *pdot = 0;
      else
         *pdot = 0x00;
      pdot++;
   }
   return q;
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

struct picture * create_picture(int w, int h)
{
   struct picture *p;
   p = malloc(imagesize(0, 0, w-1, h-1));
   p->picwidth = w;
   p->picheight = h;
   return p;
}

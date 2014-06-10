#define TICKVARS 10
volatile word *ptickvar[TICKVARS]={NULL};
volatile word max_ticks[TICKVARS]={0};
volatile word interval[TICKVARS]={0};
volatile word max_interval[TICKVARS]={0};

void interrupt int_8h(void)
{
   int i;
   for(i=0; i<TICKVARS; i++)
   {
      if(ptickvar[i] == NULL)
         continue;
      if(--interval[i] == 0)
      {
         interval[i] = max_interval[i];
         ++*ptickvar[i];
         if(max_ticks[i] != 0 && *ptickvar[i] == max_ticks[i])
         {
            *ptickvar[i] = 0;
         }
      }
   }
   outportb(0x20, 0x20);
}

int install_tickvar(volatile word *p, word minterval, word mticks)
{
   int i;
   for(i=0; i<TICKVARS; i++)
   {
      if(ptickvar[i] == NULL)
      {
         disable();
         ptickvar[i] = p;
         max_interval[i] = minterval;
         interval[i] = minterval;
         max_ticks[i] = mticks;
         enable();
         return i;
      }
   }
   return -1;
}

void uninstall_tickvar(int i)
{
   if(i<0 || i>=TICKVARS)
      return;
   disable();
   ptickvar[i] = NULL;
   enable();
}

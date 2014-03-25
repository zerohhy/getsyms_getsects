#include<unistd.h>
#include<bfd.h>
#include<string.h>
//#include<stdlib.h>
#include<stdio.h>



size_t itoa (int x, char *s, unsigned base)
{
  //printf ("in itoa\n");
  char *p = s;
  int t = x;
  //flip value, if x is negative
  if (x < 0)
    t = -t;

  //if base is smaller than 10
  if (base <= 10)
  {
    do
    {
      *p++ = '0' + t % base;
      t /= base;
    }
    while (t);
    // add negative sign
    if (x < 0)
      *p++ = '-';
  }
  else if (base >= 10)
  {
    do
    {
      if (t % base < 10)
      {
        *p++ = '0' + t % base;
        t /= base;
      }
      else
      {
        *p++ = 'A' + (t % base - 10);
        t /= base;
      }
    }
    while (t);

    //put hexadecimal sign if base = 16
    if (base == 16)
    {
      *p++ = 'x';
      *p++ = '0';
    };

    // add negative sign
    if (x < 0)
      *p++ = '-';
  }
  //digits 
  size_t size = p - s;
  while (s < --p)
  {
    char t = *s;
    *s++ = *p;
    *p = t;
  }
  return size;
}


void print_int (int x, unsigned base)
{
  //printf ("print_int\n");
  char buf[100];
  size_t n = itoa (x, buf, base);
  //printf("itoa(%d) = %.*s.\n", x, (int) n, buf);
  write (1, buf, n);
  for(n;n<=11;n++){ write(1," ",1);}
  write (1, "  ", 2);
}



void getsects(bfd *file){

  
  char print;
  asection *p;

  //Idx Name          Size      VMA               LMA               File off  Algn
  void *print_section (bfd * obj, asection * sect)
  {
    //printf ("print_section\n");
    //printf ("%s %x %x %x\n", sect->name, sect->size, sect->vma, sect->rawsize,sect->filepos);
    
    int cnt = write (1, sect->name, sizeof(sect->name));
    //for(cnt; cnt<=18; cnt++){ write(1," ",1);}

  write(1,"     ",5);
  print_int(sect->lma,16);
    print_int(sect->rawsize,16);
  print_int(sect->size,16);
  print_int(sect->filepos,16);
    write(1,"\n",1);
  }
  

  write(1,"NAME        ",sizeof("NAME       "));
  write(1,"VMA           ",sizeof("VMA           "));
  write(1,"RAW SIZE     ",sizeof("RAW SIZE     "));
  write(1,"SIZE           ",sizeof("SIZE           "));
  write(1,"File Pos  \n",sizeof("File Pos  \n"));
  
  
  
  for (p = file->sections; p != NULL; p = p->next)
  {
    print_section (file, p);
  }



}







#include<unistd.h>
#include<bfd.h>
#include<string.h>
//#include<stdlib.h>
#include<stdio.h>



//extern size_t itoa (int x, char *s, unsigned base);
//extern void print_int (int x, unsigned base);
extern void getsects(bfd *file);

 
int
main (int argc, const char *argv[])
{
  bfd *file;
  bfd_init ();
  char *default_target = "elf64-x86-64";	//"elf64-x86-64" ;
  file = bfd_openr (argv[1], default_target);
  if (file != NULL)
  {
    //printf ("open bfd\n");
    //write(1,argv[1],sizeof(argv[1]));
	write(1," opened\n",sizeof(" opened\n"));
  }
  if (bfd_check_format (file, bfd_object))
  {
    //printf ("format checked\n");
    write(1,"format checked\n",sizeof("format checked\n"));
  }
getsects(file);
bfd_close(file);
}



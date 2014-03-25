#include<unistd.h>
#include<bfd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<dlfcn.h> 
#include<string.h>

extern void print_int(int x, unsigned base );
extern void getsects(bfd *file);

#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))


int main(int argc, char *argv[])
{
  unsigned long long start, finish;
  void *handle;
  void (*func)(bfd *obj);
  char *error;
  char *err;

  bfd *file;
  bfd_init ();
  char *default_target = "elf64-x86-64";  //"elf64-x86-64" ;
  file = bfd_openr (argv[1], default_target);
  if (file != NULL)
  {
    write(1," opened\n",sizeof(" opened\n"));
  }

  if (bfd_check_format (file, bfd_object))
  {
    //printf ("format checked\n");
    write(1,"format checked\n",sizeof("format checked\n"));
  }
  //  _bfd_new_bfd();

  int flag_num = 1;
  char *NOW = "2";
  char *flag = argv[2];
  if(strcmp(flag,NOW) == 0){
    flag_num = 2; 
    write(1, "Setting flag to RTLD_NOW\n",sizeof("Setting flag to RTLD_NOW\n"));
  }
  else{
    write(1, "Use default flag:RTLD_LAZY\n",sizeof("Use default flag:RTLD_LAZY\n"));    
  }  


  rdtsc(&start);    
  handle = dlopen("./libobjdata.so",iflag); // 1 = LAZY , 2 = NOW
  if (!handle) {
    fputs (dlerror(), stderr);
    exit(1);
  }
  dlclose(handle);
  rdtsc(&finish);

  write(1,"\nstart: ", sizeof("\nstart: "));
  print_int(start, 10);

  write(1,"\nfinished: ", sizeof("\nfinished: "));
  print_int(finish, 10);
  
  write(1,"\nrdtsc time: ", sizeof("\nrdtsc time: "));
  int sec = (finish-start)/2500000000;
  print_int(sec, 10); 


  func = dlsym(handle, "getsects");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }  
  getsects(file);


  dlclose(handle);
  bfd_close (file);

}




#include<unistd.h>
#include<bfd.h>
#include<string.h>
#include<stdlib.h>
//#include<stdio.h>



extern void print_int (int x, unsigned base);

void getsyms(bfd *file){

  
  long symtab_upper_bound = bfd_get_symtab_upper_bound (file);
  asymbol **p;
  long symbol_count;
  int i;

  if (symtab_upper_bound <= 0){
    write(1,"Error no symbols in the object file \n",sizeof("Error no symbols in the object file \n"));
    exit(-1);
  }
  write(1,"symtab_upper_bound checked\n",sizeof("symtab_upper_bound checked\n"));

  p = (asymbol **) malloc (symtab_upper_bound);
  symbol_count = bfd_canonicalize_symtab (file, p);

  if (symbol_count < 0){
    write(1,"Can't find symbols\n",sizeof("Can't find symbols\n"));
    exit(-1);
  }
  write(1,"symbol_count checked\n",sizeof("symbol_count checked\n"));



  write(1,"VMA                   ",sizeof("VMA                  "));
  write(1,"NAME        \n",sizeof("NAME       \n"));

  for (i = 0; i < symbol_count; i++) {
    print_int(p[i]->section->vma+p[i]->value,16);
    write(1,"        ",8);
    write(1,p[i]->name,strlen(p[i]->name));
    write(1,"    \n",6);
  }
}    
















































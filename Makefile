$(shell export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH)

#gcc getsections.c objsect.c -lbfd

#gcc getsyms.c objsym.c -lbfd


#getsects: objsect.c
#	gcc objsect.c  -l bfd -o $@



PROGS = getsections getsyms getsections_dl getsyms_dl
OBJS = objsect.o objsym.o
LIBS = libobjdata.so
all: $(LIBS) $(PROGS) $(OBJS)


libobjdata.so: objsect.o objsym.o
	gcc -shared -o $@ objsect.o objsym.o

objsect.o: objsect.c
	gcc -fPIC -c objsect.c

objsym.o: objsym.c
	gcc -fPIC -c objsym.c

	
getsections: getsections.c 
	gcc -o $@ getsections.c -lbfd -L. -lobjdata

getsyms: getsyms.c 
	gcc -o $@ getsyms.c -lbfd -L. -lobjdata

getsections_dl: getsections_dl.c
	gcc -o $@ getsections_dl.c -lbfd -L. -lobjdata -ldl

getsyms_dl: getsyms_dl.c 
	gcc -o $@ getsyms_dl.c -lbfd -L. -lobjdata -ldl






#objsym.o: objsym.c
#	gcc -fPIC -c objsym.c

	

#getsections_dl: getsections_dl.c 
#	gcc -o $@ getsections_dl.c -lbfd -L. -lobjdata -ldl




#getsyms: getsyms.c 
#	gcc -o $@ getsyms.c -lbfd -L. -lobjdata




#to make a static lib
#libobjdata.a: objsect.o objsym.o
#	ar rc libobjdata.a objsect.o objsym.o
#	ranlib libobjdata.a



clean:
	rm -f *.0 *~ *.so $(PROGS)

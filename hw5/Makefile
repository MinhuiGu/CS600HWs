CC=gcc
CXX=c++
CFLAGS=-ggdb -I. 
LDFLAGS=-L. -lcs600

OBJ=timer.o random_generator.o dynprog.o

#
# if yo want to use gcc $(CC) instead of c++ $(CXX), then simply replace
# $(CXX) with $(CC) in the following rules 
# cs600: ...
# .c.o: ...
#
cs600:	libcs600.a main.o
	$(CXX) $(CFLAGS) main.o -o hw5 $(LDFLAGS)

libcs600.a:	$(OBJ)
	ar ru libcs600.a $(OBJ)
	ranlib libcs600.a

.cc.o:
	$(CXX) -c $(CFLAGS) $<


clean:
	@rm -f *.o
	@rm -f libcs600.a
	@rm -f hw5


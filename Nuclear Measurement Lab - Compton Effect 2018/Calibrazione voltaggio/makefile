LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

all: gauss

gauss: gauss_pol.C
	g++ gauss_pol.C -o gauss ${INCS} ${LIBS}

esegui: 
	./gauss
clean:
	rm -f gauss

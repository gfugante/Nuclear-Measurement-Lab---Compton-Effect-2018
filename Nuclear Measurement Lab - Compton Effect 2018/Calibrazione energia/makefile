LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
C:=regressione.C
O:=regressione.o
N:=regressione

all: ${N}

${N}: ${O}
	g++ -o ${N} ${O} ${INCS} ${LIBS}

${O}: ${C}
	g++ -c ${C} -o ${O} ${INCS}

clean:
	rm -f ${N} ${O} 

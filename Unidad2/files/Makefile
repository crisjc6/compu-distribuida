# Makefile para programas sum (cap 2)

FILESC= fileconc.c
FILESO= fileconc.o
FILES1C= fileconc1.c
FILES1O= fileconc1.o
FILES2C= fileconc2.c
FILES2O= fileconc2.o

ALLOBJ= fileconc.o fileconc1.o fileconc2.o

all:    fileconc fileconc1 fileconc2

fileconc:        $(FILESO)
	cc -o fileconc $(FILESO)

fileconc1:        $(FILES1O)
	cc -o fileconc1 $(FILES1O)

fileconc2:        $(FILES2O)
	cc -o fileconc2 $(FILES2O)

clean:	
	rm -f $(ALLOBJ)

all: mos6502

mos6502: main.o operaciones.o status.o dicc.o direccionamiento.o mos6502.o
	gcc -Wall -std=c99 -pedantic -g  main.o operaciones.o status.o dicc.o direccionamiento.o mos6502.o -o mos6502

main.o: main.c operaciones.h status.h direccionamiento.h dicc.h mos6502.h
	gcc -Wall -std=c99 -pedantic -g -c main.c

operaciones.o: operaciones.c operaciones.h 
	gcc -Wall -std=c99 -pedantic -g -c operaciones.c

dicc.o: dicc.c dicc.h 
	gcc -Wall -std=c99 -pedantic -g -c dicc.c

status.o: status.c status.h
	gcc -Wall -std=c99 -pedantic -g -c status.c

direccionamiento.o: direccionamiento.c direccionamiento.h 
	gcc -Wall -std=c99 -pedantic -g -c direccionamiento.c

mos6502.o: mos6502.c mos6502.h
	gcc -Wall -std=c99 -pedantic -g -c mos6502.c
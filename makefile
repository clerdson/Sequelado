all : Sequelado.c
	gcc Sequelado.c -o base `pkg-config --cflags --libs gtk+-3.0` -I/usr/include/postgresql -L/usr/include/postgres -lpq
   
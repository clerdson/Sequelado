all : Sequelado.c
	gcc Sequelado.c do_exit.c create.c -o Sequelado `pkg-config --cflags --libs gtk+-3.0` -I/usr/include/postgresql -L/usr/include/postgres -lpq


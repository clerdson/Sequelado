#include<stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>




int main() {

int lib_ver = PQlibVersion();
printf("Version of libpq:%d\n",lib_ver);    


return 0;
}

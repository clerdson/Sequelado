#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include <stdlib.h>
#include "do_exit.h"
#include "create.h"



void create(PGresult *res,PGconn *conn);



int main(int argc,char *argv[]) {

  GtkWidget *window;
  GtkWidget *vbox;
  
  GtkWidget *toolbar;
  GtkToolItem *newTb;
  GtkToolItem *openTb;
  GtkToolItem *saveTb;
  GtkToolItem *sep;
  GtkToolItem *exitTb;

PGresult *res;
int nFields; 
int i,j;
 
PGconn *conn =PQconnectdb("host=localhost user=postgres dbname=mydb password=root");

if(PQstatus(conn)==CONNECTION_BAD){
printf("connection to database failed:%s\n",PQerrorMessage(conn));

do_exit(conn);
}
int ver = PQserverVersion(conn);
printf("Server version %d\n",ver);

/*
*create database

res = PQexec(conn,"create database casa");
if(PQresultStatus(res)!=PGRES_COMMAND_OK){
printf("create database failed:%s\n",PQerrorMessage(conn));
}else{
printf("create database\n");
}*/

create(res, conn);

res = PQexec(conn,"create table cars(name varchar(30),id_car integer)");
if(PQresultStatus(res)!=PGRES_COMMAND_OK){
printf("create table failed:%s\n",PQerrorMessage(conn));
}else{
printf("create table successfuly\n");
}

/*
*Start with begin
*/
res = PQexec(conn,"BEGIN");
if(PQresultStatus(res)!=PGRES_COMMAND_OK)
{
printf("BEGIN command failed :%s",PQerrorMessage(conn));
}

/*
*create select in table 
*/
res = PQexec(conn,"declare myportal cursor for select*from casa");
if(PQresultStatus(res)!=PGRES_COMMAND_OK){
printf("erro ocorreu in %s \n",PQerrorMessage(conn));
}

res = PQexec(conn,"fetch all in myportal");
if(PQresultStatus(res)!=PGRES_TUPLES_OK){
printf("fethc all falho %s",PQerrorMessage(conn));
}
/*
*primeiroimprimir os nomes dos atributos
*/

nFields = PQnfields(res);
for(i=0;i<nFields;i++){
printf(" | %s |",PQfname(res,i));
}
printf ("\n\n");
printf("LINHAS \n");
/*
*next,print rows
*/
for (i=0;i<PQntuples(res);i++){
for(j=0;j<nFields;j++){
printf("--------\n");
printf("%s",PQgetvalue(res,i,j));
printf("\n");
}
printf("\n");
}


gtk_init(&argc,&argv);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window),"Sequelado");
gtk_container_set_border_width(GTK_CONTAINER(window),10);
gtk_widget_set_size_request(window,200,200);


 vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  toolbar = gtk_toolbar_new();
  gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

  newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);

  openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);

  saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);

  sep = gtk_separator_tool_item_new();
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1); 

  exitTb = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitTb, -1);

  gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

  g_signal_connect(G_OBJECT(exitTb), "clicked", 
        G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

gtk_widget_show_all(window);

//finish PQ and GTK
gtk_main();
PQclear(res);
PQfinish(conn);


return 0;
}



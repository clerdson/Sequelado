#include <stdio.h>
#include <gtk/gtk.h>
#include <libpq-fe.h>
#include <stdlib.h>
#include "do_exit.h"
#include "create.h"

//void do_exit(PGconn *conn){
//PQfinish(conn);
//exit(1);
//}

void create(PGresult *res,PGconn *conn);

int main() {

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




PQclear(res);
PQfinish(conn);


return 0;
}

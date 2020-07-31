#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void create(PGresult *res,PGconn *conn){

res = PQexec(conn,"create database casa");
if(PQresultStatus(res)!=PGRES_COMMAND_OK){
printf("create database failed :%s\n",PQerrorMessage(conn));
}else{
printf("create database");
}

}

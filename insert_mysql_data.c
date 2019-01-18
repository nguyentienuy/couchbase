/*
 * insert mysql db.c
 *
 *  Created on: Jan 16, 2019
 *      Author: UyNT2 + CuongDD4 + ThangNC
 *      Guide to build: gcc -g  -o db_run.out -L/usr/lib64/mysql -lmysqlclient main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MAX_KI 3
#define MAX_NV 10000
#define MAX_KI_RESULT 100000000
#define NUM_FILE_SPLIT 100
#define MONTH 13

int generate_ran_number( int max );

int generate_ran_number( int max ) {
	int r = rand() ;
	return (r % max );
}
const char* KI [] ={"A","B","C","D"};

int main(void)
{
  MYSQL *conn;

  if ((conn = mysql_init(NULL)) == NULL)
  {
    fprintf(stderr, "Could not init DB\n");
    return EXIT_FAILURE;
  }
  if (mysql_real_connect(conn, "172.16.28.71", "root", "Msc@2014", "test", 0, NULL, 0) == NULL)
  {
    fprintf(stderr, "DB Connection Error\n");
    return EXIT_FAILURE;
  }

  char str_sql_insert[100000],str_tmp[30];
  int i,j;
  int n=1000,m=100000;//Staff KI
  int count=0;
  int year=1;
  int SPLIT_YEAR=MAX_KI_RESULT/NUM_FILE_SPLIT;
  for(j=1;j<m;j++){
	  strcat(str_sql_insert,"INSERT INTO ki_history (MA_NV,KI,MONTH_KI,YEAR_KI) VALUES ");
	    for(i=1;i<n;i++){
	    	count++;
	  	  if(i==n-1){
	  		  sprintf(str_tmp,"(%d,'%s',%d,%d)",i%MAX_NV, KI[generate_ran_number(MAX_KI)],i%MONTH,year);
	  	  }else{
	  		  sprintf(str_tmp,"(%d,'%s',%d,%d),",i%MAX_NV, KI[generate_ran_number(MAX_KI)],i%MONTH,year);
	  	  }
	  	  strcat(str_sql_insert,str_tmp);
	  	  if(count%SPLIT_YEAR==0){
				year++;
			}
	    }
//	    printf("String_Query: %s\n",str_sql_insert);
	    printf("Preparing insert into database....\n");

	    if (mysql_query(conn, str_sql_insert) != 0)
	    {
	      fprintf(stderr, "Query Failure\n");
	      return EXIT_FAILURE;
	    }
	    printf("sleeping 10 u_second...\n");
	    memset(str_sql_insert,0,strlen(str_sql_insert));
	    usleep(10);
  }
  
  n=1000,m=100;//Staff
  count=0;
  for(j=1;j<m;j++){
	  strcat(str_sql_insert,"INSERT INTO nhan_vien (MA_NV,TEN_NV) VALUES ");
	    for(i=1;i<n;i++){
	    	count++;
	  	  if(i==n-1){
	  		  sprintf(str_tmp,"(%d,'Staff_name_%d')",count,count);
	  	  }else{
	  		  sprintf(str_tmp,"(%d,'Staff_name_%d'),",count,count);
	  	  }
	  	  strcat(str_sql_insert,str_tmp);
	    }
//	    printf("String_Query: %s\n",str_sql_insert);
	    printf("Preparing insert into database: nhan_vien....\n");

	    if (mysql_query(conn, str_sql_insert) != 0)
	    {
	      fprintf(stderr, "Query Failure\n");
	      return EXIT_FAILURE;
	    }
	    printf("sleeping 10 u_second...\n");
	    memset(str_sql_insert,0,strlen(str_sql_insert));
	    usleep(10);
  }

  mysql_close(conn);
  return EXIT_SUCCESS;
}

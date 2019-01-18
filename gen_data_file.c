/*
 * gen_data_file.c
 *
 *  Created on: Jan 17, 2019
 *      Author: UyNT2 + CuongDD4 + ThangNC
 *      Guide to build: gcc -g -o gen_data gen_data_file.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

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

#define SAVE_PATH "D:\\tmp"
#define NHAN_VIEN_TABLE "nhan_vien"
#define KI_TABLE "ki_table"
#define SCRIPT_INSERT "script_insert"

int main () {
	int fml, srn, nm;
	FILE* f = NULL;
	char name_file[256] ;
	char buf[1024];
	int i = 0 ;
	int j = 0 ;
	srand(time(NULL)) ;
	sprintf(name_file,"%s/%s", SAVE_PATH, SCRIPT_INSERT ) ;
	f= fopen(name_file,"w") ;
	for(i=0;i<NUM_FILE_SPLIT;i++){
		sprintf(buf,"Command_insert_her_%d\n",i) ;
		fputs(buf, f);
	}
	fclose(f) ;

	sprintf(name_file,"%s/%s", SAVE_PATH, NHAN_VIEN_TABLE ) ;
	f= fopen(name_file,"w") ;
	fputs("Ma_NV,Ho_ten\n",f) ;
	for ( i = 0 ; i < MAX_NV ; i++ ) {
		sprintf(buf,"%d,%s%d\n", i, "staff_Name_",i) ;
		fputs(buf, f);
	}
	fclose(f) ;

	int year=1;
	int count=0;
	int SPLIT_TMP=MAX_KI_RESULT/NUM_FILE_SPLIT;
	for(j=0;j<NUM_FILE_SPLIT;j++){
		sprintf(name_file,"%s/%s_%d", SAVE_PATH, KI_TABLE,j+1 ) ;
		f= fopen(name_file,"w") ;
		fputs("MaNV,KI,Month,Year\n",f) ;
		for ( i = 0 ; i < MAX_KI_RESULT/NUM_FILE_SPLIT ; i++ ) {
			count++;
			sprintf(buf,"%d,%s,%d,%d\n", i%MAX_NV, KI[generate_ran_number(MAX_KI)],i%MONTH,year);
			fputs(buf, f);
			if(count%SPLIT_TMP==0){
				year++;
			}
		}
		fclose(f) ;
	}

}

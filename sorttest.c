#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "xgraph/header/expr.h"
#include <time.h>
#include <err.h>
void add_common_symbols(struct expr_symset *es);
double dtime(void);
struct expr_symset es[1];
volatile sig_atomic_t vssuc;
volatile sig_atomic_t vsi;
void randomize(double *buf,size_t sz){
	if(!sz)sz=1;
	do
		*(buf++)=drand48();
	while(--sz);
}
double rv[10000000];
int main(int argc,char **argv){
	double t3,t,dt;
	size_t from=1,to=UINT_MAX,times=10000;
	switch(argc){
		case 4:
			times=atol(argv[3]);
		case 3:
			to=atol(argv[2]);
		case 2:
			from=atol(argv[1]);
		default:
			break;
	}
	srand48(time(NULL)+getpid());
	srand(time(NULL)+getpid());
	srandom(time(NULL)+getpid());
	for(size_t i=from;i<to;++i,printf("\n")){
		t3=0.0;
		for(size_t j=0;j<times;++j){
			randomize(rv,i);
			dt=dtime();
			expr_sort3(rv,i);
			t3+=dtime()-dt;
		}
		printf("n=%zu\t expr_sort3: %zums",i,(size_t)(t3*1000));
		//continue;
		t=0.0;
		for(size_t j=0;j<times;++j){
			randomize(rv,i);
			dt=dtime();
			expr_sort_old(rv,i);
			t+=dtime()-dt;
		}
		printf("\texpr_sort_old: %zums\t1 : %lg",(size_t)(t*1000),t/t3);
	}
	return 0;
}

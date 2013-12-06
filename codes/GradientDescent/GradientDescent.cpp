/**
*梯度下降法 
*
**/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

const int N = 3;
const double rate = 0.001;
const double err = 0.0000000001;
int M;//实际样本大小 
typedef struct
{
	double x0,x1,x2; //x0 = 1; h(x) = t0*x0 + t1*x1 + t2*x2;
	double y;// 测得的y值 
}node;

node x[100];//样本集

double theta[N] = {0,0,0};//t0,t1,t2

void init()
{
	double x1,x2,y;
	FILE *f = fopen("data.txt","r");
	fscanf(f,"%d",&M);//样本数目
	for(int i = 0; i < M; i++){
		fscanf(f,"%lf %lf %lf",&x1,&x2,&y);
		x[i].x0 = 1;
		x[i].x1 = x1;
		x[i].x2 = x2;
		x[i].y = y;
	} 
	
}

double h(node *x, double *theta)
{
	return x->x0 * theta[0] + x->x1 * theta[1] + x->x2 * theta[2];
}

void show()
{
	for(int i = 0; i < M; i++){
		printf("%.5lf %.5lf %.5lf %.10lf\n", x[i].x1, x[i].x2, x[i].y, h(&x[i], theta));
	}
	
	printf("%.10lf %.10lf %.10lf\n", theta[0], theta[1], theta[2]);
}

double ABS(double x)
{
	return (x - 0.0000000001) > 0 ? x : -x;
}

void Batch()
{
	int cnt = 0;
	
	while(true){
		
		cnt++;
		double sum = 0;
		for(int i = 0; i < N; i++){
			
			for(int j = 0; j < M; j++){
				double temp = 0;
				if (i == 0) temp = x[j].x0;
				if (i == 1) temp = x[j].x1;
				if (i == 2) temp = x[j].x2;
				sum += (x[j].y - h(&x[j], theta)) * temp;
			}
			
			theta[i] += rate * sum;
		
		}
		
		double error = (x[0].y - h(&x[0],theta)) * (x[0].y - h(&x[0],theta));
		
  		if (error < err) {
			printf("It takes %d loops\n",cnt);
			break;
		}
	}
	
}

int main()
{
	
	init();
	Batch();
	
	show();
	return 0;
}

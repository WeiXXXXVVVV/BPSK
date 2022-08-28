#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float rand49()
{  /*rand_max=7FFF (32767) */
	static int Num=0;
    double number;
    int    i;
    i=rand();
    number=(double)(i)/((unsigned) (RAND_MAX+1));
    Num++;
    if (Num >=RAND_MAX){
		time_t t;
		t=time(NULL);
//		srand((unsigned)(t%RAND_MAX));
        Num=0;
    }
    return (float)number;
}

double normal()
{
	static int iset=0;
    static double qset;
    double vx,vy,r,temp;
    if (iset==0)//noise=normal*deviate
    {
	    do
        {
		    vx=2.0*rand49()-1.0;
            vy=2.0*rand49()-1.0;
            r =vx*vx+vy*vy;
        }while (r >=1.0 || r==0);
        temp=sqrt(-2.0*log(r)/r);
        qset=vy*temp;
        iset=1;
        return (vx*temp);
    }
    else
    {
   	    iset=0;
        return qset;
    }
}

int main(int argc, char *argv[]) {
srand(time(NULL));
	int i,snr_dB,a=0;
	 double ber,x,y,err=0.0,tx=0.0;


   for(snr_dB=0;snr_dB<13;snr_dB++)
   {   
    double snr=pow(10,snr_dB*0.1);
	double N0=1/snr;
    while(err<=100)
    {
    tx++;
    x=rand()%2;
    //printf("%f\n",x);
    if(x==0)
    {
    x=-1;
	}
	y=x+sqrt(0.5*N0)*normal();
	//printf("%f\n",x);
	if(y<=0)
	{
	y=-1;
	}
	else
	{
	y=1;
	}
	//	printf("%f %f\n",x,y);
	if(x!=y)
	{
	err++;
	}

	}ber=(err)/tx;	
	//printf("%d %f",a,err);
	
	printf("SNR %d dB ¿ù»~²v %e\t  ¿ù%f bits ¶Ç%f bits \n ",snr_dB,ber,err-1,tx);
//printf(" %e  \t ",ber);
	err=0;
	tx=0;
}
	
	return 0;
}

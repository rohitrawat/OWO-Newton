/*****************************************************************************
 random.cpp

 author : Tae

C*******************************************************************
C
C       Originally from  : RAND1.FORC       Date:	 29 FEB 1996	University of Texas of Arlington, Texas 76010
C
C       FUNCTION RAND1 GENRATES RANDOME NUMBERS DEPENDING ON THE SEED PASSED TO IT AND THE SEEDS ARE STATIC DATA PASSED
C       FUNCTION SLETE GENERATES GAUSSIAN RANDOM NUMBERS , USING THE UNIFORM RANDOM NUMBERS GENERATED BY THE FUNCTION RAND1, FOR
C       A GIVEN STANDARD DEVIATION AND MEAN FOR THE RANDOM NUMBER
C
C       VARIABLES       IX,IY,IZ             INTEGER
C                       STD, XMEAN           REAL   
C       IX,IY,IZ   :    GLOBAL SEEDS  ; 0 < ... < 30000 *
*****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "random.h"
#include <iostream>
#include <algorithm>
#include <vector>
typedef std::pair<double,int> mypair;

bool comparator(const mypair& left, const mypair& right)
{
  return (left.first < right.first);
};

extern "C" double genrand_real3(void);
const double PI=(atan(1.0)*4);
//const int SEED1=3,SEED2=4009,SEED3=234;//seed # 1 
//int IX=163,IY=4057,IZ=2179;// seed # 2 
//int IX=11,IY=4799,IZ=2621;// seed # 3 
int IX=463,IY=17351,IZ=20269;// seed # 4 
//const int SEED1=2141,SEED2=24001,SEED3=6257;// seed # 5 
//const int SEED1=8297,SEED2=19,SEED3=1153;// seed # 6 
//const int SEED1=27241,SEED2=26119,SEED3=3;// seed # 7 
//const int SEED1=15461,SEED2=31,SEED3=79;/// seed # 8 
//const int SEED1=13757,SEED2=10639,SEED3=16433;// seed # 9 
//const int SEED1=18401,SEED2=5903,SEED3=1627; //seed #10

std::vector<int> randperm(int N)
{
   std::vector<mypair> permutations;
   std::vector<int> return_vals;
   mypair thePair;
   int i;

   for (i=0;i<N;i++)
   {
         thePair.first=genrand_real3();
         thePair.second=i;
         permutations.push_back(thePair);
   }
   sort(permutations.begin(),permutations.end(),comparator);
   for (i=0;i<N;i++)
       return_vals.push_back(permutations[i].second);
   return(return_vals);
}
/******************************************************************************/
//	rand1 produces uniformly distributed random numbers 'een 0 & 1. 
//	(according to observation of its outputs)
/******************************************************************************/
double rand1(int *ix, int *iy, int *iz)
{
       int ixx, iyy, izz;
       double itemp;
       double temp;


       ixx=(*ix)/177;
       *ix=171*(*ix%177)-2*ixx;

       if(*ix < 0)
               *ix+=30269;

       iyy=(*iy)/176;
       *iy=176*(*iy%176)-2*iyy;

       if(*iy < 0)
               *iy+=30307;

       izz=(*iz)/178;
       *iz=170*(*iz%178)-2*izz;

       if(*iz < 0)
               *iz+=30323;

       temp=(double)(*ix)/30629.0+(double)(*iy)/30307.0+(double)(*iz)/30323.0;
       itemp=floor(temp);
       return (temp-itemp);

}
int random_int(int a,int b)
// Returns a random integer in the range of [a,b]
{
    double k=genrand_real3();
    if (a>=b)
    {
       std::cout << "You put the limits in the wrong way" << std::endl;
       exit(0);
    }
    return(a+floor((b-a+1)*k));
}
double slete1(double dstd, double dmean)
{
       double rand1(int *, int *, int *);
       return (dmean+dstd*cos(2*PI*rand1(&IX, &IY, &IZ))*sqrt(-2.0*log(rand1(&IX, &IY, &IZ))));

}
/******************************************************************************/
	/* function slete() generates a gaussian random process by invoking
		rand1() and manipulating the sample returned by it. */
/******************************************************************************/
double slete(double mean, double std)
{
	//double rand1(void);
	double gaussian;

	//gaussian = mean +  std * cos(2*PI*rand1()) * sqrt(-2.0*log(rand1()));
	gaussian = mean + std * cos(2*PI*genrand_real3()*sqrt(-2.0*log(
             genrand_real3())));
	return(gaussian);
}
/***************************************************************************/


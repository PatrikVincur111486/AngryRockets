#include <stdio.h>
#include <stdlib.h>
#define Nmin 10 
#define Nmax 100
#define R_MAX 2147483647

static long long unsigned int SEED = 0x1;

void srnd(int seed) {
  SEED = seed;  }

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);     }

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );}

int max(int a,int b){
  if (a>b){return a;}
  return b;
}

int main()
{
  int n,seed,m1,m2,p1=0,p2=0,i,R1,R2,posA=-1,posB=-1,round=1,d,m2A=0,m2B=0,m2Abef=0,m2Bbef=0,posAbef=-1,posBbef=-1,temp,hs=0;
  scanf("%d %d %d %d",&seed,&n,&m1,&m2);
  int draha[n],pos_Block[m1],pos_Boost[m2],hotspot[n];

  if(seed<=0 || n<Nmin || n>Nmax || ((m1+m2)>(n/2)))    {return 1;}
  srnd(seed);

  for(i=0;i<n;i++){
    draha[i]=0;
    hotspot[i]=0;}

  while (p1!=m1){
        i=rnd(1,n-1);
        if (draha[i]!=1)
            {
            draha[i]=1;
            pos_Block[p1]=i;
            p1++;   }}

  while (p2!=m2){   
        i=rnd(1,n-1);
        if (draha[i]!=1 && draha[i]!=2)
            {
            draha[i]=2;
            pos_Boost[p2]=i;
            p2++;   }}

  qsort(pos_Block,m1,sizeof(int),cmp);
  qsort(pos_Boost,m2,sizeof(int),cmp);

  printf("BLOCK:");
  for( i = 0 ; i < m1; i++ ) {   
      printf("%d ", pos_Block[i]);     }
  printf("\nBOOST:");
  for( i = 0 ; i < m2; i++ ) {   
      printf("%d ", pos_Boost[i]);    }  
  while (posA<n && posB<n)
    { d=0;
      R1=rnd(1,6);
      R2=rnd(1,6);
      if (posA==-1)
        {
          if(R1+R2>7)
          {
          d=R1+R2-6;
          }
          else{d=0;}
        }       
      else {d=max(R1,R2);}

      if ( ((posA>posB && R1==1 && R2==1) || (posA<posB && R1==6 && R2==6)) && (posA>0 && posB>0 && posA<n-1 && posB<n-1) )
        {
          m2Abef=m2A;
          posAbef=posA;
          posBbef=posB;
          temp=posA;
          posA=posB;
          posB=temp;
          d=0;
          hotspot[posA]++;
          hotspot[posB]++;
        }    
      else
        {
          posAbef=posA;
          m2Abef=m2A;
          posA=posA+d+m2A;
          hotspot[posA]++;
        }

      if(posA==posB)
      {
        posBbef=posBbef;
        posAbef=posAbef;
        posB=-1;

      }
      if (draha[posA]==1)
        { 
          draha[posA]=0;
          if (m2A==0) 
            {
              posA=-1;
            }
          else{m2Abef=m2A; m2A=0;}
        }
      if (draha[posA]==2)
        {
          draha[posA]=0;
          m2Abef=m2A;
          m2A++;
        }
      
      printf("\n[%d,1] [%d,%d] [%d,%d] [%d,%d]",round,posAbef,m2Abef,R1,R2,posA,m2A);
      round++;
      if (posA>=n){break;}
//8888888888888888888888888888888888888888888888888888888888888
      d=0;
      R1=rnd(1,6);
      R2=rnd(1,6);
      if (posB==-1)
        {        
          if(R1+R2>7)
            {
              d=R1+R2-6;
            }
          else{d=0;}
        }
      else {d=max(R1,R2);}
      
      if ( ((posB>posA && R1==1 && R2==1) || (posB<posA && R1==6 && R2==6)) && (posA>0 && posB>0 && posA<n-1 && posB<n-1) )
            {
              m2Bbef=m2B;
              posAbef=posA;
              posBbef=posB;
              temp=posA;
              posA=posB;
              posB=temp;
              d=0;
              hotspot[posA]++;
              hotspot[posB]++;
            }
      else 
        {
          posBbef=posB;
          m2Bbef=m2B;
          posB=posB+d+m2B;
          hotspot[posB]++;
        }

      if(posB==posA)
      {
        posBbef=posB;
        posAbef=posA;
        posA=-1;
      }
      if (draha[posB]==1)
        { 
          draha[posB]=0;
          if (m2B==0)
            {
              posB=-1;
            }
          else
            {
              m2Bbef=m2B;m2B=0;
            }
        }
      if (draha[posB]==2)
        {
          draha[posB]=0;
          m2Bbef=m2B;
          m2B++;
        }
      printf("\n[%d,2] [%d,%d] [%d,%d] [%d,%d]",round,posBbef,m2Bbef,R1,R2,posB,m2B);

    
      round++;
    }
  if (posA>=n){printf("\nWINNER:1");}
  else{printf("\nWINNER:2");}
  hs=1;
  
  for(i=1;i<n;i++)
    {
      if (hotspot[i]>hs){hs=hotspot[i];}
    }
  printf("\nHOTSPOT:%d",hs);
  
  return 0;
}
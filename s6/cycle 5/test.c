#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define packetCount 3

int main(){
  srand(time(0));
  int packets[packetCount],i,rate,bucketSize,remainingSize=0,timeToTransmit,clk,op;
  for (i=0;i<packetCount;i+=1)
    packets[i]=(rand()%6+1)*10;
  printf("Enter the output rate:\n");
  scanf("%d",&rate);
  printf("Enter the bucket size:\n");
  scanf("%d",&bucketSize);
  i=0;
  while(i<packetCount || remainingSize>0){
    if (i<packetCount){
      printf("Incoming packet size:%d\n",packets[i]);
      if ((packets[i]+remainingSize)>bucketSize){
        printf("Bucket size exceeded\n");
      } else{
        remainingSize+=packets[i];
        printf("Bytes remaining to transmit:%d\n",remainingSize);
      }
      ++i;
    }
    timeToTransmit=(rand()%4+1)*10;
    printf("Time left to transmit:%d\n",timeToTransmit);
    for (clk=10;clk<=timeToTransmit;clk+=10){
      sleep(1);
      if(remainingSize){
        if(remainingSize<=rate){
          op=remainingSize,remainingSize=0;
        }
        else {
          op=rate,remainingSize-=rate;
        }
        printf("%d packets transmitted\n",op);
        printf("bytes remaing to ttransmit:%d\n",remainingSize);
      }
      else{
        printf("time left for transmission:%d\n",timeToTransmit-clk);
        printf("no packets to transmit\n");
      }
    }
  }
}
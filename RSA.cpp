#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;

int prim(int a){   //judege prim number
	int flag=0;
	
	if(a==2||a==1||a==3)
	 flag=0;
	else{
		for(int i=2;i<a/2+1;i++){
			if(a%i==0){
				flag=1;//has 
				break;
			}
		}
	}
	return flag;  //1:not ; 0:yes prim
}

int gcd(int a,int b){  //ma
	if(b==0)
		return a;
	else 
		return gcd(b,a%b);
} 

int select(int a){  //select e
	int i;
	for(i=2;i<a;i++){
		if(gcd(a,i)==1)
			break;
	}
	if(i==a)
		printf("select error\n");
	else
	 	return i;
}

int dispose(int n,int e){ //calcu d
	int d;
	int t=1;
	while(1){
		if((t*n+1)%e==0)
			break;
		else
		 	t++;
	}
	return (t*n+1)/e;
}

int quickmi(int M,int e,int n){
	if(e==1)
		return M%n;
	if(e==2)
		return (M*M)%n;
	if(e%2==0)
		return (quickmi(M,e/2,n)*quickmi(M,e/2,n))%n;
	else
		return (M*quickmi(M,e-1,n))%n;
}
/* PU={e,n}
	PK={d,n}*/
int main(int argc,char *argv[]){ 
	string line;
	line=argv[1];
	cout<<line;
	srand((unsigned) time(NULL)); 
	int p,q;
	int N;
	int euler;
	int e,d;
	//int input=(int)argv[1];
	
/*get prim*/	
	while(1){
		p=rand()%100+1;
		if(p==1)
			continue;
		if(prim(p)==0)
			break;
	}
	while(1){
		q=rand()%100+1;
		if(q==1)
			continue;
		if(prim(q)==0)
			break;
	}
	
	printf("p q:%d %d\n",p,q);
	N=p*q;
	euler=(p-1)*(q-1);
	e=select(euler);
	d=dispose(euler,e);
	
	int an=quickmi(123,e,N);
	printf("N:%d euler:%d e:%d d:%d\n",N,euler,e,d);
	
	printf("encode: %d\n",an);
	printf("decode: %d",quickmi(an,d,N));
	return 0;
}

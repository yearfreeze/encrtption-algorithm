#include <stdlib.h>
#include <stdio.h>
const char IP_Table[64]={             
	58,50,42,34,26,18,10, 2,60,52,44,36,28,20,12, 4,
	62,54,46,38,30,22,14, 6,64,56,48,40,32,24,16, 8,
	57,49,41,33,25,17, 9, 1,59,51,43,35,27,19,11, 3,
	61,53,45,37,29,21,13, 5,63,55,47,39,31,23,15, 7 
};

const char IPR_Table[64]={              
	40, 8,48,16,56,24,64,32,39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,33, 1,41, 9,49,17,57,25	
};
static char E_Table[48]={
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13,12,13,14,15,16,17,
    16,17,18,19,20,21,20,21,22,23,24,25,
    24,25,26,27,28,29,28,29,30,31,32, 1
};
static char PC1_Table[56]={
	57,49,41,33,25,17, 9, 1,58,50,42,34,26,18,
	10, 2,59,51,43,35,27,19,11, 3,60,52,44,36,
	63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
	14, 6,61,53,45,37,29,21,13, 5,28,20,12, 4
};

// 对C0,D0分别进行左移,共16次,左移位数
static char Move_Table[16]={
	 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
     
static char PC2_Table[48]={
	14,17,11,24, 1, 5, 3,28,15, 6,21,10,
	23,19,12, 4,26, 8,16, 7,27,20,13, 2,
	41,52,31,37,47,55,30,40,51,34,33,48,
	44,49,39,56,34,53,46,42,50,36,29,32	
};

static char S_Box[8][4][16]={
	//S1
	14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
	 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
	 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,
	//S2
	15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
	 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
	 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
	13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,
	//S3
	10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
	13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
	 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,
	//S4
	 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
	13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
	10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
	 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,
	//S5
	 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
	14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
	 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
	11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,
	//S6
	12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
	10,15, 4, 2, 7,12, 0, 5, 6, 1,13,14, 0,11, 3, 8,
	 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
   	 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,
	//S7
	 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
	13, 0,11, 7, 4, 0, 1,10,14, 3, 5,12, 2,15, 8, 6,
	 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
	 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,
	//S8
	13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
	 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
	 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
	 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
};
static char P_Table[32]={
	16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
	 2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
};
static bool SubKey[16][48]={0};

void BitsCopy(bool *DatOut,bool *DatIn,int Len)     // 数组复制  
{
	int i=0;
	for(i=0;i<Len;i++)
	{
		DatOut[i]=DatIn[i];
	}
}

void ByteToBit(bool *DatOut,char *DatIn,int Num)    
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=(DatIn[i/8]>>(i%8))&0x01;   
	}                                       
}
void BitToByte(char *DatOut,bool *DatIn,int Num)       
{
	int i=0;
	for(i=0;i<(Num/8);i++)
	{
		DatOut[i]=0;
	} 
	for(i=0;i<Num;i++)
	{
		DatOut[i/8]|=DatIn[i]<<(i%8);	
	}		
}
void BitToHex(char *DatOut,bool *DatIn,int Num)
{
	int i=0;
	for(i=0;i<Num/4;i++)
	{
		DatOut[i]=0;
	}
	for(i=0;i<Num/4;i++)
	{
		DatOut[i] = DatIn[i*4]+(DatIn[i*4+1]<<1)
					+(DatIn[i*4+2]<<2)+(DatIn[i*4+3]<<3);
		if((DatOut[i]%16)>9)
		{
			DatOut[i]=DatOut[i]%16+'7';      
		}                                     
		else
		{
			DatOut[i]=DatOut[i]%16+'0';       //  输出字符	   
		}
	}
	
}
void HexToBit(bool *DatOut,char *DatIn,int Num)
{
	int i=0;                        
	for(i=0;i<Num;i++)
	{
		if((DatIn[i/4])>'9')         
		{
			DatOut[i]=((DatIn[i/4]-'7')>>(i%4))&0x01;   			
		}
		else
		{
			DatOut[i]=((DatIn[i/4]-'0')>>(i%4))&0x01; 	
		} 
	}	
}
// 表置换函数  OK
void TablePermute(bool *DatOut,bool *DatIn,const char *Table,int Num)  
{
	int i=0;
	static bool Temp[256]={0};
	for(i=0;i<Num;i++)                
	{
		Temp[i]=DatIn[Table[i]-1];  
	}
	BitsCopy(DatOut,Temp,Num);       // 缓存输出 
} 
// 子密钥的移位
void LoopMove(bool *DatIn,int Len,int Num) 
{
	static bool Temp[256]={0};    // 缓存   
	BitsCopy(Temp,DatIn,Num);      
	BitsCopy(DatIn,DatIn+Num,Len-Num); 
	BitsCopy(DatIn+Len-Num,Temp,Num);  
} 

// 按位异或
void Xor(bool *DatA,bool *DatB,int Num)           
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatA[i]=DatA[i]^DatB[i];                  
	}
} 

void S_Change(bool DatOut[32],bool DatIn[48])     
{
	int i,X,Y;                                   
	for(i=0,Y=0,X=0;i<8;i++,DatIn+=6,DatOut+=4)    
	{    										  
		Y=(DatIn[0]<<1)+DatIn[5];                          
		X=(DatIn[1]<<3)+(DatIn[2]<<2)+(DatIn[3]<<1)+DatIn[4]; 
		ByteToBit(DatOut,&S_Box[i][Y][X],4);      
	}
}
void F_Change(bool DatIn[32],bool DatKi[48])       // F函数
{
	static bool MiR[48]={0};            
	TablePermute(MiR,DatIn,E_Table,48); 
	Xor(MiR,DatKi,48);                  
	S_Change(DatIn,MiR);                 
	TablePermute(DatIn,DatIn,P_Table,32);   
}
void SetKey(char KeyIn[8])               
{
	int i=0;
	static bool KeyBit[64]={0};                		 
	static bool *KiL=&KeyBit[0],*KiR=&KeyBit[28];  	
	ByteToBit(KeyBit,KeyIn,64);                    
	TablePermute(KeyBit,KeyBit,PC1_Table,56);      	
	for(i=0;i<16;i++)
	{
		LoopMove(KiL,28,Move_Table[i]);       		
		LoopMove(KiR,28,Move_Table[i]);	      	
	 	TablePermute(SubKey[i],KeyBit,PC2_Table,48); 
	}		
}

void PlayDes(char MesOut[8],char MesIn[8])  		// 执行DES加密
{                                           		// 字节输入 Bin运算 Hex输出 
	int i=0;
	static bool MesBit[64]={0};        				// 明文二进制存储空间 64位
	static bool Temp[32]={0};
	static bool *MiL=&MesBit[0],*MiR=&MesBit[32]; 	// 前32位 后32位 
	ByteToBit(MesBit,MesIn,64);                 	// 把明文换成二进制存入MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);    	// IP置换 
	for(i=0;i<16;i++)                       		// 迭代16次 
	{
		BitsCopy(Temp,MiR,32);           
		F_Change(MiR,SubKey[i]);           
		Xor(MiR,MiL,32);                  
		BitsCopy(MiL,Temp,32);            
	}					
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToHex(MesOut,MesBit,64);
}

void KickDes(char MesOut[8],char MesIn[8])      
{												
	int i=0;
	static bool MesBit[64]={0};        			
	static bool Temp[32]={0};
	static bool *MiL=&MesBit[0],*MiR=&MesBit[32]; 	
	HexToBit(MesBit,MesIn,64);                 		
	TablePermute(MesBit,MesBit,IP_Table,64);    
	for(i=15;i>=0;i--)
	{
		BitsCopy(Temp,MiL,32);
		F_Change(MiL,SubKey[i]);
		Xor(MiL,MiR,32);
		BitsCopy(MiR,Temp,32);
	}	
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToByte(MesOut,MesBit,64);		
} 
int main()
{
	int i=0; 
	char MesHex[16]={0};        
 	char MyKey[8]={0}; 			// 默认秘钥 
	char YourKey[8]={0};         
	char MyMessage[8]={0};       
	printf("mesg:");
	gets(MyMessage);   
	printf("key:");         
	gets(MyKey);                

	SetKey(MyKey);               	
	PlayDes(MesHex,MyMessage); 
	
	printf("secert(16bits):");
	for(i=0;i<16;i++)           
	{
		printf("%c",MesHex[i]);
	}
	printf("\n");
	
	SetKey(MyKey);                                       
	KickDes(MyMessage,MesHex);    
	printf("mesg:");                
	for(i=0;i<8;i++)
	{
		printf("%c",MyMessage[i]);
	}
	printf("\n");	
}










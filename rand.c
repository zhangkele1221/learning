
//密码生成程序 且不能存在111111 或者222222  
//即不能6位完全相同的数字
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void get_sms_code(char *sms,int cnt){
	int number = 0;
	int i =0;
	
	srand ((unsigned)time(NULL));
	while((number % 111111) ==0){
		number =0;
		for(i=0;i<(cnt-1);i++){
			int temp = rand()%10;
			number = number*10+temp;
		}
	}
	sprintf(sms,"%06d",number);
	return ;
}

int main()
{
	char sms_code[7]={};
	memset(sms_code,0x00,sizeof(sms_code));
	get_sms_code(sms_code,sizeof(sms_code));

	printf("%s\n",sms_code);
	return 0;
}








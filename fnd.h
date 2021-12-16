#ifndef __FND_DRV_H__
#define __FND_DRV_H__
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
int counter_10(void); // 10까지 count 숫자 변경 가능
int timeDis(void);   //현재 시간 출력
int fndDisp(int num , int dotflag); //숫자 쓰면 출력됨
int fndOff(void);  // fnd 꺼짐
typedef struct FNDWriteDataForm_tag
{
char DataNumeric[FND_DATA_BUFF_LEN]; //숫자 0-9
char DataDot[FND_DATA_BUFF_LEN]; //숫자 0 or 1
char DataValid[FND_DATA_BUFF_LEN]; //숫자 0 or 1
}stFndWriteForm,*pStFndWriteForm;
#endif// __FND_DRV_H__

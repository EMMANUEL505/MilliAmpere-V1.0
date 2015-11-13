
//int16 sensors_ADC[15],black_limit=730;
int16   sensors_BIN[15],base_speed=900,left_correction,right_correction,last_center,center,last_error,error,derivative,correction;
float   integral=0,KD=450,KP=75,KI=0;
int RUN=0x00,i=0;//
int16 x=0,delay_time=12800,t_speed=1500;
char buffer[50];
//KD=0,KP=125,KI=0,BaseSpeed=700

//2.8 800, 400, 70, 9800
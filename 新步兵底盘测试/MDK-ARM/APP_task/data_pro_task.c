/* ����ͷ�ļ�----------------------------------------------------------------*/
#include "data_pro_task.h"
#include "SystemState.h"
/* �ڲ��궨��----------------------------------------------------------------*/
#define press_times  20
#define VAL_LIMIT(val, min, max)\
if(val<=min)\
{\
	val = min;\
}\
else if(val>=max)\
{\
	val = max;\
}\
//extern osSemaphoreId Dubs_BinarySemHandle;
/* �ڲ��Զ�����������--------------------------------------------------------*/

/* ���������Ϣ����----------------------------------------------------------*/
//extern osMessageQId JSYS_QueueHandle;
/* �ڲ���������--------------------------------------------------------------*/

#define REMOTE_PERIOD 1 

/* �ⲿ��������--------------------------------------------------------------*/

/* ���õ��ⲿ����ԭ������------------------------------------------------------
	uint8_t verify_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength);
	uint8_t verify_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength);
------------------------------------------------------------------------------
*/
/* �ڲ�����------------------------------------------------------------------*/
int16_t XY_speed_max = 2500;
int16_t XY_speed_min = -2500; 
int16_t W_speed_max = 2000;
int16_t W_speed_min = -2000; 
uint8_t press_counter;
uint8_t shot_anjian_counter=0;
uint8_t shot_frequency = 20;
int8_t chassis_gimble_Mode_flg;

/* �ڲ�����ԭ������-----------------------------------------------------------*/

/***************************************************************************************
**
	*	@brief	RemoteControlProcess()
	*	@param
	*	@supplement	��ң�������жԽӣ���ң���������ݽ��д���ʵ�ֶԵ��̡���̨����������Ŀ���
	*	@retval	
****************************************************************************************/
void RemoteControlProcess()  
{
	
					moto_3508_set.dstVmmps_X = ((RC_Ctl.rc.ch0 - 0x400) * 10);   //��ҡ�ˡ�����
					moto_3508_set.dstVmmps_Y = ((RC_Ctl.rc.ch1 - 0x400) * 10);   //��ҡ�ˡ�����
          moto_3508_set.dstVmmps_W = ((RC_Ctl.rc.ch2 - 0x400) * 10);   //��ҡ�ˡ�����

					switch(RC_Ctl.rc.s1)  //��ť
			    {
							case 1: //��
							{
								
							}break; 
							case 2: //��
							{
						
							}break; 
							case 3: //��
							{
								
							}break;  
							default :break;
			  	}
					switch(RC_Ctl.rc.s2) //�Ҳ�ť
			    {
							case 1: //��
							{
								
							}break; 
							case 2: //��
							{
						
							}break; 
							case 3: //��
							{
								
							}break;  
							default :break;
			    }					
							
					
}

/***************************************************************************************
**
	*	@brief	MouseKeyControlProcess()
	*	@param
	*	@supplement	�Լ�������ݽ��д���
	*	@retval	
****************************************************************************************/
void MouseKeyControlProcess()
{
	
	
	    if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_SHIFT )
			{
					XY_speed_max = 6000;  //(NORMAL_SPEED_MAX)*3.5;
					XY_speed_min = -6000; //(NORMAL_SPEED_MIN)*3.5;
			}else 
			{
					XY_speed_max = 4500;  //(NORMAL_SPEED_MAX)*3.5;
					XY_speed_min = -4500; //(NORMAL_SPEED_MIN)*3.5;
			}
			
		  if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_CTRL )
		  {
					XY_speed_max = 2000;  //(NORMAL_SPEED_MAX)*3.5;
					XY_speed_min = -2000; //(NORMAL_SPEED_MIN)*3.5;
		  }
 
 
			if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_W)                      
				 moto_3508_set.dstVmmps_Y += ACC_SPEED;//����W��
			else if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_S)                 
				 moto_3508_set.dstVmmps_Y -= ACC_SPEED;//����S��
			else
			{  
				if(moto_3508_set.dstVmmps_Y > -DEC_SPEED  &&  moto_3508_set.dstVmmps_Y < DEC_SPEED) 	
					   moto_3508_set.dstVmmps_Y = 0;
				if(moto_3508_set.dstVmmps_Y > 0) 	                 
					   moto_3508_set.dstVmmps_Y -= DEC_SPEED;
				if(moto_3508_set.dstVmmps_Y < 0) 		                
					   moto_3508_set.dstVmmps_Y += DEC_SPEED;
			}


			if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_D)                       
				 moto_3508_set.dstVmmps_X -= ACC_SPEED; //����D��
			else if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_A)    		         
				 moto_3508_set.dstVmmps_X += ACC_SPEED;//����A��
			else
				{
					if(moto_3508_set.dstVmmps_X > -DEC_SPEED  &&  moto_3508_set.dstVmmps_X < DEC_SPEED) 	
						 moto_3508_set.dstVmmps_X = 0;		
					if(moto_3508_set.dstVmmps_X > 0) 	                  
						 moto_3508_set.dstVmmps_X -= DEC_SPEED;
					if(moto_3508_set.dstVmmps_X < 0) 		                
						 moto_3508_set.dstVmmps_X += DEC_SPEED;
			  }

					
					//������ת
					if(RC_Ctl.key.v & 0x80)
					{
              moto_3508_set.dstVmmps_W -= ACC_SPEED;
             if(moto_3508_set.dstVmmps_W < W_speed_min)   moto_3508_set.dstVmmps_W = W_speed_min;
					}else if(RC_Ctl.key.v & 0x40)
          {
             moto_3508_set.dstVmmps_W += ACC_SPEED;
             if(moto_3508_set.dstVmmps_W > W_speed_max)   moto_3508_set.dstVmmps_W = W_speed_max;
          }else
          {
            	 moto_3508_set.dstVmmps_W = 0;
          }
 
          if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_F)//Ť��
          {
             Chassis.mode = 3;
          }else if(RC_Ctl.key.v & KEY_PRESSED_OFFSET_Z  &&  RC_Ctl.key.v & KEY_PRESSED_OFFSET_CTRL)
          {
             Chassis.mode = 1;
          }
								
}



/* �������岿�� -------------------------------------------------------------*/
/***************************************************************************************
**
	*	@brief	Data_Pro_task(void const * argument)
	*	@param
	*	@supplement	ң�����ݽ��ռ���������
	*	@retval	
****************************************************************************************/
void Remote_Data_Task(void const * argument)
{
	uint32_t NotifyValue;
	
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
			
	  NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    if(NotifyValue==1)
		{	
			NotifyValue=0;
			
			HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_14); //GRE_main
			
			RefreshTaskOutLineTime(RemoteDataTask_ON);
			Remote_Ctrl();

			RemoteControlProcess();
			

         press_counter++;
		}
		
			osDelayUntil(&xLastWakeTime, REMOTE_PERIOD);
	}
}





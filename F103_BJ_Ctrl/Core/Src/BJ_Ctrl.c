#include "BJ_Ctrl.h"

extern TIM_HandleTypeDef htim2;

BJ_Ctrl BJ_step={0,0,0,0};

void BJ_do_step(int step,uint8_t BJ_motor)
{
    
    switch(BJ_motor)
    {
        case 1:
            if(step>0)
                BJ_Dir_1_GO;
            else
                BJ_Dir_1_BACK;
            BJ_step.step[0]=(step>0?step:-step);
            TIM2->CCR1=600;
            break;
        case 2:
            if(step>0)
                BJ_Dir_2_GO;
            else
                BJ_Dir_2_BACK;
            BJ_step.step[1]=(step>0?step:-step)*4; 
            TIM2->CCR2=500;            
            break;
        case 3:
            if(step>0)
                BJ_Dir_3_GO;
            else
                BJ_Dir_3_BACK;
            BJ_step.step[2]=step>0?step:-step;  
            TIM2->CCR3=500;
            break;
        case 4:
            if(step>0)
                BJ_Dir_4_GO;
            else
                BJ_Dir_4_BACK;
            BJ_step.step[3]=step>0?step:-step;  
            TIM2->CCR4=500;
            break;
    }
    
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim2)
    {
        if(BJ_step.step[0]>0)
            BJ_step.step[0]--;
        else
        {
            TIM2->CCR1=0;
            BJ_step.sign[0]=0;
        }
        
        if(BJ_step.step[1]>0)
            BJ_step.step[1]--;
        else
        {
            TIM2->CCR2=0;
            BJ_step.sign[1]=0;
        }
        
        if(BJ_step.step[2]>0)
            BJ_step.step[2]--;
        else
        {
            TIM2->CCR3=0;
            BJ_step.sign[2]=0;
        }
        
        if(BJ_step.step[3]>0)
            BJ_step.step[3]--;
        else
        {
            TIM2->CCR4=0;
            BJ_step.sign[3]=0;
        }     
    }
}


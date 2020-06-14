
#include "main.h"



void	GPIO_init(void);
void	SysTick_init_1ms(void);


volatile	uint32_t	LocalTime = 0, TimeOld = 0;


/*								notes
*
*	In this empty project - led blinking on pin B12 (1Hz)
*
*	 when rising clock frequency need to set flash latency
*
*/


int main(void)
{
	SysTick_init_1ms();
	GPIO_init();		//led on pin B12	
	
    while(1)
    {

    }
}


void	GPIO_init(void)
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
	LL_GPIO_InitTypeDef	GPIO_init_struct;
	
	GPIO_init_struct.Pin = LL_GPIO_PIN_12;
	GPIO_init_struct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_init_struct.Speed = LL_GPIO_MODE_OUTPUT_50MHz;
	GPIO_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_init_struct.Pull = LL_GPIO_PULL_UP;
	
	LL_GPIO_Init(GPIOB, &GPIO_init_struct);
}

void	SysTick_init_1ms(void)
{
	SystemCoreClockUpdate();
	LL_InitTick(SystemCoreClock, TICKS_1MS);
	LL_SYSTICK_EnableIT();
	//__enable_irq();
}

void	SysTick_Handler(void)
{
	LocalTime++;
	
	if( LocalTime - TimeOld >= BLINK_PERIOD )
	{
		TimeOld = LocalTime;
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_12);
	}
}


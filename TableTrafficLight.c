// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// December 29, 2014

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
// Functions eja:__________________________________________________:<)

void West(void) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x08; //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x04; //eja
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x08; //eja
} //eja

void South(void) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x01; //eja
		//GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x; //eja
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x08; //eja
} //eja

void Walk(void) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x04; //eja
		//GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x; //eja
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x08; //eja
} //eja

//End Functions eja.________________________________________________:<)

// ***** 3. Subroutines Section *****
void SysTick_Init(void) { //eja
	NVIC_ST_CTRL_R = 0; //eja
	NVIC_ST_RELOAD_R = 0x00FFFFFF; //eja
	NVIC_ST_CURRENT_R = 0; //eja
	NVIC_ST_CTRL_R = 0x00000005; //eja
} //eja
unsigned long S; //eja
unsigned long Input; //eja
int main(void){ /*eja*/ volatile unsigned long delay; //eja
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); // activate grader and set system clock to 80 MHz
  SysTick_Init(); //eja
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_R = 0x32; //eja
	delay = SYSCTL_RCGC2_R; //eja
	GPIO_PORTE_AMSEL_R = GPIO_PORTE_AMSEL_R & ~0x07; //eja
	GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R & ~0x00000FFF; //eja
	GPIO_PORTE_DIR_R = GPIO_PORTE_DIR_R & ~0x07; //eja
	GPIO_PORTE_AFSEL_R = GPIO_PORTE_AFSEL_R & ~0x07; //eja
	GPIO_PORTE_DEN_R = GPIO_PORTE_DEN_R | 0x07; //eja
  
	EnableInterrupts();
  while(1){
	  unsigned long ews; //eja
		unsigned long nss; //eja
		unsigned long ws; //eja
		ews = GPIO_PORTB_DATA_R&0x01; //eja
		nss = GPIO_PORTB_DATA_R&0x02; //eja
		ws = GPIO_PORTB_DATA_R&0x04; //eja
		
		if () { //eja
			West(); //eja
		} //eja
		if () { //eja
			South(); //eja
		} //eja
		if () { //eja
			Walk(); //eja
		} //eja
  }
}

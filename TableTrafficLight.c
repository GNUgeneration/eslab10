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

void delay(unsigned long t) { //eja
	unsigned long i; //eja
	while (t > 0) { //eja
		i = 1333333; //eja
		while (i > 0) { //eja
			i = i - 1; //eja
		} // eja
		t = t - 1; //eja
	} //eja
} //eja

void R0(void) { unsigned long PE0; //eja
	PE0 = GPIO_PORTE_DATA_R&0x01; //eja
	if (PE0 == 1) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x08; //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x04; //eja
	} //eja
} //eja
void R1(void) { unsigned long PE1; //eja
	PE1 = GPIO_PORTE_DATA_R&0x02; //eja
	if (PE1 == 1) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x01; //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x20; //eja
	} //eja
} //eja
void R2(void) { unsigned long PE2; //eja
	PE2 = GPIO_PORTE_DATA_R&0x04; //eja
	if (PE2 == 1) { //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x04; //eja
		GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | 0x20; //eja
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x08; //eja
	} //eja
} //eja
void R3(void) { unsigned long PE0, PE1; //eja
	PE0 = GPIO_PORTE_DATA_R&0x01; //eja
	PE1 = GPIO_PORTE_DATA_R&0x02; //eja
	if ((PE0 == 1) || (PE1 == 1)) { //eja
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x02; //eja
	} //eja
} //eja

// ---------------------------------------------------------------------
// ***** 3. Subroutines Section *****
void SysTick_Init(void) { //eja
	NVIC_ST_CTRL_R = 0; //eja
	NVIC_ST_CTRL_R = 0x00000005; //eja
} //eja

void SysTick_Wait(unsigned long delay) { //eja
	NVIC_ST_RELOAD_R = delay - 1; //eja
	NVIC_ST_CURRENT_R = 0; //eja
} //eja

void SysTick_Wait10ms(unsigned long delay) { //eja
	unsigned long i; //eja
	for (i = 0; i < delay; ++i) { //eja
		SysTick_Wait(800000); //eja
	} //eja
} //eja
//____________________________________________________________

#define SENSOR (*((volatile unsigned long *)0x4002400C)) //eja
#define LIGHT  (*((volatile unsigned long *)0x400050FC)) //eja
// Linked data structure
struct State { //eja
	unsigned long Out; //eja
	unsigned long Time; //eja
	unsigned long Next[16];}; //eja
typedef const struct State STyp; //eja
#define goN   0 //eja
#define waitN 1 //eja
#define goE   2 //eja
#define waitE 3 //eja
STyp FSM[4] = { //eja
	{0x21,3000,{goN,waitN,goN,waitN}}, //eja
	{0x22, 500,{goE,goE,goE,goE}}, //eja
	{0x0C,3000,{goE,goE,waitE,waitE}}, //eja 
	{0x14, 500,{goN,goN,goN,goN}}}; //eja
unsigned long S; //eja
unsigned long Input; //eja
int main(void){ /*eja*/ volatile unsigned long delay; //eja
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); // activate grader and set system clock to 80 MHz
	SysTick_Init(); //eja
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_R | 0x32; //eja
	delay = SYSCTL_RCGC2_R; //eja
	GPIO_PORTE_AMSEL_R = GPIO_PORTE_AMSEL_R & ~0x07; //eja
	GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R & ~0x00000FFF; //eja
	GPIO_PORTE_DIR_R = GPIO_PORTE_DIR_R & ~0x07; //eja
	GPIO_PORTE_AFSEL_R = GPIO_PORTE_AFSEL_R & ~0x07; //eja
	GPIO_PORTE_DEN_R = GPIO_PORTE_DEN_R | 0x07; //eja
//----------------------------------------------------------
	GPIO_PORTB_DIR_R = GPIO_PORTB_DIR_R | 0x3F; //eja
	GPIO_PORTB_DEN_R = GPIO_PORTB_DEN_R | 0x3F; //eja
	GPIO_PORTB_AFSEL_R = GPIO_PORTB_AFSEL_R & ~0x3F; //eja
  S = goN; //eja
  EnableInterrupts();
  while(1){
    LIGHT = FSM[S].Out; //eja
		SysTick_Wait10ms(FSM[S].Time); //eja
		Input = SENSOR; //eja
		S = FSM[S].Next[Input]; //eja
		
		R0(); //eja
		R1(); //eja
		R2(); //eja
		R3(); //eja
  }
}

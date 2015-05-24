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

// ***** 3. Subroutines Section *****
void PLL_Init(void) {
	// 0) Use RCC2
	SYSCTL_RCC2_R = SYSCTL_RCC2_R | 0x80000000; //eja
//____________________________________________________________

#define SENSOR (*((volatile unsigned long *)0x4002400C)) //eja
#define LIGHT  (*((volatile unsigned long *)0x400050FC)) //eja
// Linked data structure
struct State { //eja
	unsigned long Out; //eja
	unsigned long Time; //eja
	unsigned long Next[4];}; //eja
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
  //TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); // activate grader and set system clock to 80 MHz
	
  
  EnableInterrupts();
  while(1){
     
  }
}

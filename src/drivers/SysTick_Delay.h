// SysTick_Delay.h
// Class Number : 447
// Project Number: 4
// Group Number: 2
// Team Members: Ana Arante, Emily Hsu, Suphia Sidiqi

#include <stdint.h>

#define TEN_MS									160000	// reload value for generating 5ms time interval for 16MHz system clock
#define FIVE_MS									80000		// reload value for 5ms and 16MHz system clock

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void);

// Time delay using busy wait. 
// The delay parameter is in units of the core clock. (units of 62.5 nsec for 16 MHz clock)
void SysTick_Wait(uint32_t delay);

// Time delay using busy wait.
// This assumes 16 MHz system clock.
// This function generate a time delay that is multiple of 10ms
// Parameter:
// n_ms: specify how many 10ms will be generated.
// maximum delay: 2^32*10ms
void SysTick_Wait10ms(uint32_t n_10ms);
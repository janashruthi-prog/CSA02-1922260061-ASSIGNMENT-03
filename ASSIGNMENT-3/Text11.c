#include <stdio.h> 
#include <stdint.h> 
#include <inttypes.h> 
#define FIXED_CHARGE 5000LL 
#define SLAB1_LIMIT 100U 
#define SLAB2_LIMIT 200U 
#define SLAB2_RATE 225LL 
#define SLAB3_RATE 450LL 
int main(void) 
{ 
 uint16_t previous, current;
 uint32_t units;
 int64_t energy_charge = 0;
 int64_t total_bill;
 printf("GRAM JYOTHI BILLING SYSTEM\n");
 printf("Enter previous reading: ");
 if (scanf("%" SCNu16, &previous) != 1) { 
 printf("Invalid input.\n");
 return 1;
 } 
 printf("Enter current reading: ");
Python Programming Assignment — Student Template 
 if (scanf("%" SCNu16, &current) != 1) { 
 printf("Invalid input.\n");
 return 1;
 } 
 if (current < previous) { 
 printf("Invalid reading: rollover is not handled here.\n");
 return 1;
 } 
 units = (uint32_t)current - (uint32_t)previous;
 if (units > SLAB1_LIMIT) { 
 uint32_t slab2_units = 
 (units < SLAB2_LIMIT) ? units - SLAB1_LIMIT 
 : SLAB2_LIMIT - SLAB1_LIMIT;
 energy_charge += (int64_t)slab2_units * SLAB2_RATE;
 } 
 if (units > SLAB2_LIMIT) { 
 energy_charge += 
 (int64_t)(units - SLAB2_LIMIT) * SLAB3_RATE;
 } 
 total_bill = FIXED_CHARGE + energy_charge;
 printf("\n--- BILL DETAILS ---\n");
 printf("Units consumed: %" PRIu32 "\n", units);
 printf("Energy charge: %" PRId64 " paise\n", energy_charge);
 printf("Fixed charge: %" PRId64 " paise\n", FIXED_CHARGE);
 printf("Total bill: Rs. %" PRId64 ".%02" PRId64 "\n", 
 total_bill / 100, total_bill % 100);
 printf("\n--- DESIGN JUSTIFICATION ---\n");
 printf("Meter reading type: uint16_t\n");
 printf("Consumption type: uint32_t\n");
 printf("Money type: int64_t in paise\n");
 printf("Tariff values: named preprocessor constants\n");
 return 0;
}

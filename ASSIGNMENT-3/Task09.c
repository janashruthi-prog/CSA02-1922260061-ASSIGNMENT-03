#include <stdio.h> 
#include <stdint.h> 
#include <inttypes.h> 
Python Programming Assignment — Student Template 
#define SLAB1_UNITS 100U 
#define SLAB2_UNITS 200U 
#define RATE1_PAISE 0LL 
#define RATE2_PAISE 225LL 
#define RATE3_PAISE 450LL 
#define FIXED_CHARGE_PAISE 5000LL 
#define ROLLOVER_PREVIOUS_MIN 60000U 
#define ROLLOVER_CURRENT_MAX 1000U 
typedef uint16_t meter_t;
static uint32_t consumption(meter_t previous, meter_t current) 
{ 
/* Unsigned 16-bit arithmetic gives 256 for 65400 -> 120. */ 
return (uint16_t)(current - previous);
} 
static int valid_readings(unsigned int previous, unsigned int current) 
{ 
if (previous > UINT16_MAX || current > UINT16_MAX) return 0;
if (current >= previous) return 1;
return previous >= ROLLOVER_PREVIOUS_MIN && 
current <= ROLLOVER_CURRENT_MAX;
} 
static long long compute_bill(uint32_t units) 
{ 
uint32_t slab2 = 0;
uint32_t slab3 = 0;
long long paise = FIXED_CHARGE_PAISE;
if (units > SLAB1_UNITS) 
slab2 = units < SLAB2_UNITS ? units - SLAB1_UNITS : SLAB2_UNITS - SLAB1_UNITS;
if (units > SLAB2_UNITS) 
slab3 = units - SLAB2_UNITS;
paise += (long long)slab2 * RATE2_PAISE;
paise += (long long)slab3 * RATE3_PAISE;
return paise;
} 
static void print_money(long long paise) 
{ 
printf("Rs %lld.%02lld", paise / 100, paise % 100);
} 
int main(void) 
{ 
unsigned int household_id, previous_input, current_input;
meter_t previous, current;
uint32_t units;
long long bill;
printf("Household ID: ");
if (scanf("%u", &household_id) != 1) { 
fprintf(stderr, "Invalid household ID.\n");
return 1;
} 
printf("Previous meter reading (0-65535): ");
if (scanf("%u", &previous_input) != 1) { 
fprintf(stderr, "Invalid previous reading.\n");
return 1;
} 
printf("Current meter reading (0-65535): ");
if (scanf("%u", &current_input) != 1) { 
fprintf(stderr, "Invalid current reading.\n");
return 1;
} 
if (!valid_readings(previous_input, current_input)) { 
fprintf(stderr, "Invalid readings or unsupported rollover.\n");
return 1;
} 
previous = (meter_t)previous_input;
current = (meter_t)current_input;
units = consumption(previous, current);
bill = compute_bill(units);
printf("\nHousehold ID: %u\n", household_id);
printf("Units consumed: %" PRIu32 "\n", units);
printf("Fixed charge: Rs 50.00\n");
printf("Total bill: ");
print_money(bill);
printf("\n");
return 0;
}

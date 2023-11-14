#define G_ON LED_G_PORT |= (1 << LED_G_PORT_NUM)
#define B_ON LED_B_PORT |= (1 << LED_B_PORT_NUM)
#define G_OFF LED_G_PORT &= ~ (1 << LED_G_PORT_NUM)
#define B_OFF LED_B_PORT &= ~ (1 << LED_B_PORT_NUM)

void led_loop_top();

void led_begin_wait_for_start_bit();
void led_end_wait_for_start_bit();
void led_begin_wait_for_dollar();
void led_end_wait_for_dollar();

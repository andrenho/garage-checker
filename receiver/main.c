#include <avr/pgmspace.h>
#include <util/delay.h>

#define RX_PIN  PB3
#define LED_PIN PB4

uint8_t receive_byte()
{
	// Wait for start bit
    while (PINB & (1 << RX_PIN)); // Wait for LOW
    _delay_us(1000);

    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++) {
        if (PINB & (1 << RX_PIN))
            data |= (1 << i);
        else
            data &= ~(1 << i);
        _delay_us(1000);
    }

    // Stop bit (optional check)
    _delay_us(1000);

    return data;
}

int main(void)
{
    DDRB &= ~(1 << RX_PIN); // Input
    PORTB |= (1 << RX_PIN); // Pull-up

    DDRB |= (1 << LED_PIN);

    for (;;) {
        uint8_t c = receive_byte();
        if (c == 'H')
            PORTB |= (1 << LED_PIN);
        if (c == 'L')
            PORTB &= ~(1 << LED_PIN);
    }
    return 0;
}

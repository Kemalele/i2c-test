#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

#define I2C_PORT I2C1
#define I2C_RCC RCC_I2C1
#define I2C_SCL_GPIO GPIOB
#define I2C_SCL_PIN GPIO6
#define I2C_SDA_GPIO GPIOB
#define I2C_SDA_PIN GPIO7
#define I2C_SPEED 100000 // I2C speed in Hz

void i2c_setup() {
    // Enable GPIOB clock
    rcc_periph_clock_enable(RCC_GPIOB);

    // Enable I2C1 clock
    rcc_periph_clock_enable(I2C_RCC);

    // Set up I2C pins (SCL and SDA)
    gpio_mode_setup(I2C_SCL_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, I2C_SCL_PIN);
    gpio_set_output_options(I2C_SCL_GPIO, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, I2C_SCL_PIN);
    gpio_set_af(I2C_SCL_GPIO, GPIO_AF4, I2C_SCL_PIN);

    gpio_mode_setup(I2C_SDA_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, I2C_SDA_PIN);
    gpio_set_output_options(I2C_SDA_GPIO, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, I2C_SDA_PIN);
    gpio_set_af(I2C_SDA_GPIO, GPIO_AF4, I2C_SDA_PIN);

    // Initialize I2C
    i2c_reset(I2C_PORT);
    i2c_peripheral_disable(I2C_PORT);
    i2c_set_speed(I2C_PORT, i2c_speed_fm_400k, rcc_apb1_frequency / 1000000);

    // Enable ACK (optional, depends on your use case)
    // i2c_enable_ack(I2C_PORT);

    // Enable I2C1
    i2c_peripheral_enable(I2C_PORT);
}

int main(void) {
	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

    i2c_setup();

    // Now the I2C1 peripheral is configured properly and ready for communication

    while (1) {
        i2c_send_start(I2C1);
        i2c_send_7bit_address(I2C1,0x20,0);
        i2c_reset(I2C_PORT);
        // Your code here
    }

    return 0;
}
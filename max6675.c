#include "max6675.h"

#include <furi.h>
#include <furi_hal_spi.h>
#include <furi_hal_gpio.h>
#include <furi_hal_resources.h>

#define CS_PIN &gpio_ext_pb2 // Пин CS

static uint16_t get_raw() {
    furi_hal_gpio_init(&gpio_ext_pb2, GpioModeOutputPushPull, GpioPullNo, GpioSpeedVeryHigh);

    uint8_t rx[2] = {0, 0};

    furi_hal_spi_acquire(&furi_hal_spi_bus_handle_external);

    furi_hal_gpio_write(CS_PIN, false);
    furi_delay_us(1);

    furi_hal_spi_bus_rx(&furi_hal_spi_bus_handle_external, rx, 2, 0xFF);

    furi_hal_gpio_write(CS_PIN, true);

    furi_hal_spi_release(&furi_hal_spi_bus_handle_external);

    return ((uint16_t)rx[0] << 8) | rx[1];
}

static bool check_d2(uint16_t raw) {
    return raw & 0x4;
}

float get_temperature() {
    uint16_t raw = get_raw();

    if(check_d2(raw)) {
        return -1.0f;
    }

    return ((int16_t)(raw >> 3)) * 0.25f;
}

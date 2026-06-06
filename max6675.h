#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Чтение температуры в градусах Цельсия
 *
 * @return float температура в °C
 *         -1.0f если ошибка датчика (термопара не подключена или обрыв CS)
 */
float get_temperature(void);

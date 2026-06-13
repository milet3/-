#include "mbedtls/build_info.h"
#include "mbedtls/entropy.h"
#include "stm32f4xx_hal.h"

#if defined(HAL_RNG_MODULE_ENABLED)
extern RNG_HandleTypeDef hrng;

int mbedtls_hardware_poll(void *data, unsigned char *output,
                          size_t len, size_t *olen)
{
    uint32_t random;
    size_t remaining = len;

    (void)data;

    while (remaining > 0) {
        if (HAL_RNG_GenerateRandomNumber(&hrng, &random) != HAL_OK) {
            return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
        }
        size_t copy = (remaining < sizeof(random)) ? remaining : sizeof(random);
        memcpy(output + (len - remaining), &random, copy);
        remaining -= copy;
    }

    *olen = len;
    return 0;
}
#else
int mbedtls_hardware_poll(void *data, unsigned char *output,
                          size_t len, size_t *olen)
{
    (void)data;
    (void)output;
    (void)len;
    (void)olen;
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
}
#endif
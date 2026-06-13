#include "mbedtls/build_info.h"
#include "mbedtls/platform_time.h"
#include "mbedtls/timing.h"
#include "stm32f4xx_hal.h"
#include <time.h>

#if defined(MBEDTLS_HAVE_TIME)
extern RTC_HandleTypeDef hrtc;
#endif

mbedtls_ms_time_t mbedtls_ms_time(void)
{
    return (mbedtls_ms_time_t)HAL_GetTick();
}

#if defined(MBEDTLS_HAVE_TIME)
time_t mbedtls_time(time_t *timer)
{
    RTC_TimeTypeDef rtc_time;
    RTC_DateTypeDef rtc_date;

    HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

    struct tm t = {0};
    t.tm_sec = rtc_time.Seconds;
    t.tm_min = rtc_time.Minutes;
    t.tm_hour = rtc_time.Hours;
    t.tm_mday = rtc_date.Date;
    t.tm_mon = rtc_date.Month - 1;
    t.tm_year = rtc_date.Year + 100;

    time_t now = mktime(&t);
    if (timer != NULL) {
        *timer = now;
    }
    return now;
}
#endif /* MBEDTLS_HAVE_TIME */

unsigned long mbedtls_timing_get_timer(struct mbedtls_timing_hr_time *val, int reset)
{
    (void)val;
    (void)reset;
    return HAL_GetTick();
}

void mbedtls_timing_set_delay(void *data, uint32_t int_ms, uint32_t fin_ms)
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *)data;
    ctx->MBEDTLS_PRIVATE(int_ms) = int_ms;
    ctx->MBEDTLS_PRIVATE(fin_ms) = fin_ms;
}

int mbedtls_timing_get_delay(void *data)
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *)data;
    unsigned long elapsed = HAL_GetTick();

    if (ctx->MBEDTLS_PRIVATE(fin_ms) == 0) {
        return -1;
    }

    if (elapsed >= ctx->MBEDTLS_PRIVATE(fin_ms)) {
        return 2;
    }
    if (elapsed >= ctx->MBEDTLS_PRIVATE(int_ms)) {
        return 1;
    }
    return 0;
}
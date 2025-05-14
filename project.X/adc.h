/*
 * File:   main.h
 * Author: weyth
 *
 * Created on 4 avril 2025, 14:53
 */

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#include <stdbool.h>
#include <stdint.h>

void ADC_Init(void);
void ADC_read(uint16_t *adcValue);
void ADC1_read(uint16_t *adcValue);
void ADC2_read(uint16_t *adcValue);
void ADC3_read(uint16_t *adcValue);
void ADC4_read(uint16_t *adcValue);
void ADC_convert(uint16_t *adcValue, float *temperature);

#endif /* ADC_H */

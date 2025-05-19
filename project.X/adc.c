#include "adc.h"
#include <xc.h>
#define _XTAL_FREQ 20e6
void ADC_Init(void) {
    /**
     * @brief Configures the ADC module.
     *
     * ADCON1 Register:
     * - Bit 7: ADFM (A/D Result Format Select bit)
     *   - 1 = Right justified
     * - Bits 6-4: Unimplemented (Read as '0')
     * - Bits 3-0: PCFG<3:0> (A/D Port Configuration Control bits)
     *   - 0x0 = All pins are configured as analog inputs (AN0-AN7).

     * ADCON0 Register:
     * - Bit 7: ADCS1 (A/D Conversion Clock Select bit 1)
     *   - 0 = FOSC/8
     * - Bit 6: ADCS0 (A/D Conversion Clock Select bit 0)
     *   - 1 = FOSC/8
     * - Bit 5: CHS2 (A/D Channel Select bit 2)
     *   - 0 = Selects AN3 as the input channel
     * - Bit 4: CHS1 (A/D Channel Select bit 1)
     *   - 1 = Selects AN3 as the input channel
     * - Bit 3: CHS0 (A/D Channel Select bit 0)
     *   - 1 = Selects AN3 as the input channel
     * - Bit 2: GO/DONE (A/D Conversion Status bit)
     *   - 0 = A/D conversion is not in progress
     * - Bit 1: Unimplemented (Read as '0')
     * - Bit 0: ADON (A/D On bit)
     *   - 1 = A/D converter module is enabled
     */
    // Configure the ADC
    ADCON1 = 0x80; // Keep all pins as analog inputs
    ADCON0 = 0x99; // Enable the ADC module (ADON = 1), set FOSC/32 as the clock
                   // source, and select AN3 as the input channel
    PIE1bits.ADIE = 1; // Enable ADC interrupt
}

void ADC_ISR(void) {
    // ADC interrupt service routine
    if (PIR1bits.ADIF) {
        // ADC conversion complete
        PIR1bits.ADIF = 0; // Clear ADC interrupt flag
    }
}

void ADC_read(uint16_t *adcValue) {
    // Start the ADC conversion
    __delay_us(20); // Small delay to ensure the conversion is complete
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to complete
    while (ADCON0bits.GO_nDONE)
        ;
    // Read the ADC value
    if (ADCON0bits.GO_nDONE == 0) {
        // Conversion is done, read the result
        *adcValue = ((uint16_t)ADRESH << 8) | ADRESL;
    }
}

void ADC1_read(uint16_t *adcValue) {
    // Select the appropriate analog channel (AN1 in this case)
    ADCON0bits.CHS = 0b000;
    __delay_us(20); // Small delay to stabilize the channel
    // Start the ADC conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to complete
    while (ADCON0bits.GO_nDONE)
        ;

    // Read the ADC value
    *adcValue = ((uint16_t)ADRESH << 8) | ADRESL;
}

void ADC2_read(uint16_t *adcValue) {
    // Start the ADC conversion
    ADCON0bits.CHS = 0b001; // Select AN2
    __delay_us(20);         // Small delay to stabilize the channel
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to complete
    while (ADCON0bits.GO_nDONE)
        ;

    // Read the ADC value
    *adcValue = ((uint16_t)ADRESH << 8) | ADRESL;
}

void ADC3_read(uint16_t *adcValue) {
    ADCON0bits.CHS = 0b010; // Select AN3
    __delay_us(20);         // Small delay to stabilize the channel
    // Start the ADC conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to complete
    while (ADCON0bits.GO_nDONE)
        ;

    // Read the ADC value
    *adcValue = ((uint16_t)ADRESH << 8) | ADRESL;
}

void ADC4_read(uint16_t *adcValue) {
    // Select the appropriate analog channel (AN4 in this case)
    ADCON0bits.CHS = 0b011;
    __delay_us(20); // Small delay to stabilize the channel
    // Start the ADC conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to complete
    while (ADCON0bits.GO_nDONE)
        ;

    // Read the ADC value
    *adcValue = ((uint16_t)ADRESH << 8) | ADRESL;
}

void ADC_convert(uint16_t *adcValue, float *temperature) {
    // convert the ADC value to a temperature
    *temperature = (*adcValue / 3.1);
}
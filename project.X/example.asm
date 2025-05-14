; Pour programmer en assembleur, penser à changer le compilateur:
; Propriétés du projet, mettre "compiler toolchain" sur "pic-as"

; Configuration du PIC16F877A
    PROCESSOR 16F877A      ; Spécifie le modèle de PIC
    #include <xc.inc>

; Configuration des bits spéciaux
CONFIG  FOSC = HS         ; Oscillator Selection bits (HS oscillator)
CONFIG  WDTE = OFF        ; Watchdog Timer Enable bit (WDT disabled)
CONFIG  PWRTE = OFF       ; Power-up Timer Enable bit (PWRT disabled)
CONFIG  BOREN = OFF       ; Brown-out Reset Enable bit (BOR enabled)
CONFIG  LVP = OFF         ; Low-Voltage Programming Enable bit
CONFIG  CPD = OFF         ; Data EEPROM Memory Code Protection bit 
CONFIG  WRT = OFF         ; Flash Program Memory Write Enable bits
CONFIG  CP = OFF          ; Flash Program Memory Code Protection bit 

; Définitions des variables
PSECT udata_bank0
COUNT1:     DS 1          ; Reserve 1 byte for COUNT1
COUNT2:     DS 1          ; Reserve 1 byte for COUNT2
COUNT3:     DS 1          ; Reserve 1 byte for COUNT3
var1:       DS 1          ; 1 octet pour var1

; Vecteur d'interruption (adresse 0x0004)
PSECT intVect, class=CODE, delta=2
    ORG 0x0004           ; Interrupt vector starts at 0x0004
    retfie

; Vecteur de reset (adresse 0x0000)
PSECT resetVect, class=CODE, delta=2
    ORG 0x0000           ; Reset vector starts at 0x0000
    goto START

; Section de code principal
PSECT code, delta=2
START:
    ; Configuration initiale
    BANKSEL TRISB
    CLRF    TRISB        ; Configure le port B comme sortie
    BANKSEL PORTB
    CLRF    PORTB        ; Initialise le port B à 0
    
LOOP:
    ; CALL COMPLEMENT_PB
    BANKSEL PORTD
    BTFSS   PORTD, 0      ; Check if button on RD0 is pressed
    GOTO    SKIP_TOGGLE   ; Skip toggle if not pressed

    BANKSEL var1
    MOVF    var1, W       ; Move var1 to W
    XORLW   0x01          ; Toggle var1 (0 -> 1, 1 -> 0)
    MOVWF   var1          ; Store the result back to var1

    SKIP_TOGGLE:
        BANKSEL var1
        BTFSC   var1, 0       ; Check if var1 is 0
        GOTO    REVERSE       ; If pressed, go to REVERSE
        CALL    CHENILLARD    ; Otherwise, call CHENILLARD
        GOTO    CONTINUE

    REVERSE:
        CALL    CHENILLARD_REVERSE ; Call CHENILLARD_REVERSE

    CONTINUE:
        CALL    DELAY_1SEC
    
    ; Retourne au début de la boucle
    GOTO    LOOP

; Sous-programme: complément du Port B
COMPLEMENT_PB:
    ; Complémente le Port B
    COMF    PORTB, F     ; Note: added F for result to PORTB
    RETURN

; Sous-programme: chenillard
CHENILLARD:
    RLF     PORTB, F     ; Rotate left (added F for result to PORTB)
    RETURN

CHENILLARD_REVERSE:
    RRF     PORTB, F     ; Rotate right (added F for result to PORTB)
    RETURN

; Sous-programme: délai d'environ 1 seconde
DELAY_1SEC:    
    MOVLW   0x0F         
    MOVWF   COUNT1       

    DELAY_LOOP1:
        MOVLW   0xFF         
        MOVWF   COUNT2       

    DELAY_LOOP2:
        MOVLW   0xFF         
        MOVWF   COUNT3       

    DELAY_LOOP3:
        NOP                  
        DECFSZ  COUNT3, F    
        GOTO    DELAY_LOOP3  

        DECFSZ  COUNT2, F    
        GOTO    DELAY_LOOP2  

        DECFSZ  COUNT1, F    
        GOTO    DELAY_LOOP1  

        RETURN   
                



#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

// =============================
#define SENS_SAR_READ_CTRL_REG     (*(volatile uint32_t*)0x3FF48804)
#define SENS_SAR_ATTEN1_REG        (*(volatile uint32_t*)0x3FF48820)
#define SENS_SAR_START_FORCE_REG   (*(volatile uint32_t*)0x3FF4880C)
#define SENS_SAR_MEAS_START1_REG   (*(volatile uint32_t*)0x3FF4881C)

// Pines
#define BTN_INC 5
#define BTN_DEC 4
#define LED_R   27
#define LED_G   26
#define LED_B   25

// ADC

void adc1_configuracion()
{
    // ATTEN bits 12 y 13
    SENS_SAR_ATTEN1_REG |= (1 << 12) | (1 << 13);

    // READ_CTRL bits 27, 16 y 17
    SENS_SAR_READ_CTRL_REG |= (1 << 27);
    SENS_SAR_READ_CTRL_REG |= (1 << 16) | (1 << 17);

    // START_FORCE bits 0 y 1
    SENS_SAR_START_FORCE_REG |= (1 << 0) | (1 << 1);
}

//  ONSHOT

int32_t adc1_leer()
{

    SENS_SAR_MEAS_START1_REG |= (1 << 31) | (1 << 18) | (1 << 17);

    SENS_SAR_MEAS_START1_REG |= (1 << 25);

    uint32_t timeout = 1000000;


    while(((SENS_SAR_MEAS_START1_REG >> 16) & 1) == 0)
    {
        if(--timeout == 0) return -1;
    }

    // Leer bits 0–15
    int32_t valor = (SENS_SAR_MEAS_START1_REG & 0xFFFF);
    return valor;
}

void leds_off(){
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void led_por_tiempo(int t){
    leds_off();

    if(t >= 2 && t <= 10){
        digitalWrite(LED_R, HIGH);
    } 
    else if(t >= 12 && t <= 16){
        digitalWrite(LED_B, HIGH);
    }
    else if(t == 18 || t == 20){
        digitalWrite(LED_G, HIGH);
    }
}


bool boton_presionado(int pin){
    if(digitalRead(pin) == LOW){
        delay(40);
        if(digitalRead(pin) == LOW) return true;
    }
    return false;
}



void setup() {
    Serial.begin(115200);

    pinMode(BTN_INC, INPUT_PULLUP);
    pinMode(BTN_DEC, INPUT_PULLUP);

    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    leds_off();
    adc1_configuracion();

    Serial.println("P4 Iniciado...");
}


void loop() {

    static int tiempo = 2;   // inicia en 2 segundos

 
    if(boton_presionado(BTN_INC)){
        tiempo += 2;
        if(tiempo > 20) tiempo = 20;
        while(digitalRead(BTN_INC) == LOW);
    }

    
    if(boton_presionado(BTN_DEC)){
        tiempo -= 2;
        if(tiempo < 2) tiempo = 2;
        while(digitalRead(BTN_DEC) == LOW);
    }

    // LED según intervalo
    led_por_tiempo(tiempo);


    int suma = 0;
    for(int i = 0; i < 10; i++){
        int v = adc1_leer();
        if(v >= 0) suma += v;
        delay(10);
    }
    int promedio = suma / 10;

    
    Serial.printf("Promedio ADC = %d\n", promedio);
    Serial.printf("Tiempo de muestreo = %d s\n", tiempo);

    leds_off();

 
    delay(tiempo * 1000);
}


// Sensor ADXL335 - 


//Note: ADC2 pins cannot be used when Wi-Fi is used. So, if you’re using Wi-Fi and you’re having trouble getting the value from an ADC2 GPIO, you may consider using an ADC1 GPIO instead, that should solve your problem. 

#define NUM_ADC_READINGS 5
#define ACCEL_READING_INTERVAL 50

const int xpin = 34; // x-axis of the accelerometer
const int ypin = 36; // y-axis
const int zpin = 39; // z-axis

const byte adc_pins[]={34,36,39};

void accel_config(){
    analogReadResolution(11); // Default of 12 is not very linear. 
    analogSetAttenuation(ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
}

int16_t accel_read() {
    static uint32_t last_t_read=0;
    static int last_reading[3]={-1,-1,-1};
    static uint16_t last_accel_reading=0;
    int accel_readings[3][NUM_ADC_READINGS+1];
    uint16_t accel_sum=0;

    if (millis()-last_t_read < 100) return -1; //last_accel_reading;

    last_t_read=millis();

    //Acumulamos N lecturas del ADC para minimizar ruidos
    for (byte i=0; i<NUM_ADC_READINGS; i++){
        for (byte j=0; j<3; j++){
            accel_readings[j][i]=analogRead(adc_pins[j]);
            //Serial.printf("Leyendo sensor %d, lectura num %d, valor %d\n", j, i, accel_readings[j][i]);
        }
    }

    //Calculamos el promedio las lecturas
    for (byte j=0; j<3; j++){
        accel_readings[j][NUM_ADC_READINGS]=0;
        for (byte i=0; i<NUM_ADC_READINGS; i++){
            accel_readings[j][NUM_ADC_READINGS]+=accel_readings[j][i];
        }
        accel_readings[j][NUM_ADC_READINGS]/=NUM_ADC_READINGS;

        //Serial.printf("%d ", accel_readings[j][NUM_ADC_READINGS]);
    }
    //Serial.println();

    for (byte j=0; j<3; j++){
        //Serial.print(j);
        //Serial.print(" ");
        //Serial.print(accel_readings[j][NUM_ADC_READINGS]);
        //Serial.print(" ");
        //Serial.print(last_reading[j]);
        //Serial.print(" ");
        //Serial.print(accel_readings[j][NUM_ADC_READINGS]-last_reading[j]);
        //Serial.println();
        //Serial.print(accel_readings[j][NUM_ADC_READINGS]-last_reading[j]);
        //Serial.print(" ");
        accel_sum += abs(accel_readings[j][NUM_ADC_READINGS]-last_reading[j]);
        last_reading[j]=accel_readings[j][NUM_ADC_READINGS]; //Esto lo último siempre
    }
    //Serial.print(" ");
    //Serial.println(accel_sum);

    last_accel_reading = accel_sum;
    return accel_sum;
}

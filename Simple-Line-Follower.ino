#define MOTOR_LEFT_A_PIN_NO  16
#define MOTOR_LEFT_B_PIN_NO  17
#define MOTOR_STANDBY_PIN_NO 18
#define MOTOR_RIGHT_A_PIN_NO 19
#define MOTOR_RIGHT_B_PIN_NO 20

#define IR_LEFT_PIN_NO  13
#define IR_RIGHT_PIN_NO 12

#define IR_ON_PIN_NO 10

#define BATTERY_VOLTAGE_CHECK_PIN_NO A2
#define ANALOG_REFERENCE_VOLTAGE     3.3
#define ANALOG_READ_RESOLUTION       12
#define R7_OHM_POSITIVE              10000.0
#define R8_OHM_GROUND                5100.0
#define BATTERY_LOW_VOLTAGE_CUTOFF   7.0

#define ANALOG_WRITE_RESOLUTION 16
#define MOTOR_DRIVER_ENABLE     1
#define MOTOR_DRIVER_STANDBY    0
int gati =  24;
int gati_1 = 24;
int gati_2 = 26;
const float voltageDividerRatio = (R7_OHM_POSITIVE + R8_OHM_GROUND) / R8_OHM_GROUND;
const float adcCountToVolt = ANALOG_REFERENCE_VOLTAGE / (pow(2, ANALOG_READ_RESOLUTION) - 1) * voltageDividerRatio; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    
    pinMode(MOTOR_LEFT_A_PIN_NO, OUTPUT);
    pinMode(MOTOR_LEFT_B_PIN_NO, OUTPUT);

    pinMode(MOTOR_STANDBY_PIN_NO, OUTPUT);

    pinMode(MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    pinMode(MOTOR_RIGHT_B_PIN_NO, OUTPUT);
    
    pinMode(IR_LEFT_PIN_NO, INPUT);
    pinMode(IR_RIGHT_PIN_NO, INPUT);
    
    pinMode(IR_ON_PIN_NO, INPUT);
    
    pinMode(BATTERY_VOLTAGE_CHECK_PIN_NO, INPUT); 

    analogReadResolution(ANALOG_READ_RESOLUTION);

    // analogWruteResolution(ANALOG_WRITE_RESOLUTION);
    analogWriteResolution(8);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
    batteryVoltageCheck();
    if(digitalRead(IR_LEFT_PIN_NO) == 1 && digitalRead(IR_RIGHT_PIN_NO) == 1){
      motionForward_1(gati_1) ;
      motionForward_2(gati_2);
    }
    else if(digitalRead(IR_LEFT_PIN_NO)==1 && digitalRead(IR_RIGHT_PIN_NO) == 0){
      turnRight(gati);
    }
    else if(digitalRead(IR_LEFT_PIN_NO)==0 && digitalRead(IR_RIGHT_PIN_NO) == 1){
      turnLeft(gati);
    }
    else if(digitalRead(IR_LEFT_PIN_NO)==0 && digitalRead(IR_RIGHT_PIN_NO) == 0){
      motionStop();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void turnRight(int speed){
    analogWrite( MOTOR_LEFT_A_PIN_NO,  speed);
    // pinMode(     MOTOR_LEFT_B_PIN_NO,  OUTPUT);
    digitalWrite(MOTOR_LEFT_B_PIN_NO,  LOW);
    
    // pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);
    analogWrite( MOTOR_RIGHT_B_PIN_NO, LOW);

    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
}
void turnLeft(int speed){
  analogWrite( MOTOR_LEFT_A_PIN_NO,  LOW);
    // pinMode(     MOTOR_LEFT_B_PIN_NO,  OUTPUT);
    digitalWrite(MOTOR_LEFT_B_PIN_NO,  LOW);
    // pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);
    analogWrite( MOTOR_RIGHT_B_PIN_NO, speed);

    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
}

void motionForward_1(int speed) {
    analogWrite( MOTOR_LEFT_A_PIN_NO,  speed);
    // pinMode(     MOTOR_LEFT_B_PIN_NO,  OUTPUT);
    digitalWrite(MOTOR_LEFT_B_PIN_NO,  LOW);
    
    // pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    //digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);
   // analogWrite( MOTOR_RIGHT_B_PIN_NO, speed);

    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);    //??
}   
///////////////////////////////////////////////////
void motionForward_2(int speed) {
    //analogWrite( MOTOR_LEFT_A_PIN_NO,  speed);
    // pinMode(     MOTOR_LEFT_B_PIN_NO,  OUTPUT);
    //digitalWrite(MOTOR_LEFT_B_PIN_NO,  LOW);
    
    // pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);
    analogWrite( MOTOR_RIGHT_B_PIN_NO, speed);

    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);    //??
}   


/////////////////////////////////////
void motionReverse(int speed) {
    // pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_LEFT_A_PIN_NO, LOW);
    analogWrite( MOTOR_LEFT_B_PIN_NO, speed);

    analogWrite( MOTOR_RIGHT_A_PIN_NO, speed);
    // pinMode(     MOTOR_RIGHT_B_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_RIGHT_B_PIN_NO, LOW);
    
    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_ENABLE);
}
/////////////////////////////////////
void motionStop(void) {
    // pinMode(     MOTOR_RIGHT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_RIGHT_A_PIN_NO, LOW);
    pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_LEFT_B_PIN_NO, LOW);

    // pinMode(     MOTOR_LEFT_A_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_LEFT_A_PIN_NO, LOW);
    pinMode(     MOTOR_LEFT_B_PIN_NO, OUTPUT);
    digitalWrite(MOTOR_LEFT_B_PIN_NO, LOW);

    digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_STANDBY);
}
/////////////////////////////////////
float batteryVoltageCheck(void) {
    int adcCount = analogRead(BATTERY_VOLTAGE_CHECK_PIN_NO);
    float voltageOfBattery;

    voltageOfBattery = adcCount * adcCountToVolt;

    if(voltageOfBattery < BATTERY_LOW_VOLTAGE_CUTOFF) {
        digitalWrite(MOTOR_STANDBY_PIN_NO, MOTOR_DRIVER_STANDBY);
        digitalWrite(IR_ON_PIN_NO, LOW);

        
    }
    return voltageOfBattery;
}

#include <PinChangeInt.h>

#define CH_1 3   // Throttle
#define CH_2 4   // Yaw
#define CH_3 5    //Pitch  
#define CH_4 7   //Roll
#define CH_5 8  //Switching

#define ROUNDING_BASE 50

#define ESC_MIN 800
#define ESC_MAX 2200
#define ESC_TAKEOFF_OFFSET 900
#define ESC_ARM_DELAY 5000


#define CH_1_HIGH 1800
#define CH_1_LOW 1100
#define CH_2_HIGH 1050
#define CH_2_LOW 1900
#define CH_3_HIGH 1900
#define CH_3_LOW 1050
#define CH_4_HIGH 1050
#define CH_4_LOW 1900

#define PITCH_MIN_ANG -30
#define PITCH_MAX_ANG 30
#define ROLL_MIN_ANG -30
#define ROLL_MAX_ANG 30
#define YAW_MIN_ANG -20
#define YAW_MAX_ANG 20

boolean interruptLock = false;


float ch1, ch2, ch3, ch4, ch5;
float rc_yaw, rc_pitch, rc_roll, rc_yaw_pre, rc_pitch_pre, rc_roll_pre;
int throttle, throttle_pre;
   
unsigned long chLastChange1 = micros();
unsigned long chLastChange2 = micros();
unsigned long chLastChange3 = micros();
unsigned long chLastChange4 = micros();
unsigned long chLastChange5 = micros();

void setup()
{
  Serial.begin(115200);
  initRC();
}

void loop()
{

  ch1 = int(ch1/ROUNDING_BASE)*ROUNDING_BASE;
  throttle = map(ch1, CH_1_LOW, CH_1_HIGH, ESC_MIN, ESC_MAX);
  
   ch2 = int(ch2/ROUNDING_BASE)*ROUNDING_BASE;
   ch3 = int(ch3/ROUNDING_BASE)*ROUNDING_BASE;
   ch4 = int(ch4/ROUNDING_BASE)*ROUNDING_BASE;
    
    
   rc_yaw = map(ch2, CH_2_LOW, CH_2_HIGH, YAW_MIN_ANG, YAW_MAX_ANG) ;
   rc_pitch = map(ch3, CH_3_LOW, CH_3_HIGH, PITCH_MIN_ANG, PITCH_MAX_ANG) ;
   rc_roll = map(ch4, CH_4_LOW, CH_4_HIGH, ROLL_MIN_ANG, ROLL_MAX_ANG) ;
  
  if((throttle < ESC_MIN) || (throttle > ESC_MAX))
  {
    throttle = throttle_pre;
  }
  if((rc_yaw < YAW_MIN_ANG) || (rc_yaw > YAW_MAX_ANG))
  {
    rc_yaw = rc_yaw_pre;
   }
  if((rc_pitch < PITCH_MIN_ANG) || (rc_pitch > PITCH_MAX_ANG))
  {
    rc_pitch = rc_pitch_pre;
   }
   if((rc_roll < ROLL_MIN_ANG) || (rc_roll > ROLL_MAX_ANG))
   {
     rc_roll = rc_roll_pre;
   }
   
   throttle_pre = throttle;
   rc_yaw_pre = rc_yaw;
   rc_pitch_pre = rc_pitch;
   rc_roll_pre = rc_roll;
  
  
  
  Serial.print("Throttle : ");
  Serial.print(throttle);
  Serial.print("\t"); 
  Serial.print("Yaw: ");
  Serial.print(rc_yaw);
  Serial.print("\t"); 
  Serial.print("Pitch: ");
  Serial.print(rc_pitch);
  Serial.print("\t"); 
  Serial.print("Roll : ");
  Serial.print(rc_roll);
  Serial.print("\t");
  Serial.print("Switch : ");
  Serial.print(ch5);
  Serial.println("\t");
  
}

inline void initRC()
{
  PCintPort::attachInterrupt(CH_1, chInterrupt1, CHANGE);
  PCintPort::attachInterrupt(CH_2, chInterrupt2, CHANGE);
  PCintPort::attachInterrupt(CH_3, chInterrupt3, CHANGE);
  PCintPort::attachInterrupt(CH_4, chInterrupt4, CHANGE);
  PCintPort::attachInterrupt(CH_5, chInterrupt5, CHANGE);
}

inline void chInterrupt1()
{
   if(!interruptLock) ch1 = micros() - chLastChange1;
   chLastChange1 = micros(); 
}

inline void chInterrupt2()
{
   if(!interruptLock) ch2 = micros() - chLastChange2;
   chLastChange2 = micros(); 
}

inline void chInterrupt3()
{
   if(!interruptLock) ch3 = micros() - chLastChange3;
   chLastChange3 = micros(); 
}

inline void chInterrupt4()
{
   if(!interruptLock) ch4 = micros() - chLastChange4;
   chLastChange4 = micros(); 
}

inline void chInterrupt5()
{
   if(!interruptLock) ch5 = micros() - chLastChange5;
   chLastChange5 = micros(); 
}
inline void acquireLock(){
  interruptLock = true; 
}

inline void releaseLock(){
  interruptLock = false;
}


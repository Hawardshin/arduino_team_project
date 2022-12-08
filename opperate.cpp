#include "auto_system.h"
#include "CDS.h"
Servo Penservo;
Servo Rotateservo;

int cnt = 0;
CDS CDS1(A0, 40, 0);		 //객체 led1 생성
CDS CDS2(A1, 40, 0);		 //객체 led2 생성

volatile int state = 0;

void emergency() {                  	// ISR
  digitalWrite(LED_OPERATE,LOW);
  if (cnt != 0)
  {
    Penservo.write(180);
    delay(200);
    Rotateservo.write(0);
  }
  if (state == 0)
  {
    digitalWrite(LED_DANGER,HIGH);
    digitalWrite(LED_OPERATE,LOW);
    Serial.println("-------EMERGENCY STATE------");
    state =1;
  }
  else if (state == 1)
  {
    digitalWrite(LED_DANGER,LOW);
    digitalWrite(LED_OPERATE,HIGH);
    Serial.println("------NOMAL_STATE-------");
    state =0;
  }
  delay(200);
  CDS1.STATE = 0;
  CDS2.STATE = 0;
}

void  move_rotate(int i)
{
  int angle = 1;//you can change the angle
  Rotateservo.write(i * angle);
  delay(50);
}

void  move_pen(int time)//time is in second 1000ms
{
  int angle = 25;
  for (int i = 0; i <= 5; i++)
  {
    digitalWrite(LED_OPERATE,LOW);
    Penservo.write(180 - (i * angle)/5);
    //  Penservo.write((i * angle)/5);
    delay(time * 100);
    digitalWrite(LED_OPERATE,HIGH);
    if (state == 1)
      return ;
  }
  for (int i = 5; i > 0; i--)
  {
    digitalWrite(LED_OPERATE,LOW);
    // Penservo.write((i * angle)/5);
    Penservo.write(180 - (i * angle)/5);
    delay(time * 100);
    digitalWrite(LED_OPERATE,HIGH);
    if (state == 1)
      return ;
  }
  // Penservo.write(180);
  Penservo.write(180);
}

// pen_angle = ?
// rotate_angle = ?

int  check_state()
{
  CDS1.STATE = 0;
  CDS2.STATE = 0;
  CDS1.update();
  CDS2.update();
  if(CDS1.STATE+CDS2.STATE == 2)
    {
      Serial.println("----it went dark----");
      state = 0;
      emergency();
    }
  if (state == 1)// 1 is danger
  {
      Serial.println("!!!!The danger is detected!!!!!");
      return (1);
  }
  return (0);    
}

int main_opperate(semiconductor obj)
{
  Serial.println("\n----------!!operate start!!-------------\n");
  int i = 0;
  int q =  obj.ret_quantity();
  int delay_time = obj.ret_delay_time();
  while (i < q)
  {
    move_rotate(i*10);
    if (check_state())
      return (1);
    move_pen(delay_time);
    if (check_state())
      return (1);
    delay(1000);
    i++;
  }
  Serial.println("The operation is done");
  print_aline();
  return (1);
}

int  operate_machine(semiconductor *obj,int obj_num)
{
  digitalWrite(LED_OPERATE,HIGH);
  char  temp;
  state = 0;
  if (cnt == 0)
  {
    Penservo.attach(pen_servo);
    Rotateservo.attach(rotate_servo);
    //하강 에지
    cnt++;
  }
   for(int i=0; i < strlen_P(opperate_messege); i++){
    temp = pgm_read_byte_near(opperate_messege+i);
    Serial.print(temp);
  }
  print_obj_list_name(obj, obj_num);
  while (1)
  {
    if (Serial.available() >= 1)
    {
      int num = Serial.parseInt();
      if (num >= obj_num || num < 0 )
      {
        Serial.println(num);
        Serial.println("you must input available number");
      }
      else 
      {
        Serial.print("you choose ");
        Serial.print(obj[num].ret_name());
        Serial.println("right? (y/n)");
        while (1)
        {
          if (Serial.available() >= 1)
          {
            
            String s = Serial.readString();
            if (s == "y")
            {
               if (main_opperate(obj[num]))
               {
                 digitalWrite(LED_OPERATE,LOW);
                 digitalWrite(LED_DANGER,LOW);
                    return (1);
               }                    
            }
            else if (s == "n")
            {
              Serial.println("NO");
              break ;
            }
            else
            {
              String name = obj[num].ret_name();
              Serial.print("you choose  :");
              Serial.print(name);
              Serial.println(" right? (y/n)");
            }
          }
        }
      }
      print_obj_list_name(obj, obj_num);
    }
  }
  
  return (1);
}



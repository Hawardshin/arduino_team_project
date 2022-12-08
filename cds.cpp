#include<arduino.h>
#include"CDS.h"

CDS::CDS(int pin , int intensity, int state) {  	// 생성자
  PIN=pin;
  INTEN=intensity;
  STATE=state;
}

void CDS::update() {                  // 주기적 호출 필요
  float adc=analogRead(PIN);
  if (adc <= INTEN)
    STATE = 1;
}
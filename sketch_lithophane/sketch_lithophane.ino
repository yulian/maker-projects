/*
 * 블루투스 통신을 이용해 스마트폰으로 리쏘페인 조명(무드등)을 제어하는 코드
 * 
 * 블루투스 모듈(HC-06, HM-10 등)을 이용해 명령어를 전달한다.
 * 스마트폰 앱을 통해 무선 데이터를 전송하여 명령에 따라 무드등을 On/Off 시킨다.
 * 더 많은 정보는 토이 메이커스 http://cafe.naver.com/toymakers
 * 
 * 2017년 9월 19일 생성됨 by 메이커멘토(토이메이커스)
 * 
 */

#define PIN_LITHOPHANE  2

void setup() {
  // 블루투스 통신을 위한 시리얼 초기화(0번:RX, 1번:TX로 사용)
  Serial.begin(9600);

  // 아두이노 나노에 연결된 리쏘페인 조명의 핀번호 초기화
  // 전원이 들어왔을 때 켜짐(On)을 기본 값으로 세팅
  pinMode(PIN_LITHOPHANE, OUTPUT);
  digitalWrite(PIN_LITHOPHANE, HIGH);
}

void loop() {

  // 블루투스 통신을 통해 명령어를 수신한 경우 if문 동작
  if (Serial.available()) {

    // 블루투스로 수신된 명령어를 command에 저장
    char command = Serial.read();

    if (command == 'O' || command == 'o') {

      // 명령어가 대문자 'O' 또는 소문자 'o'인 경우 무드등 켜기
      digitalWrite(PIN_LITHOPHANE, HIGH);
    }
    else {
      // 명령어가 대문자 'O' 또는 소문자 'o'이 아닌 경우 무드등 끄기
      digitalWrite(PIN_LITHOPHANE, LOW);
    }
  }

  // 일정시간 지연
  delay(100);
}


/*
 * 블루투스 통신을 통해 스마트폰으로 제어하는 이륜(2WD) RC카 코드
 *
 * 블루투스 모듈(HC-06, HM-10 등)을 이용해 명령어를 전달한다.
 * 스마트폰 앱을 통해 무선 데이터를 전송하여 명령에 따라 RC카를 조종한다.
 * 소프트웨어 시리얼을 사용해 프로그램 업로드 시 충돌을 방지한다.
 * 초음파 센서를 활용해 장애물 발견 시 우회하여 동작한다.
 * 더 많은 정보는 토이 메이커스 http://cafe.naver.com/toymakers
 *
 * 2018년 2월 14일 생성됨 by 메이커멘토(Yulian)
 *
 */
 
#include <SoftwareSerial.h>       // 소프트웨어로 시리얼통신 제어를 위한 라이브러리 참조

SoftwareSerial BTSerial(13, 12);  // 블루투스 모듈의 TX:13번핀 RX:12번핀

// 모터A의 핀배열 초기화
#define ENA 3
#define EN1 2
#define EN2 4

// 모터B의 핀배열 초기화
#define ENB 5
#define EN3 7
#define EN4 6

int carSpeed = 200; // RC카의 속도

// 초음파 센서 핀 초기화
#define TRIG 8
#define ECHO 9

// 장애물 회피를 위한 모드와 플래그
#define COMMAND   1
#define OBSTACLE  2
int mode = COMMAND;
int flag = 0;

// 블루투스에서 수신된 명령어 저장을 위한 변수 정의
char command = 0;

void setup() {
  // 소프트웨어 시리얼통신 초기화
  // HC-06과 HM-10은 보어레이트가 9600으로 초기화되어 있음
  BTSerial.begin(9600);

  // 거리를 출력하기 위해 시리얼통신 초기화
  Serial.begin(9600);

  // 모터 활성화핀 출력모드로 초기화
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // 모터A의 두 핀을 출력 모드로 초기화
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  // 모터B의 두 핀을 출력 모드로 초기화
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  // 초음파 센서 모드 초기화
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  // 입력받은 명령어에 따라 모드를 변경하는 코드
  if (BTSerial.available()) {
    command = BTSerial.read(); // 블루투스로 수신된 명령어를 command에 저장
    if (command == 'A' || command == 'a') {
      // A 또는 a를 입력으로 받는 경우 RC카를 장애물 회피 모드로 변경
      mode = OBSTACLE;
      Serial.println("OBSTACLE mode");
    } else {
      // 수신된 명령어에 따라 움직이는 명령어 모드로 변경
      mode = COMMAND;
      Serial.println("COMMAND mode");
    }
  }

  // 선택된 모드에 따라 동작
  if (mode == OBSTACLE) {
    obstacle_avoidance();   // 장애물 회피 모드
  } else {
    command_mode(command);  // 명령어 모드
  }

  // 일정시간 지연
  delay(100);
}

void moving_forward() {
  // 모터A를 정방향으로 회전
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, carSpeed);

  // 모터B를 정방향으로 회전
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, carSpeed);
}

void moving_backward() {
  // 모터A를 역방향으로 회전
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, carSpeed);

  // 모터B를 역방향으로 회전
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, carSpeed);
}

void moving_left() {
  // 모터A를 정방향으로 회전
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, carSpeed);

  // 모터B를 역방향으로 회전
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, carSpeed);
}

void moving_right() {
  // 모터A를 역방향으로 회전
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, carSpeed);

  // 모터B를 정방향으로 회전
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, carSpeed);
}

void stop_moving() {
  // 모터A와 모터B를 비활성화
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}


void obstacle_avoidance() {
  
  digitalWrite(TRIG, LOW);  // 트리거 핀에 전압을 0V로 하여 동작하지 않게 함
  delayMicroseconds(2);     // 송출 신호와 수신 신호 사이에 일정시간 지연
  digitalWrite(TRIG, HIGH); // 트리거 핀에 전압을 가하여 초음파를 송출함
  delayMicroseconds(5);     // 5 마이크로초(0.005 밀리초) 동안 초음파를 송출함
  digitalWrite(TRIG, LOW);  // 초음파 송출 정지

  // 에코 핀의 값이 HIGH가 되는 순간의 시간 측정
  // 0 또는 마이크로초(백만분의 1초)가 pulseIn() 함수의 반환 값으로 전달됨
  long duration = pulseIn(ECHO, HIGH);
  
  // HC-SR04 초음파 센서 모듈의 데이터시트를 확인 (초음파 센서에 따라 스펙이 다를 수 있으므로 반드시 데이터시트 확인 필요)
  // 공식: 마이크로초(uS) / 58 = 센티미터(centimeters) 라는 것을 알 수 있음
  long cm = duration / 58;

  // 장애물이 15cm 범위 내에 있으면 우측 회전 후 직진
  if (cm < 15) {
    if (flag == 0) {
      stop_moving();
      moving_backward();
      delay(500);
      moving_right();
      delay(500);
      moving_forward();
      flag = 1;
    }
  }
  else {
    // 장애물이 없는 경우 직진
    moving_forward();
    flag = 0;
  }

  // 시리얼로 거리를 출력한다. 예) 15cm
  Serial.print(cm);
  Serial.println("cm");
}

void command_mode(char command) {

  if (command == 'F' || command == 'f') {
    // F 또는 f를 입력으로 받는 경우 RC카를 전진시키는 함수 호출
    moving_forward();
  }
  else if (command == 'B' || command == 'b') {
    // B 또는 b를 입력으로 받는 경우 RC카를 후진시키는 함수 호출
    moving_backward();
  }
  else if (command == 'L' || command == 'l') {
    // L 또는 l을 입력으로 받는 경우 RC카를 왼쪽으로 회전시키는 함수 호출
    moving_left();
  }
  else if (command == 'R' || command == 'r') {
    // R 또는 r을 입력으로 받는 경우 RC카를 오른쪽으로 회전시키는 함수 호출
    moving_right();
  }
  else if (command == 'S' || command == 's') {
    // S 또는 s를 입력으로 받는 경우 RC카를 정지시키는 함수 호출
    stop_moving();
  }
  else {
    // 인식하지 못하는 명령어 수신시 RC카를 정지시키는 함수 호출
    stop_moving();
  }
    
}


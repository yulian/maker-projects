/*
 * 블루투스 통신을 통해 스마트폰으로 제어하는 이륜(2WD) RC카 코드
 * 
 * 블루투스 모듈(HC-06, HM-10 등)을 이용해 명령어를 전달한다.
 * 스마트폰 앱을 통해 무선 데이터를 전송하여 명령에 따라 RC카를 조종한다.
 * 더 많은 정보는 토이 메이커스 http://cafe.naver.com/toymakers
 * 
 * 2017년 5월 23일 생성됨 by 율리안(Yulian)
 * 
 */

// 모터A의 핀배열 초기화
#define ENA 3
#define EN1 2
#define EN2 4

// 모터B의 핀배열 초기화
#define ENB 5
#define EN3 7
#define EN4 6

int carSpeed = 200; // RC카의 속도

void setup() {
  Serial.begin(9600);   // 시리얼 통신 초기화(0번:RX, 1번:TX로 사용)

  // 모터 활성화핀 출력모드로 초기화
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // 모터A의 두 핀을 출력 모드로 초기화
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  // 모터B의 두 핀을 출력 모드로 초기화
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
}

void loop() {

  if (Serial.available()) {
    
    char command = Serial.read(); // 블루투스로 수신된 명령어를 command에 저장
    
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


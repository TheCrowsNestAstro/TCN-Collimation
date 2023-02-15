#include <Arduino.h>
#include <CommandParser.h>

typedef CommandParser<> MyCommandParser;

// A
#define AC_PIN 3
#define ACC_PIN 5

// B
#define BC_PIN 6
#define BCC_PIN 9

// C
#define CC_PIN 10
#define CCC_PIN 11

MyCommandParser parser;
/*
void cmd_test(MyCommandParser::Argument *args, char *response) {
  Serial.print("string: "); Serial.println(args[0].asString);
  Serial.print("double: "); Serial.println(args[1].asDouble);
  Serial.print("int64: "); Serial.println((int32_t)args[2].asInt64); // NOTE: on older AVR-based boards, Serial doesn't support printing 64-bit values, so we'll cast it down to 32-bit
  Serial.print("uint64: "); Serial.println((uint32_t)args[3].asUInt64); // NOTE: on older AVR-based boards, Serial doesn't support printing 64-bit values, so we'll cast it down to 32-bit
  strlcpy(response, "success", MyCommandParser::MAX_RESPONSE_SIZE);
}
*/

void smoothStart(uint8_t pin)
{
  Serial.println("starting");
  for(int i=0; i<255; i++){
    analogWrite(pin, i);
    delay(5);
  }
}

void smoothStop(uint8_t pin)
{
  Serial.println("stopping");
  for(int i=255; i>0; i--){
    analogWrite(pin, i);
    delay(5);
  }
}

void runMotor(uint8_t pin)
{
  Serial.println("starting");
  for(int i=0; i<255; i++){
    analogWrite(pin, i);
    delay(5);
  }

  Serial.println("stopping");
  for(int i=255; i>0; i--){
    analogWrite(pin, i);
    delay(5);
  }
}

void cmd_motorA(MyCommandParser::Argument *args, char *response) {
  String dir = args[0].asString;
  int32_t state = (int32_t)args[1].asInt64;

  if(dir == "C")
  {
    if(state == 1)
    {
      smoothStart(AC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(AC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
  else if(dir == "CC")
  {
    if(state == 1)
    {
      smoothStart(ACC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(ACC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
}

void cmd_motorB(MyCommandParser::Argument *args, char *response) {
  String dir = args[0].asString;
  int32_t state = (int32_t)args[1].asInt64;

  if(dir == "C")
  {
    if(state == 1)
    {
      smoothStart(BC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(BC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
  else if(dir == "CC")
  {
    if(state == 1)
    {
      smoothStart(BCC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(BCC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
}

void cmd_motorC(MyCommandParser::Argument *args, char *response) {
  String dir = args[0].asString;
  int32_t state = (int32_t)args[1].asInt64;

  if(dir == "C")
  {
    if(state == 1)
    {
      smoothStart(CC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(CC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
  else if(dir == "CC")
  {
    if(state == 1)
    {
      smoothStart(CCC_PIN);
      strlcpy(response, "running", MyCommandParser::MAX_RESPONSE_SIZE);
    }
    else
    {
      smoothStop(CCC_PIN);
      strlcpy(response, "idle", MyCommandParser::MAX_RESPONSE_SIZE);
    }
  }
}

void command(char motor, int direction)
{
  // direction
  // 0 = counter clockwise
  // 1 = clockwise

  switch (motor)
  {
  case 'A':
    if(direction == 0)
    {
      runMotor(ACC_PIN);
    }
    else if(direction == 1)
    {
      runMotor(AC_PIN);
    }
    break;
  case 'B':
    if(direction == 0)
    {
      runMotor(BCC_PIN);
    }
    else if(direction == 1)
    {
      runMotor(BC_PIN);
    }
    break;
  case 'C':
    if(direction == 0)
    {
      runMotor(CCC_PIN);
    }
    else if(direction == 1)
    {
      runMotor(CC_PIN);
    }
    break;
  default:
    break;
  }
}

void setup() {
  Serial.begin(19200);
  while (!Serial);

  // A
  pinMode(AC_PIN, OUTPUT);
  pinMode(ACC_PIN, OUTPUT);

  // B
  pinMode(BC_PIN, OUTPUT);
  pinMode(BCC_PIN, OUTPUT);
  
  // C
  pinMode(CC_PIN, OUTPUT);
  pinMode(CCC_PIN, OUTPUT);

  analogWrite(AC_PIN, 0);
  analogWrite(ACC_PIN, 0);
  analogWrite(BC_PIN, 0);
  analogWrite(BCC_PIN, 0);
  analogWrite(CC_PIN, 0);
  analogWrite(CCC_PIN, 0);

  

  //Motor A Clockwise/Counter Clockwise
  //parser.registerCommand("A", "si", &cmd_motorA);

  //Motor B Clockwise/Counter Clockwise
  //parser.registerCommand("B", "si", &cmd_motorB);
  
  //Motor C Clockwise/Counter Clockwise
  //parser.registerCommand("C", "si", &cmd_motorC);
  

  // Serial.println("registered command: TEST <string> <double> <int64> <uint64>");
  // Serial.println("example: TEST \"\\x41bc\\ndef\" -1.234e5 -123 123");
}

void loop() {
  if (Serial.available()) {
    char line[128];
    size_t lineLength = Serial.readBytesUntil('\n', line, 127);
    //line[lineLength] = '\0';

    //Serial.println(line[0]);
    //Serial.println(String(line[1]).toInt());

    command(line[0], String(line[1]).toInt());

    //char response[MyCommandParser::MAX_RESPONSE_SIZE];
    //parser.processCommand(line, response);
    //Serial.println(response);
  }
}
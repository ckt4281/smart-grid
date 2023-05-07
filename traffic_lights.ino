int GREEN1 = 2;
int YELLOW1 = 3;
int RED1 = 4;

int GREEN2 = 5;
int YELLOW2 = 6;
int RED2 = 7;

void setup() {
  pinMode(GREEN1, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(RED2, OUTPUT);

  digitalWrite(GREEN1, HIGH);
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(RED1, HIGH);

  digitalWrite(GREEN2, HIGH);
  digitalWrite(YELLOW2, HIGH);
  digitalWrite(RED2, HIGH);

}

void loop() {

green1on_green2off();
delay(5000);

yellow_light_1();
delay(2000);

green1off_green2on();
delay(5000);

yellow_light_2();
delay(2000);

}


void green1on_green2off()
{

  digitalWrite(GREEN1, LOW);
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(RED1, HIGH);

  digitalWrite(GREEN2, HIGH);
  digitalWrite(YELLOW2, HIGH);
  digitalWrite(RED2, LOW);
}

void yellow_light_1()
{
  digitalWrite(GREEN1, HIGH);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(RED1, HIGH);

  digitalWrite(GREEN2, HIGH);
  digitalWrite(YELLOW2, HIGH);
  digitalWrite(RED2, LOW);

}

void green1off_green2on()
{
  digitalWrite(GREEN1, HIGH);
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(RED1, LOW);

  digitalWrite(GREEN2, LOW);
  digitalWrite(YELLOW2, HIGH);
  digitalWrite(RED2, HIGH);
}

void yellow_light_2()
{
  digitalWrite(GREEN1, HIGH);
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(RED1, LOW);

  digitalWrite(GREEN2, HIGH);
  digitalWrite(YELLOW2, LOW);
  digitalWrite(RED2, HIGH);
}
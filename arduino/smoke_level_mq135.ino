int smokeS = A1;

int data = 0;

int led = 13;

int flag = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(smokeS, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(smokeS);

  Serial.print("Smoke: ");
  Serial.println(data);


if ((data < 230) && (flag == 0))
{
  digitalWrite(led, LOW);
  flag = 1;
}

if ((data >+ 230) && (flag == 1))
{
  digitalWrite(led, HIGH);
  flag = 0;
}
delay(1000);
}

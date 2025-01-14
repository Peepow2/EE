#include <iostream>
int main()
{
    std::string name = "Peerawich Sodsuay";
    std::cout << "Hello world! My name is " << name << ".";
    return 0;
} "https://onlinegdb.com/saH_4A5oB"

// ---------------------------------------------------------- //
int LED_pin = 5;
void setup() 
{
  pinMode(LED_pin, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_pin, HIGH);
  delay(1000);
  digitalWrite(LED_pin, LOW);
  delay(1000);
} "https://wokwi.com/projects/420079422533783553"


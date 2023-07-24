#include <Adafruit_I2CDevice.h>
#include <Pixy2.h>
#include <Servo.h>
#define ServoPin_X 7
#define ServoPin_Y 8
#define ServoPin_1 9
#define ServoPin_2 10

Servo Det_Servo_X
Servo Det_Servo_Y
Servo Shoot_Servo_1
Servo Shoot_Servo_2

Pixy2 pixy;

String Shoot;
String Cordinates;
void setup() 
{
    Serial.begine(115200);
    Serial.println("Starting");
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);    
    Det_Servo_X.attach(ServoPin_X);
    Det_Servo_Y.attach(ServoPin_Y);
    Shoot_Servo_1.attach(ServoPin_1);
    Shoot_Servo_2.attach(ServoPin_2);
    pixy.init();

}

void loop() 
{
    Det_Servo_X.write(0);
    Det_Servo_Y.write(0);
    Shoot_Servo_1.write(0);
    Shoot_Servo_2.write(0);
    degitalWrite(12,LOW);
    degitalWrite(13,LOW);
    pixy.ccc.getBlocks();

    if (Serial.available() > 0)
    {
        Serial.println("Please input X and Y cordinates ( x,y  ,   202,122 )")
        Cordinates = Serial.readStringUntil('/n')
        Serial.println(Cordinates)
    }
    Det_Servo_X.write((int)Cordinates[0]);
    Det_Servo_Y.write((int)Cordinates[2]);
    if (Serial.available() > 0)
    {
        Serial.println("please enter Shoot if you want to shoot(shot or Shot )")
        Shoot = Serial.readStringUntil('\n');
    }
    if (Shoot = "Shoot" || Shoot = "shoot")
    {
        myservo.write(180);
        myservo_two.write(90);
        delay(5000);
        myservo.write(0);
        myservo_two.write(0);
    }
    if (pixy.ccc.numBlocks)
    {
        Serial.print("Detected ");
        Serial.println(pixy.ccc.numBlocks);
        for (int i = 0;i < pixy.ccc.numBlocks;i++)
        {
            Serial.print(i);
            Serial.print(": ");
            pixy.ccc.blocks[i].print();
            // if the object is near the right edge of the camera
            // եթե օբյեկտը գտնվում Է տեսախցիկի աջ եզրին մոտիկ
            if (pixy.blocks[i].x >= 290)
            {
                digitalWrite(12,HIGH);
                delay(1000);
                digitalWrite(12,LOW);
            }

            // if the object is close to the left edge of the camera
            // եթե օբյեկտը գտնվում Է տեսախցիկի ձախ եզրին մոտիկ
            if (pixy.blocks[i].x <= 20)
            {
                digitalWrite(13,HIGH);
                delay(1000);
                digitalWrite(13,LOW);
            }
        }
    }  
}

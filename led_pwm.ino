const int pwm_pin = 12;
const int boton = 4;

const int pwm_canal = 0;
const int pwm_freq = 10000; //frecuencia en hertz
const int pwm_resolu = 8; //resolucion de 8 bits

int onda = 0;
float t;
float dutyCycle = 0;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT_PULLDOWN);

  ledcSetup(pwm_canal, pwm_freq, pwm_resolu);
  ledcAttachPin(pwm_pin, pwm_canal);
}

void loop() {
  // polling button

  if(digitalRead(boton)){
    onda++;
    if(onda > 7){
      onda = 0;
      }
      Serial.println(onda);
      delay(500);
    }
    t++;
    if(onda >= 256){
      t = 0;
      }
      
      switch(onda){

        case 0:
          dutyCycle = 0;
        break;

        case 1:
          dutyCycle = 0.3;
        break;

        case 2:
          dutyCycle = 0.5;
        break;
         
        case 3:
          dutyCycle = 0.8;
        break;
          
        case 4:
          dutyCycle = 1;
        break;
        //Formas de onda variables
        case 5:
          dutyCycle = (t+0.1)/256;
          delay(2.5);
        break;

        case 6:
          dutyCycle = 0.5*sin(2*PI*t/256) + 0.5;
          delay(0.5);
        break;

        case 7:
          dutyCycle = pow(2.71828, ((t/255)-1)+2);
          delay(4);
        break;
        
        }

        Serial.println(dutyCycle*255);
        ledcWrite(pwm_canal,dutyCycle*255);
}
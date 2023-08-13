//Definiciones
#define coil_pin 9

//Configuracion inicial
void setup()
{
  //Serial.begin(9600);//Inicializamos el puerto serie
  pinMode(coil_pin, OUTPUT);
  digitalWrite(coil_pin, LOW);
}

//Funcion de codificacion manchester para generar el protocolo EM4100
void set_pin_manchester(int clock_half, int signal)
{
  // La codificación de Manchester está sincronizando el reloj con la señal.
  int man_encoded = clock_half ^ signal;
  
  // si es 1 establezca el pin BAJO, esto sintonizará la antena y el lector lo verá como una señal alta. 
 // si es 0, configura el pin en ALTO, esto desintonizará la antena y el lector lo verá como una señal baja.
  if(man_encoded == 1)
  {
     digitalWrite(coil_pin, LOW);
  }
  else
  {
    digitalWrite(coil_pin, HIGH);
  }
}

//main
void loop()
{
    // estos son los datos de la tarjeta que estamos emulando. 
    int tag[64] = //{1,1,1,1,1,1,1,1,1, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 0,0,0,0,0};
   {1,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,1,1,1,1,0,0,1,1 ,1,1,1,1,0,0,1,1,1,1,1};
    //repito x veces la tarjeta
    for(char veces=0; veces<=4; veces++)
    {
      for(int i = 0; i < 64; i++)
      { 
        set_pin_manchester(1, tag[i]);
        delayMicroseconds(256); //256 era el original
        set_pin_manchester(0, tag[i]);
        delayMicroseconds(256); 
      } 
    }
  delay(10);

 
}

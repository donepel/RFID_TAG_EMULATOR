#define coil_pin 9

void setup()
{
  pinMode(coil_pin, OUTPUT);
  digitalWrite(coil_pin, LOW);
}


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

void loop()
{
  // estos son los datos de la tarjeta que estamos emulando. 
 
  
  int tag[][64] = {{1,1,1,1,1,1,1,1,1 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,1,1,1,1,0 ,0,0,0,0,0},
                  {1,1,1,1,1,1,1,1,1 ,0,0,0,0,0 ,0,1,1,0,0 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,1,1 ,0,0,1,0,1 ,0,1,0,1,0 ,1,0,0,1,0 ,1,1,1,0,1 ,0,0,1,1,0 ,0,1,0,0,0},
                  {1,1,1,1,1,1,1,1,1 ,1,0,0,1,0 ,1,1,1,0,1 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,1,1 ,0,0,1,0,1 ,0,1,0,1,0 ,1,0,0,1,0 ,1,1,1,0,1 ,0,0,1,1,0 ,0,1,0,1,0},
                  {1,1,1,1,1,1,1,1,1 ,0,0,0,0,0 ,1,0,0,0,1 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,1,1 ,0,0,1,0,1 ,0,1,0,1,0 ,1,0,0,1,0 ,1,1,1,0,1 ,0,0,1,1,0 ,1,0,1,0,0}};
  
  char x=0;
  for(x=0; x<=4; x++)
  {
    for(int i = 0; i < 64; i++)
    {
      set_pin_manchester(0, tag[x][i]);
      delayMicroseconds(256);
      set_pin_manchester(1, tag[x][i]);
      delayMicroseconds(256); 
    }
  }
  delay(100);
}

/*
 * Программа, регистрирующая влажность, температуру и яркость
 * Отправляет результаты на COM port
 * Формат вывода: H=1.0;T=1.0;LL=1;
 */

//Пин фоторезистора (аналоговый)
int lightPin = 0;

// Пин DHT-11 (цифровой)
int DHpin = 8; 

// Массив, хранящий данные DHT-11
byte dat[5]; 

// Первоначальная настройка
void setup()
{
	Serial.begin(9600); 
	pinMode(DHpin,OUTPUT); 
}

 /*
 * Выполняется после setup()
 * Основной бесконечный цикл
 */
void loop()
{
	delay(1000); // Замер примерно 1 раз в секунду
	int lightLevel = analogRead(lightPin); //Получаем уровень освещённости 

	temp_hum(); // Получаем температуру и влажность в переменную dat
	// И выводим результат
	Serial.print("H="); 
	Serial.print(dat[0], DEC);   
	Serial.print('.'); 
	Serial.print(dat[1],DEC);	
	Serial.print(";T="); 
	Serial.print(dat[2], DEC);	
	Serial.print('.'); 
	Serial.print(dat[3],DEC);	 
	Serial.print(";LL="); 
	Serial.print(lightLevel);
	Serial.println(";");
}

// Получить данные от DHT-11 в dat
void temp_hum() 
{ 
	digitalWrite(DHpin,LOW);
	delay(30);  
	digitalWrite(DHpin,HIGH); 
	delayMicroseconds(40);
	pinMode(DHpin,INPUT);
	while(digitalRead(DHpin) == HIGH);
	delayMicroseconds(80);
	if(digitalRead(DHpin) == LOW); 
	delayMicroseconds(80);
	for(int i=0;i<4;i++)
	{
	  dat[i] = read_data();
	}
	pinMode(DHpin,OUTPUT);
	digitalWrite(DHpin,HIGH);
} 

// Получить часть данных от DHT-11
byte read_data() 
{
	byte data; 
	for(int i=0; i<8; i++) 
	{ 
		if(digitalRead(DHpin) == LOW) 
		{ 
			while(digitalRead(DHpin) == LOW); 
			delayMicroseconds(30);
			if(digitalRead(DHpin) == HIGH) 
			{
				data |= (1<<(7-i));
			}
			while(digitalRead(DHpin) == HIGH); 
		}
	} 
	return data; 
} 
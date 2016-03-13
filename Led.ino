/*  Led.ino
 *
 *  Пример получения данных по COM порту
 *  Подключите светодиод к выводу ledPin 
 *
 */

// Вывод светодиода (цифровой)
#define ledpin 8

// "Буфер" поступающих данных
String inString = "";

void setup() {
	Serial.begin(9600);
	pinMode(ledpin, OUTPUT);
	digitalWrite(ledpin, LOW);
}

void loop() {
	// Получаем данные из COM порта
	while (Serial.available() > 0) {
	int inChar = Serial.read();
	if (isDigit(inChar)) {
		// Получаем 1 символ, 
		// Прибавляем его к строке
		inString += (char)inChar;
	}

	// Доходим до новой строки
	if (inChar == '\n') {
		// Включаем светодиод
		digitalWrite(ledpin, HIGH);
		int time = inString.toInt();
		delay(time);
		digitalWrite(ledpin, LOW);
		// Обнуляем полученную строку
		inString = "";
	}
  }


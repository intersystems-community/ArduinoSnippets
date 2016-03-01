/*  Keypadtest.ino
 *
 *  Пример использования библиотеки Keypad
 *  Подключите Keypad к выводам Arduino указанным в
 *  rowPins[] and colPins[].
 *
 */

// Репозиторий библиотеки:
// https://github.com/Chris--A/Keypad
#include <Keypad.h>

const byte ROWS = 4; // Четыре строки
const byte COLS = 4; // Три столбцы
// Карта соответствия кнопок и символов
char keys[ROWS][COLS] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
// Подключите разьёмы keypad 1-8 (сверху-вниз) к Arduino разьёмам 11-4. 1->11, 2->10, ... , 8->4 
// Подключите keypad ROW0, ROW1, ROW2 и ROW3 к этим выводам Arduino
byte rowPins[ROWS] = { 7, 6, 5, 4 };
// Подключите keypad COL0, COL1 and COL2 к этим выводам Arduino
byte colPins[COLS] = { 8, 9, 10, 11 }; 

// Инициализация Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

void setup()
{
	Serial.begin(9600); 
}

void loop()
{
	char key = kpd.getKey(); // Поолучаем нажатую кнопку
	if(key)
	{
		switch (key)
	{
		case '#':
			Serial.println();
		default:
			Serial.print(key);
	}
	}
}

Class Arduino.Habr Extends %Persistent
{

/// Порт, к которому подключается Arduino
Parameter SerialPort As %String = "com5";

/// Отправляем на порт строку 1000\n
ClassMethod SendSerial(port = {..#SerialPort})
{
	open port:(:::" 0801n0":/BAUD=9600)     // Открываем устройство
	set old = $IO // Записываем текущее устройство ввода-вывода
	use port  // Переключаемся на com порт
	write $c(10) // Отправка пробного пакета данных
	hang 1
	write 1000 _$c(10) // Передаём строку 1000\n
	use old // Переключаем вывод на терминал
	close port // Закрываем устройство
}

/// Поручение одной строки данных (до конца строки)
ClassMethod ReceiveOneLine(port = {..#SerialPort}) As %String
{
	set str=""
	try {
        open port:(:::" 0801n0":/BAUD=9600)
        set old = $io //Keep track of the original device
        use port
        read str //Read until a termination character is reached
        use old
        close port
    } catch ex {
        close port
    }
    return str
}

Storage Default
{
<Data name="HabrDefaultData">
<Value name="1">
<Value>%%CLASSNAME</Value>
</Value>
</Data>
<DataLocation>^Arduino.HabrD</DataLocation>
<DefaultData>HabrDefaultData</DefaultData>
<IdLocation>^Arduino.HabrD</IdLocation>
<IndexLocation>^Arduino.HabrI</IndexLocation>
<StreamLocation>^Arduino.HabrS</StreamLocation>
<Type>%Storage.Persistent</Type>
}

}


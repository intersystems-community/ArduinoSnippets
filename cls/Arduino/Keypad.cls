/// See for general reference on the I/O commands used here:
/// http://docs.intersystems.com/cache_latest/csp/docbook/DocBook.UI.Page.cls?KEY=GIOD_termio#GIOD_tio_openuse
/// based on https://code.intersystems.com/code/Code.View.Code.cls?ID=856&title=read-serial-input-from-arduino
Class Arduino.Keypad Extends %RegisteredObject
{

Parameter SerialPort As %String = "com5";

/// Receive one line at a time, using common terminating characters (i.e., CR/LF)
/// Infinite loop, terminated by <INTERRUPT> / etc.
/// do ##class(Arduino.Keypad).ReceiveSerial()
ClassMethod ReceiveSerial(pSerialPort = {..#SerialPort})
{
	try {
        //Parameters used to open the serial device:
        //  portstate = " 0801n0" - by byte position:
        //      1: space indicates "don't disconnect the port"
        //      2: 0 indicates "don't use modem control"
        //      3: 8 indicates 8 data bits
        //      4: 0 indicates no parity
        //      5: 1 indicates one stop bit
        //      6: n indicates that flow control is disabled
        //      7: 0 indicates disable DTR
        //  /BAUD=9600 determines the baud rate, of course.
        open pSerialPort:(:::" 0801n0":/BAUD=9600)
        set old = $io //Keep track of the original device
        for {
            use pSerialPort
            read x //Read until a termination character is reached
            if (x '= "") {
                use old
                write x,!
            }
        }
    } catch anyError {
        close pSerialPort
    }
}

/// Receive one line at a time, using common terminating characters (i.e., CR/LF)
/// w ##class(Arduino.Keypad).ReceiveOneLine()
ClassMethod ReceiveOneLine(pSerialPort = {..#SerialPort}) As %String
{
	set x=""
	try {
        //Parameters used to open the serial device:
        //  portstate = " 0801n0" - by byte position:
        //      1: space indicates "don't disconnect the port"
        //      2: 0 indicates "don't use modem control"
        //      3: 8 indicates 8 data bits
        //      4: 0 indicates no parity
        //      5: 1 indicates one stop bit
        //      6: n indicates that flow control is disabled
        //      7: 0 indicates disable DTR
        //  /BAUD=9600 determines the baud rate, of course.
        open pSerialPort:(:::" 0801n0":/BAUD=9600)
        set old = $io //Keep track of the original device
        use pSerialPort
        read x //Read until a termination character is reached
        use old
        close pSerialPort       
    } catch ex {
        close pSerialPort
    }
    return x
}

/// Receive one character at a time, without any consideration for terminating characters
/// Infinite loop, terminated by <INTERRUPT> / etc.
ClassMethod ReceiveSerial1Char(pSerialPort = {..#SerialPort})
{
    try {
        //Parameters same as above, except operating in "image mode"
        //This treats all characters as data
        open pSerialPort:(:"I"::" 0801n0":/BAUD=9600)
        set old = $io //Keep track of the original device
        for {
            use pSerialPort
            read *x //Read one character at a time
            if (x '= "") {
                use old
                write $c(x) //Convert from decimal to ASCII
            }
        }
    } catch anyError {
        close pSerialPort
    }
}

/// Receive one line at a time, using common terminating characters (i.e., CR/LF)
/// Infinite loop, terminated by <INTERRUPT> / etc.
/// do ##class(Arduino.Keypad).SendSerial()
ClassMethod SendSerial1(pSerialPort = {..#SerialPort})
{
	try {
        //Parameters used to open the serial device:
        //  portstate = " 0801n0" - by byte position:
        //      1: space indicates "don't disconnect the port"
        //      2: 0 indicates "don't use modem control"
        //      3: 8 indicates 8 data bits
        //      4: 0 indicates no parity
        //      5: 1 indicates one stop bit
        //      6: n indicates that flow control is disabled
        //      7: 0 indicates disable DTR
        //  /BAUD=9600 determines the baud rate, of course.
        open pSerialPort:(:::" 0801n0":/BAUD=9600)
        set old = $io //Keep track of the original device
        //for {
            use pSerialPort
            w $c(10)
            h 1
            w 1000 _$c(10)
            use old
            close pSerialPort
            /*read x //Read until a termination character is reached
            if (x '= "") {
                use old
                write x,!
            }*/
        //}
    } catch anyError {
        close pSerialPort
    }
}

/// Receive one line at a time, using common terminating characters (i.e., CR/LF)
/// Infinite loop, terminated by <INTERRUPT> / etc.
/// do ##class(Arduino.Keypad).SendSerial()
ClassMethod SendSerial()
{
	set port = "COM1"					// Имя порта
	open port:(:::" 0801n0":/BAUD=9600)	// Открываем устройство
	set old = $io						// Записываем текущее устройство ввода-вывода
	use port							// Переключаемся на com порт
	write $c(10)						// первоначальное установление соединения
	hang 1	
	write 1000 _$c(10)					// Передаём строку 1000\n
	use old								// Переключаем вывод на терминал
	close port							// Закрываем устройство
}

}


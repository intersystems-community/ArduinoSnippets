Class Arduino.Info Extends %Persistent
{

Parameter SerialPort As %String = "com3";

Property DateTime As %DateTime;

Property Temperature As %Double;

Property Humidity As %Double(MAXVAL = 100, MINVAL = 0);

Property Brightness As %Double(MAXVAL = 100, MINVAL = 0);

Property Volume As %Double(MAXVAL = 100, MINVAL = 0);

ClassMethod AddNew(Temperature = 0, Humidity = 0, Brightness = 0, Volume = 0)
{
	set obj = ..%New()
	set obj.DateTime=$ZDT($H,3,1)
	set obj.Temperature=Temperature
	set obj.Humidity=Humidity
	set obj.Brightness=Brightness/1023*100
	set obj.Volume=Volume
	w $SYSTEM.Status.DisplayError(obj.%Save())
}

/// Receive one line at a time, using common terminating characters (i.e., CR/LF)
/// Infinite loop, terminated by <INTERRUPT> / etc.
/// do ##class(Arduino.Info).ReceiveSerial()
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
                set Humidity = $p($p(x,";",1),"=",2)
                set Temperature =  $p($p(x,";",2),"=",2)
                set Brightness =  $p($p(x,";",3),"=",2)
                do ..AddNew(Temperature,Humidity,Brightness)
            }
        }
    } catch anyError {
        close pSerialPort
    }
}

Storage Default
{
<Data name="InfoDefaultData">
<Value name="1">
<Value>%%CLASSNAME</Value>
</Value>
<Value name="2">
<Value>DateTime</Value>
</Value>
<Value name="3">
<Value>Temperature</Value>
</Value>
<Value name="4">
<Value>Humidity</Value>
</Value>
<Value name="5">
<Value>Brightness</Value>
</Value>
<Value name="6">
<Value>Volume</Value>
</Value>
</Data>
<DataLocation>^Arduino.InfoD</DataLocation>
<DefaultData>InfoDefaultData</DefaultData>
<IdLocation>^Arduino.InfoD</IdLocation>
<IndexLocation>^Arduino.InfoI</IndexLocation>
<StreamLocation>^Arduino.InfoS</StreamLocation>
<Type>%Storage.Persistent</Type>
}

}


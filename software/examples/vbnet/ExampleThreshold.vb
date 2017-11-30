Imports System
Imports Tinkerforge

Module ExampleThreshold
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your PTC Bricklet

    ' Callback subroutine for temperature reached callback (parameter has unit °C/100)
    Sub TemperatureReachedCB(ByVal sender As BrickletPTC, ByVal temperature As Integer)
        Console.WriteLine("Temperature: " + (temperature/100.0).ToString() + " °C")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim ptc As New BrickletPTC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        ptc.SetDebouncePeriod(10000)

        ' Register temperature reached callback to subroutine TemperatureReachedCB
        AddHandler ptc.TemperatureReachedCallback, AddressOf TemperatureReachedCB

        ' Configure threshold for temperature "greater than 30 °C" (unit is °C/100)
        ptc.SetTemperatureCallbackThreshold(">"C, 30*100, 0)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module

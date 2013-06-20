Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback function for temperature callback (parameter has unit °C/100)
    Sub TemperatureCB(ByVal sender As BrickletPTC, ByVal temperature As Integer)
        System.Console.WriteLine("Temperature: " + (temperature/100.0).ToString() + " °C")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim ptc As New BrickletPTC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Set Period for temperature callback to 1s (1000ms)
        ' Note: The temperature callback is only called every second if the 
        '       temperature has changed since the last call!
        ptc.SetTemperatureCallbackPeriod(1000)

        ' Register temperature callback to function TemperatureCB
        AddHandler ptc.Temperature, AddressOf TemperatureCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module

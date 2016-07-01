Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your PTC Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim ptc As New BrickletPTC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current temperature (unit is °C/100)
        Dim temperature As Integer = ptc.GetTemperature()
        Console.WriteLine("Temperature: " + (temperature/100.0).ToString() + " °C")

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module

program ExampleThreshold;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletPTC;

type
  TExample = class
  private
    ipcon: TIPConnection;
    ptc: TBrickletPTC;
  public
    procedure TemperatureReachedCB(sender: TBrickletPTC; const temperature: longint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

{ Callback procedure for temperature greater than 120 °C (parameter has unit °C/100) }
procedure TExample.TemperatureReachedCB(sender: TBrickletPTC; const temperature: longint);
begin
  WriteLn(Format('Temperature: %f °C', [temperature/100.0]));
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  ptc := TBrickletPTC.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Get threshold callbacks with a debounce time of 10 seconds (10000ms) }
  ptc.SetDebouncePeriod(10000);

  { Register threshold reached callback to procedure TemperatureReachedCB }
  ptc.OnTemperatureReached := {$ifdef FPC}@{$endif}TemperatureReachedCB;

  { Configure threshold for "greater than 120 °C" (unit is °C/100) }
  ptc.SetTemperatureCallbackThreshold('>', 120*100, 0);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.

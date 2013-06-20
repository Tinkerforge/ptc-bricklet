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
    procedure ReachedCB(sender: TBrickletPTC; const temperature: longint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

{ Callback for temperature greater than 30 °C }
procedure TExample.ReachedCB(sender: TBrickletPTC; const temperature: longint);
begin
  WriteLn(Format('We have %f °C.', [temperature/100.0]));
  WriteLn('It is too hot, we need air conditioning!');
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

  { Register threshold reached callback to procedure ReachedCB }
  ptc.OnTemperatureReached := {$ifdef FPC}@{$endif}ReachedCB;

  { Configure threshold for "greater than 30 °C" (unit is °C/100) }
  ptc.SetTemperatureCallbackThreshold('>', 30*100, 0);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.

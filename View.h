#ifndef View_h
#define View_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

#define VirtualTerminalPin V0
#define BtnControlPin V1
#define AuthenticatingPanelPin V2
#define LockStateValuePin V3

#define LCDAddress 0x27
#define LCDColumns 16
#define LCDRows 2

class View
{
public:
    View();
    void Message(String m);
    void MessageLCD(String me);
    void MessageLCD(String m1, String m2);
    void UpdateAuthPanel(int authNums[]);
    void ResetAuthPanel();
    void UpdateLockState(String value);
    void BtnControlForUnlock();
    void BtnControlForLock();

private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCDAddress, LCDColumns, LCDRows);
    WidgetTerminal terminal = WidgetTerminal(VirtualTerminalPin);
};
#endif
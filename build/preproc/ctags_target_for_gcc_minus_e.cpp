# 1 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"


# 4 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino" 2
# 5 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino" 2

# 7 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino" 2

//char auth[] = "TwCg6uFlHUNnz-yRJLxW-tfUWfP9Bclc";
char auth[] = "iE7NulbKfx6ZgO4gBgAS4T5ZYjGcA1Ot";
char ssid[] = "HostpotTP";
char pass[] = "12345678";

class View
{
public:
 View()
 {
 }
 void Message(String message)
 {
  Serial.println(message);
  terminal.println(message);
 }

private:
 WidgetTerminal terminal = WidgetTerminal(0);
};

SecureLock lock;
View view;

WidgetTerminal terminal(0);

void setup()
{
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 137, 1), 8080);

 lock = SecureLock();
 view = View();
}

void loop()
{
 Blynk.run();
}

void BlynkWidgetWrite1 (BlynkReq __attribute__((__unused__)) &request, const BlynkParam __attribute__((__unused__)) &param)
{
 // read button state
 int btnState = param.asInt();

 // If button is pushed
 if (btnState == 1)
 {
  // If button is locked
  if (lock.State() == Locked)
  {
   // If authorizing sucess
   if (lock.Authenticate() == true)
   {
    view.Message("Authenticated successfully!");
    // Unlocking
    if (lock.Lock() == true)
    {
     view.Message("Unlooking is successful! The lock is unlocked.");
    }
    else
    {
     view.Message("Unlooking is failed because of unknown reason.");
    }
   }
   else
   {
    view.Message("Authenticated failed! Cannot unlocking the lock.");
   }
  }
  if (lock.State() == Unlocked)
  {
   if (lock.Unlock() == true)
   {
    view.Message("Locking is successful! The lock is locked.");
   }
  }
  Blynk.virtualWrite(1, 0);
 }
 else
  switch (lock.State())
  {
  case Locked:
   Blynk.setProperty(1, "offLable", "Unlock");
   Blynk.setProperty(1, "onLable", "Unlocking");
   break;
  case Unlocked:
   Blynk.setProperty(1, "offLable", "Lock");
   Blynk.setProperty(1, "onLable", "Locking");
   break;
  default:
   Blynk.setProperty(1, "offLable", "NaN");
   Blynk.setProperty(1, "onLable", "NaN");
  }
}

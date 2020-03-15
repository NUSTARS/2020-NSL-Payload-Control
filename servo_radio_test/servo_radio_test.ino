#include <controller.h>
 Controller control = Controller();
void setup() {


}

void loop() {
  for(int i = 0; i < 10; i++) { 
    control._leverMove(true);
    control._wireMove(true);
    delay(50);
  }
  for (int i = 0; i < 10; i++) { 
     control._leverMove(false);
    control._wireMove(false);
    delay(50);
  }
  
}

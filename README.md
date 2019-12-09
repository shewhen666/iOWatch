# iOWatch

The main function of this program is to use the full potential off extremly accurate DS3231 (with temperature compensation) time keeping sensor
  and show us that time precice! 
 
## [Short Press] displaying time
 
  The Watch is designed with 12LED's positioned in Circle like so
 
  1. Houres are represented normal (in Circle 1, 2, 3, 4, 5, ... , 12)
  
                            |________|
                           /_. ____ ._\
                         .' -   12    -'.
                        /,' 11       1 `.\
                       // 10   ||||    2 \\
                      ::       ||||       ::
                      || 9              3 |||]
                      ::       ||||       ::
                       \\ 8    ||||    4 //
                        \`. 7        5 ,'/
                         '.`-.  6   .-'.'
                           \-.______.-/
                            |________|
               
  2. Minutes are ranging from 0 - 60 in 5min sequnce (0, 5, 10, 15, 20...) are displayed from 0-12
     (1.st LED 5min, 2nd LED 10min, 3rd LED 15min, etc..) like so.
 
                            |________|
                           /_. ____ ._\
                         .' -    0    -'.
                        /,' 55       5 `.\
                       // 50   ||||    10 \\
                      ::       ||||        ::
                      ||45              15 |||]
                      ::       ||||        ::
                       \\ 40   ||||    20 //
                        \`. 35       25 ,'/
                         '.`-.  30   .-'.'
                           \-.______.-/
                            |________|
 
  3. Rest of the minutes are displayed from 1-4min.
 
                            |________|
                           /_. ____ ._\
                         .' -    0    -'.
                        /,' --       1 `.\
                       // --   ||||    2 \\
                      ::       ||||       ::
                      ||- -             3 |||]
                      ::       ||||       ::
                       \\ --   ||||    4 //
                        \`. --      -- ,'/
                         '.`-.  --  .-'.'
                           \-.______.-/
                            |________|
             
  4. Deep sleep
 
 ### Example
 
  If its 10:23 - Pressing the button wakes the device up, reads the time. Reading the time takes three steps
  First, hours are shown so the 10'Led light up [10:--]
  After hours, second step is displaying the minutes in 5min sequance so the 4.LED will light up showing 20min [10:2-]
 
                |________|                       |________|                     |________|
               /_. ____ ._\                     /_. ____ ._\                   /_. ____ ._\
             .' -    -    -'.                 .' -    -    -'.               .' -    -    -'.
            /,' -        - `.\               /,' -        - `.\             /,' -        - `.\
           // 10   ||||    - \\             // -    ||||    - \\           // -    ||||    - \\
          ::       ||||       ::           ::       ||||       ::         ::       ||||       ::
    1. -> || -              - |||   2. ->  || -              - ||  3. ->  || -              3 |||]
          ::       ||||       ::           ::       ||||       ::         ::       ||||       ::
           \\ -    ||||    - //             \\ -    ||||   20 //           \\ -    ||||   -  //
            \`. -        - ,'/               \`. -        - ,'/             \`. -        - ,'/
             '.`-.   -  .-'.'                 '.`-.   -  .-'.'               '.`-.   -  .-'.'
               \-.______.-/                     \-.______.-/                   \-.______.-/
                |________|                       |________|                     |________|

Third and final step, the rest of minutes raging from 0 - 4 are displayed, so if 23-20 = 3 the third LED will light up [10:23].
 
## [Double Press] displaying temperature in *C
 
 
Displaying tempearture works same as displaying minutes - for now only positive +0*C temperatures are displayed
 
                            |________|
                           /_. ____ ._\
                         .' -    0    -'.
                        /,' 55       5 `.\
                       // 50   ||||    10 \\
                      ::       ||||        ::
                      ||45      *C      15 |||]
                      ::       ||||        ::
                       \\ 40   ||||    20 //
                        \`. 35       25 ,'/
                         '.`-.  30   .-'.'
                           \-.______.-/
                            |________|
 
  And the rest of it...
  
                            |________|
                           /_. ____ ._\
                         .' -    0    -'.
                        /,' --       1 `.\
                       // --   ||||    2 \\
                      ::       ||||       ::
                      || --     *C      3 |||]
                      ::       ||||       ::
                       \\ --   ||||    4 //
                        \`. --      -- ,'/
                         '.`-.  --  .-'.'
                           \-.______.-/
                            |________|
 
### Example
 
   17* C
 
  Double pressing the button wakes the device up, reads the temperature
  To show 17*C we would need 17 LEDs, right? to show the correct and precise temperature we display it same as minutes.
  
  The 15*C LED lights up
  
                            |________|
                           /_. ____ ._\
                         .' -    -    -'.
                        /,' --       - `.\
                       // --   ||||    -- \\
                      ::       ||||        ::
                      ||--      *C      15 |||]
                      ::       ||||        ::
                       \\ --   ||||    -- //
                        \`. --       -- ,'/
                         '.`-.  --   .-'.'
                           \-.______.-/
                            |________|
                
  Followed by 2*C 
  
                            |________|
                           /_. ____ ._\
                         .' -    -    -'.
                        /,' --       - `.\
                       // --   ||||    2 \\
                      ::       ||||       ::
                      || --     *C      - |||]
                      ::       ||||       ::
                       \\ --   ||||    - //
                        \`. --      -- ,'/
                         '.`-.  --  .-'.'
                           \-.______.-/
                            |________|
 
  At the end 15*C+2*C equals 17*C
 
## [Long Press] time setting mode
  
  Holding the button 3+ seconds activates the time setting mode, time setting mode consists of 3 menus, short pressing the button scrolls the time and long pressing the button goes trough menus.
  To set the time press and hold the button for more then 3 seconds, once the 12'o clock LED lights up that means you entered MENU 1 in witch you select hours time, short pressing the button you scroll trough the hours
  after selecting propper hours time, again press and hold the button to activate MENU 2, same story - short pressing the button scorls trought the minutes [0, 5, 10, 15 ...].
  Holding the button again activates the final MENU 3, setting the rest of the minutes and pressing the button again sets the time and exits the time setting menu. 
  
  
  MENU 1 Setting hours [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
  
  MENU 2 Setting minutes [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55]
  
  MENU 3 Setting minutes to five [0, 1, 2, 3, 4]
 
  HARDWARE
 
  12 LED's Connected in circle
  Atmega328 microcontroller with 8Mhz oscillator clocked at 1Mhz
  DS3231 real time clock
  CR2032 3V 225mAh battery
  ## Authors

* **Marijo Blazevic**
  
  ## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

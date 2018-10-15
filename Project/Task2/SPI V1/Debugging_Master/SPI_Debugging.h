/*
 
 SPI Debugging 
 Author: Nick Gammon
 Date:   11 October 2014

 See:  http://www.gammon.com.au/forum/?id=11329

 
 PERMISSION TO DISTRIBUTE
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in 
 all copies or substantial portions of the Software.
 
 
 LIMITATION OF LIABILITY
 
 The software is provided "as is", without warranty of any kind, express or implied, 
 including but not limited to the warranties of merchantability, fitness for a particular 
 purpose and noninfringement. In no event shall the authors or copyright holders be liable 
 for any claim, damages or other liability, whether in an action of contract, 
 tort or otherwise, arising from, out of or in connection with the software 
 or the use or other dealings in the software. 

*/


#if DEBUG 

  #define beginDebug()  do { SPI.begin (); SPI.setClockDivider(SPI_CLOCK_DIV8); } while (0)
  #define Trace(x)      SPIdebug.print   (x)
  #define Trace2(x,y)   SPIdebug.print   (x,y)
  #define Traceln(x)    SPIdebug.println (x)
  #define Traceln2(x,y) SPIdebug.println (x,y)
  #define TraceFunc()   do { SPIdebug.print (F("In function: ")); SPIdebug.println (__PRETTY_FUNCTION__); } while (0)
  
  class tSPIdebug : public Print
  {
  public:
    virtual size_t write (const byte c)  
      { 
      digitalWrite(SS, LOW); 
      SPI.transfer (c); 
      digitalWrite(SS, HIGH); 
      return 1;
      }  // end of tSPIdebug::write
  }; // end of tSPIdebug
      
  // an instance of the SPIdebug object
  tSPIdebug SPIdebug;
  
#else
  #define beginDebug()  ((void) 0)
  #define Trace(x)      ((void) 0)
  #define Trace2(x,y)   ((void) 0)
  #define Traceln(x)    ((void) 0)
  #define Traceln2(x,y) ((void) 0)
  #define TraceFunc()   ((void) 0)
#endif // DEBUG

s1 = serial('COM1');
s1.inputbuffersize = 20000;
s1.outputbuffersize = 20000;
s1.Timeout = 120;
s1.BaudRate = 57600;
s1.Terminator ='';

%s1.Parity='Odd';
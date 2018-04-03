clear all; % Baud Rate of PC- 57600, Baud rateof board- 38400
s1 = serial('COM1'); % Creating serial object s1 
s1.BaudRate = 38400; % Setting Baudrate of PC
s1.Parity='none'; % Setting parity to none  
s1.Stopbits = 1; % Enable stop bit 
s1.Terminator ='LF'; % setting the end charachter \n 
 

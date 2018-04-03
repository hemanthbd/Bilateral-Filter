% Sending Message through the Board
Tx_str =  'PE is Awesome!\n' ;  
fopen (s1); %Open serial port for communication 
fprintf(s1,Tx_str); % sending data thro’ the serial port 
Rx_str = fscanf(s1,'%c'); %receiving characters thro’ the serial port 
msgbox(Rx_str,'Serial Com'); %outputting received message 
fclose(s1); %closing communication  
delete(s1); % Deleteing s1 object 
clear all; % clearing memory 
 
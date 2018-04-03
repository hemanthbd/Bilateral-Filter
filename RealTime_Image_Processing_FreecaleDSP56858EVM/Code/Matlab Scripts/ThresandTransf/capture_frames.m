close all; %Close any existing windows
fopen(s1); %Open Serial port for communication
camlist=webcamlist;
cam=webcam(camlist{1,1});

%Grab 12 frames
for i=1:1:12
	A=snapshot(cam); % while debugging just use 'A=imread(moon.tif)' to read the moon.tif provided to you in the folder. This saves time while debugging. 

	B = rgb2gray(A); % Transform the colored image to gray level image and store in B
	B = imresize(B,[96 128],'bicubic'); % Resize the image to 96x128

	% Transform the image to a 1D vector so that it may be streamed over the serial port
	C=B(:)'; 

	fwrite(s1,C); % write the vector to serial port
	WaitForFrame=1;
	% While loop waiting for a frame to be sent from the DSP kit
	while (WaitForFrame==1)
	    if (s1.BytesAvailable == length(C))
	        WaitForFrame = 0;
	    end
	end

	% Once the frame is in the serial RS232 buffer read that
    
	D = fread(s1,s1.BytesAvailable); % Read received frame in vector format
	D = D';
	[m,n] = size(B); 
	E = ones(m,n); % Define a matrix of ones having the same size as the frame 

	% Vector to Matrix transformation; E contains the received frame in matrix format
	E(:) = D(:); 

	%gcf

	subplot(1,2,1)
	imshow(B); % Show the original image grabbed from the USB webcam
	drawnow;
	title('Input Image');

	subplot(1,2,2)
	imshow(uint8(E)); % Show the original image frame and  the processed one received from the kit side by side
	% for binary images use
	%imshow(logical(E));
	title('Output Image');
	drawnow;

end	%for i=1:1:12
clear('cam')
fclose(s1); % Close port
  
    




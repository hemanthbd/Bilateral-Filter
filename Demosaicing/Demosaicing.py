''' Program to Perfrom Demosaicing via 3 methods- Nearest Neighbours, Bilinear Interpolation and Edge-Based Interpolation Demosaicing'''

import rawpy 
import imageio
import cv2    
import numpy as np
import matplotlib.pyplot as plt
import ipdb
from PIL import Image
import colorsys


path = '/home/owner/Documents/HW1_Blackboard/HW1_Blackboard/tetons.nef'
with rawpy.imread(path) as raw: 
    rgb = raw.postprocess(gamma=(1 ,1) , no_auto_bright=True , output_bps =8)    # Demosaicing done by the RawPy package to convert the RGGB Bayer Matrix into a 3-D Image

imageio.imsave('tetons original.png', (rgb).astype('uint8')) #That Image is saved

with rawpy.imread(path) as raw: ## To Perform Demoisaicing across 3 methods, so weneed to extract the RAw image (Bayer Matrix)
	raw_image = raw.raw_image.copy() # Creating copies of the RAW matrix in 3 different variables so as to extract Reg, Green and Blue chennels from them
	raw_image1 = raw.raw_image.copy()
	raw_image2 = raw.raw_image.copy()
	raw_image3 = raw.raw_image.copy()


'''Algorithm to extract the Red Pixels as they occur at only even positions'''
for x in range(0, raw_image1.shape[0]):
	for y in range(0, raw_image1.shape[1]):
		if ((x%2==0) and (y%2==0)):
			raw_image1[x,y]=raw_image1[x,y]
		else :
			raw_image1[x,y]=0

'''Algorithm to extract the Blue Pixels as they occur at odd positions'''
for x in range(0, raw_image2.shape[0]):
	for y in range(0, raw_image2.shape[1]):
		if ((x%2!=0) and (y%2!=0)):
			raw_image2[x,y]=raw_image2[x,y]
		else :
				raw_image2[x,y]=0


red1= raw_image1.copy() # Red Pixels extractd from the BAYER Matrix
blue1= raw_image2.copy() # Blue Pixels extractd from the BAYER Matrix
green1= raw_image3-red1-blue1 # Green pixels extracted via subtracting the Red and Blue Matices from the Original RAW Bayer Pattern

red = (red1/16).astype('float32') # Converting from 12-bit to 8-bit by dividing by 2^4
blue = (blue1/16).astype('float32')# Converting from 12-bit to 8-bit by dividing by 2^4
green = (green1/16).astype('float32')# Converting from 12-bit to 8-bit by dividing by 2^4

'''Algorithm to perform downsampling then upsampling by Bilinear Interpolation Demosaicing'''
down_r=cv2.resize(red,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_LINEAR) # Downsampling the red pixels by half
down_b=cv2.resize(blue,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_LINEAR)# Downsampling the blue pixels by half
down_g=cv2.resize(green,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_LINEAR)# Downsampling the green pixels by half

rgbArray = np.zeros((1434,2160,3), 'uint8') # Creating a zero matrix where each of the channels will be stacked at different dimensions
rgbArray[..., 0] = down_r # Red channel in dimension 1 
rgbArray[..., 1] = down_g # Green channel in dimension 2 
rgbArray[..., 2] = down_b # Blue channel in dimension 3
sub_img = Image.fromarray(rgbArray)
sub_img.save('tetons_subsample.jpeg') # Subsampled Image
 
up_BL=cv2.resize(rgbArray,None,fx=2, fy=2, interpolation= cv2.INTER_LINEAR) # Upsampling the newly formed matrix by 2 times to get the original image
img = Image.fromarray(up_BL)
img.save('Bilinear.jpeg')
plt.imshow(up_BL.astype('uint8'))
plt.show()

Algorithm to perform downsampling then upsampling by Nearest Neighbours Demosaicing
down_r2=cv2.resize(red,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_AREA) # Downsampling the red pixels by half
down_b2=cv2.resize(blue,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_AREA) # Downsampling the blue pixels by half
down_g2=cv2.resize(green,None,fx=0.5, fy=0.5, interpolation= cv2.INTER_AREA)# Downsampling the green pixels by half
rgbArray2 = np.zeros((1434,2160,3), 'uint8') # Creating a zero matrix where each of the channels will be stacked at different dimensions
rgbArray2[..., 0] = down_r2  # Red channel in dimension 1 
rgbArray2[..., 1] = down_g2 # Green channel in dimension 2 
rgbArray2[..., 2] = down_b2 # Blue channel in dimension 3
up_NN=cv2.resize(rgbArray2,None,fx=2, fy=2, interpolation= cv2.INTER_AREA)# Upsampling the newly formed matrix by 2 times to get the original image
img2 = Image.fromarray(up_NN)
img2.save('Nearest_Neighbour.jpeg')
plt.imshow(up_NN.astype('uint8'))
plt.show()

'''Algorithm to perform downsampling then upsampling by Edge-Based Demosaicing'''
# Predicting Green Pixels

for x in range(2, red.shape[0]-2,2): #Predicitng Green Pixels at Red pixel positions
	for y in range(2, red.shape[1]-2,2):#Starting from (2,2) so as to avoid corners
			dH= red[x,y-2]+red[x,y+2]/2-red[x,y]
			dV= (red[x-2,y]+red[x+2,y])/2-red[x,y]
			if (dH<dV):
				green[x,y]= (green[x,y-1]+green[x,y+1])/2
			elif (dH>dV) :
				green[x,y]= (green[x-1,y]+green[x+1,y])/2
			else :
				green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4


for x in range(3, blue.shape[0]-3,2): #Predicitng Green Pixels at Blue pixel positions
	for y in range(3, blue.shape[1]-3,2): #Starting from (3,3) so as to avoid corners
		dH= (blue[x,y-2]+blue[x,y+2])/2-blue[x,y]
		dV= (blue[x-2,y]+blue[x+2,y])/2-blue[x,y]
		if (dH<dV):
			green[x,y]= (green[x,y-1]+green[x,y+1])/2
		elif (dH>dV) :
			green[x,y]= (green[x-1,y]+green[x+1,y])/2
		else :
			green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4
#### Algorithm to predict Green Pixels at corners and at pixel positions not taken into account above ##########
for x in range(1, 2):
	for y in range(1, blue.shape[1]-1,2):
		green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4

for x in range(2, red.shape[0]-2, 2):
	for y in range(red.shape[1]-2,red.shape[1]-1):
		green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4

for x in range(red.shape[0]-2, red.shape[0]-1):
	for y in range(2,red.shape[1]-1,2):
		green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4

for x in range(1, blue.shape[0]-1,2):
	for y in range(blue.shape[1]-1,blue.shape[1]):
		green[x,y]=(green[x,y-1]+green[x-1,y]+green[x+1,y])/4

for x in range(blue.shape[0]-1, blue.shape[0]):
	for y in range(1,blue.shape[1]-1,2):
		green[x,y]=(green[x,y-1]+green[x-1,y])/4

for x in range(1,blue.shape[0]-1,2):
	for y in range(1,2):
		green[x,y]=(green[x,y-1]+green[x,y+1]+green[x-1,y]+green[x+1,y])/4

for x in range(0, 1):
	for y in range(2, red.shape[1]-1,2):
		green[x,y]=(green[x,y-1]+green[x,y+1])/2

for x in range(0, blue.shape[0],2):
	for y in range(0,1):
		green[x,y]=(green[x,y+1])/2

# Predicting Red Pixels by Bilinear Interpolation

for x in range(0, red.shape[0],2):
	for y in range(1, red.shape[1]-1,2):
		red[x,y]= (red[x,y-1]+red[x,y+1])/2


for x in range(1, red.shape[0]-1,2):
	for y in range(0, red.shape[1],2):
		red[x,y]=(red[x-1,y]+red[x+1,y])/2


for x in range(1, red.shape[0]-1,2):
	for y in range(1, red.shape[1]-1,2):
		red[x,y]=(red[x-1,y]+red[x-1,y+1]+red[x+1,y-1]+red[x+1,y+1])/4

for x in range(red.shape[0]-1, red.shape[0]):
	for y in range(0, red.shape[1],1):
		red[x,y]=(red[x-1,y])/2

#for x in range(0, red.shape[0]-1):
#	for y in range(4310, red.shape[1],1):
#		red[x,y]=525


# Predicting Blue Pixels by Bilinear Interpolation

for x in range(1, blue.shape[0]-1,2):
	for y in range(2, blue.shape[1]-2,2):
		blue[x,y]= (blue[x,y-1]+blue[x,y+1])/2


for x in range(2, blue.shape[0]-2,2):
	for y in range(1, blue.shape[1]-1,2):
		blue[x,y]=(blue[x-1,y]+blue[x+1,y])/2

for x in range(2, blue.shape[0]-2,2):
	for y in range(2, blue.shape[1]-2,2):
		blue[x,y]=(blue[x,y-1]+blue[x,y+1]+blue[x-1,y]+blue[x+1,y])/4

for x in range(1, blue.shape[0],1):
	for y in range(0, blue.shape[1]-2,blue.shape[1]):
		blue[x,y]=(blue[x,y+1])/2

for x in range(1, blue.shape[0],1):
	for y in range(blue.shape[1]-1, blue.shape[1]):
		blue[x,y]=(blue[x,y-1])/2

for x in range(0, blue.shape[0],blue.shape[0]):
	for y in range(0, blue.shape[1]):
		blue[x,y]=(blue[x+1,y])/2

for x in range(blue.shape[0]-2, blue.shape[0],blue.shape[0]):
	for y in range(0, blue.shape[1]):
		blue[x,y]=(blue[x+1,y]+blue[x-1,y])/2

for x in range(blue.shape[0]-1, blue.shape[0],blue.shape[0]):
	for y in range(2, blue.shape[1]-2):
		blue[x,y]=(blue[x-1,y])/2


edge_interpolation = np.zeros((2868,4320,3), 'uint8')#Stacking the Red, Green and Blue Matrices into a Matrix 
edge_interpolation[..., 0] = red 
edge_interpolation[..., 1] = green
edge_interpolation[..., 2] = blue
img3 = Image.fromarray(edge_interpolation)
img3.save('Edge_Interpolation.jpeg')
plt.imshow(edge_interpolation.astype('uint8'))
plt.show()
'''
plt.subplot(131), plt.imshow(up_NN.astype('uint8'))
plt.title('Nearest Neighbour '), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(up_BL.astype('uint8'))
plt.title('Bilinear Interpolation '), plt.xticks([]), plt.yticks([])
plt.subplot(333), plt.imshow(edge_interpolation.astype('uint8'))
plt.title('Edge-Based'), plt.xticks([]), plt.yticks([])
plt.show()


crop_img1 = up_NN[3000:4000, 0:1000]
plt.imshow(crop_img1.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img2 = up_BL[3000:4000, 0:1000]
plt.imshow(crop_img2.astype('uint8'))
plt.title('Bilinear Interpolation'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img3 = edge_interpolation[3000:4000, 0:1000]
plt.imshow(crop_img3.astype('uint8'))
plt.title('Edge-Base'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img11 = up_NN[3000:4000, 2000:]
plt.imshow(crop_img11.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img12 = up_BL[3000:4000, 2000:]
plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(crop_img13.astype('uint8'))
plt.show()

crop_img13 = edge_interpolation[3000:4000, 2000:]
plt.imshow(crop_img13.astype('uint8'))
plt.title('Edge-Based'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img21 = up_NN[2500:3500, 1500:2500]
plt.imshow(crop_img21.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img22 = up_BL[2500:3500, 1500:2500]
plt.imshow(crop_img22.astype('uint8'))
plt.title('Bilinear Interpolation'), plt.xticks([]), plt.yticks([])
plt.show()

crop_img23 = edge_interpolation[2500:3500, 1500:2500]
plt.imshow(crop_img23.astype('uint8'))
plt.title('Edge-Based'), plt.xticks([]), plt.yticks([])
plt.show()


plt.subplot(131), plt.imshow(crop_img1.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(crop_img2.astype('uint8'))
plt.title('Bilinear Interpolation'), plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(crop_img3.astype('uint8'))
plt.title('Edge-Base'), plt.xticks([]), plt.yticks([])
plt.show()
plt.subplot(131), plt.imshow(crop_img11.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(crop_img12.astype('uint8'))
plt.title('Bilinear Interpolation'), plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(crop_img13.astype('uint8'))
plt.title('Edge-Based'), plt.xticks([]), plt.yticks([])
plt.show()
plt.subplot(131), plt.imshow(crop_img21.astype('uint8'))
plt.title('Nearest Neighbour'), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(crop_img22.astype('uint8'))
plt.title('Bilinear Interpolation'), plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(crop_img23.astype('uint8'))
plt.title('Edge-Based'), plt.xticks([]), plt.yticks([])
plt.show()

'''




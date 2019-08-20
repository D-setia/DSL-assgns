#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rgbPixelValues[1268][953][3]; //! 3-D array to store RGB intensity values for each pixel


int red = 0;
int blue = 1;
int green = 2;

/*!
This function remomes all shades of the color specified
@param color 	the color whose shades are to be removed
@return ---
 */
void removeAllShades(int color){
	for(int i = 0; i < 1268; i++){
		for(int j = 0; j < 953; j++){
			if((rgbPixelValues[i][j][color] > rgbPixelValues[i][j][(color+1)%3])
							&&
			  (rgbPixelValues[i][j][color] > rgbPixelValues[i][j][(color+2)%3])){
				rgbPixelValues[i][j][color] = 0;
			}

		}

	}
}

/*!
This function keeps the shades of only the color specified
@param color 	the color whose shades are to be removed
@return ---
 */
void keepOnly(int color){
	for(int i = 0; i < 1268; i++){
		for(int j = 0; j < 953; j++){
			if((rgbPixelValues[i][j][(color+1)%3] > rgbPixelValues[i][j][(color+2)%3])
							&&
			  (rgbPixelValues[i][j][(color+1)%3] > rgbPixelValues[i][j][color])){
				rgbPixelValues[i][j][(color+1)%3] = 0;
			}else if((rgbPixelValues[i][j][(color+2)%3] > rgbPixelValues[i][j][(color+1)%3])
								   &&
				(rgbPixelValues[i][j][(color+2)%3] > rgbPixelValues[i][j][color])){
					rgbPixelValues[i][j][(color+2)%3] = 0;
			}
		}
	}
}

/*!
This function prints RGB intensity values for a given pixel position
@param x 	x coordinate of pixel
@param y 	y coordinate of pixel
@return ---
 */
void pixelValue(int x, int y){
	printf("Red: %d\n",rgbPixelValues[x][y][0]);
	printf("Blue: %d\n",rgbPixelValues[x][y][1]);
	printf("Green: %d\n\n",rgbPixelValues[x][y][2]);
}

int main(){
	
	int value =0;
	int counter = 0;
	
	FILE* redPixelValuesStream = fopen("./Q3_ip_Red.dat", "r");
	FILE* bluePixelValuesStream = fopen("./Q3_ip_Blue.dat", "r");
	FILE* greenPixelValuesStream = fopen("./Q3_ip_Green.dat", "r");
	

	while(fscanf(redPixelValuesStream, "%d,", &value) != EOF){
		rgbPixelValues[(int)counter/953][counter%953][0] = value;
		counter++;
	}
	
	counter = 0;
	while(fscanf(bluePixelValuesStream, "%d,", &value) != EOF){
		rgbPixelValues[(int)counter/953][counter%953][1] = value;
		counter++;
	}
	
	counter = 0;
	while(fscanf(greenPixelValuesStream, "%d,", &value) != EOF){
		rgbPixelValues[(int)counter/953][counter%953][2] = value;
		counter++;
	}
	
	pixelValue(21,730);
//	pixelValue(1245,497);
//	pixelValue(907,43);

//	removeAllShades(green);
	keepOnly(green);	
	pixelValue(21,730);
//	pixelValue(1245,497);
//	pixelValue(907,43);	
	return 0;
}

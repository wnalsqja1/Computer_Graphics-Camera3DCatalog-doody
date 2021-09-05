#include <stdio.h>
#include <stdlib.h>

#include "bmpfuncs.h"



void storeImage(float *imageOut, const char *filename, int rows, int cols, 
                const char* refFilename) {

   FILE *ifp, *ofp;
   unsigned char tmp;
   int offset;
   unsigned char *buffer;
   int i, j;

   int bytes;

   int height, width;

   ifp = fopen(refFilename, "rb");
   if(ifp == NULL) {
      perror(filename);
      exit(-1);
   }

   fseek(ifp, 10, SEEK_SET);
   fread(&offset, 4, 1, ifp);

   fseek(ifp, 18, SEEK_SET);
   fread(&width, 4, 1, ifp);
   fread(&height, 4, 1, ifp);

   fseek(ifp, 0, SEEK_SET);

   buffer = (unsigned char *)malloc(offset);
   if(buffer == NULL) {
      perror("malloc");
      exit(-1);
   }

   fread(buffer, 1, offset, ifp);

   printf("Writing output image to %s\n", filename);
   ofp = fopen(filename, "wb");
   if(ofp == NULL) {
      perror("opening output file");
      exit(-1);
   }
   bytes = fwrite(buffer, 1, offset, ofp);
   if(bytes != offset) {
      printf("error writing header!\n");
      exit(-1);
   }

   // NOTE bmp formats store data in reverse raster order (see comment in
   // readImage function), so we need to flip it upside down here.  
   int mod = width % 4;
   if(mod != 0) {
      mod = 4 - mod;
   }
   //   printf("mod = %d\n", mod);
   for(i = height-1; i >= 0; i--) {
      for(j = 0; j < width; j++) {
         tmp = (unsigned char)imageOut[i*cols+j];
         fwrite(&tmp, sizeof(char), 1, ofp);
      }
      // In bmp format, rows must be a multiple of 4-bytes.  
      // So if we're not at a multiple of 4, add junk padding.
      for(j = 0; j < mod; j++) {
         fwrite(&tmp, sizeof(char), 1, ofp);
      }
   } 

   fclose(ofp);
   fclose(ifp);

   free(buffer);
}

/*
 * Read bmp image and convert to byte array. Also output the width and height
 */
uchar* readImageData(const char *filename, int* width, int* height, int* channels)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	int dataPos;     // Position in the file where the actual data begins
	int imageSize;   // = width*height*3 or width*height
	// Actual RGB data
	uchar* imageData;

	// Open the file
	FILE * file = fopen(filename, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// ����Ʈ �迭���� int ������ �н��ϴ�. 
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	*width = *(int*)&(header[0x12]);
	*height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = (*width) * (*height) * 3; // Assume 3 channels
	else {
		if (imageSize == (*width) * (*height)) {
			//printf("input source : 8bit-img\n");
			*channels = 1;
		}
		else if (imageSize == (*width) * (*height) * 3) {
			//printf("input source : 24bit-img\n");
			*channels = 3;
		}
		else {
			channels = 0;
		}
	}
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	//printf("width = %d\n", *width);
	//printf("height = %d\n", *height);
	//printf("imgSize = %d\n", imageSize);

	imageData = (uchar*)malloc(imageSize);

	fread(imageData, 1, imageSize, file);
	fclose(file);

	// flip R & B // BGR order -> RGB order
	if (*channels == 3) {
		for (int i = 0; i < (*height); i++)
		{
			for (int j = 0; j < (*width); j++)
			{
				uchar tmp = imageData[3 * (i * (*width) + j)]; // R
				imageData[3 * (i * (*width) + j)] = imageData[3 * (i * (*width) + j) + 2];
				imageData[3 * (i * (*width) + j) + 2] = tmp;
			}
		}
	}

	return imageData;
}

// float version
float* readImageDataf(const char *filename, int* width, int* height, int* channels) {

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	int dataPos;     // Position in the file where the actual data begins
	int imageSize;   // = width*height*3 or width*height
	// Actual RGB data
	uchar* imageData;

	// Open the file
	FILE * file = fopen(filename, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// ����Ʈ �迭���� int ������ �н��ϴ�. 
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	*width = *(int*)&(header[0x12]);
	*height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = (*width) * (*height) * 3; // Assume 3 channels
	else {
		if (imageSize == (*width) * (*height)) {
			//printf("input source : 8bit-img\n");
			*channels = 1;
		}
		else if (imageSize == (*width) * (*height) * 3) {
			//printf("input source : 24bit-img\n");
			*channels = 3;
		}
		else {
			channels = 0;
		}
	}
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	//printf("width = %d\n", *width);
	//printf("height = %d\n", *height);
	//printf("imgSize = %d\n", imageSize);

	imageData = (uchar*)malloc(imageSize);

	fread(imageData, 1, imageSize, file);
	fclose(file);

	// flip R & B // BGR order -> RGB order
	if (*channels == 3) {
		for (int i = 0; i < (*height); i++)
		{
			for (int j = 0; j < (*width); j++)
			{
				uchar tmp = imageData[3 * (i * (*width) + j)]; // R
				imageData[3 * (i * (*width) + j)] = imageData[3 * (i * (*width) + j) + 2];
				imageData[3 * (i * (*width) + j) + 2] = tmp;
			}
		}
	}

   // Input image on the host
   float* floatImage = NULL;
   floatImage = (float*)malloc(sizeof(float)*imageSize);

   // Convert the BMP image to float (not required)
   for(int i = 0; i < *height; i++) {
      for(int j = 0; j < *width; j++) {
		  for(int c=0; c< *channels; c++)
			floatImage[((*channels)*i*(*width)+j)+c] = (float)imageData[((*channels) * i*(*width) + j) + c];
      }
   }

   free(imageData);
   return floatImage;
}

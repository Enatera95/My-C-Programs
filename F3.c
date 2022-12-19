#include<stdio.h>
#include<String.h>
#include<stdint.h>
#include<math.h>

struct bmp_sign
{
	char signature[2];
} bsign;
	
struct bmp_header
{
	int file_size;
	int reserved;
	int doffset;
} bmhead;
	
struct info1
{
	int info_header_size;
	int width;
	int height;	
} i;

struct info2
{
	short int planes;
	short int bpp;	
} i2;

struct info3
{
	int compression;
	int image_size;
	int xPixpM;
	int yPixpM;
	int colUsed;
	int impCol;
} i3;

struct pixel
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} whitep, blackp;

struct padding
{
	uint8_t z1;
} pad;


void generateSqBitmap(int s)
{
	int m = s%2;
	
	FILE * fp = fopen("ArrayInText.bmp", "wb");
	
	i2.bpp = 24;
	bmhead.doffset = 54;
	
	i.width = s;
	i.height = s;
	int rowSize = floor((i2.bpp*i.width+31)/32)*4;
	
	i3.image_size = rowSize*i.height;
	bmhead.file_size = i3.image_size + bmhead.doffset;
	
	int colourTableRowSize = 3*i.width;
	
	int padcount = rowSize - colourTableRowSize;
	
	//Initialization of struct members.
	strcpy(bsign.signature, "BM");
	
	bmhead.reserved = 0;
	
	i.info_header_size = 40;
	
	i2.planes = 1;
	
	i3.compression = 0;
	i3.xPixpM = 197;
	i3.yPixpM = 197;
	i3.colUsed = 0;
	i3.impCol = 0;
	
	printf("Rowsize: %d bytes\n", rowSize);
	printf("Image_Size: %d bytes\n", i3.image_size);
	printf("File_Size: %d bytes\n", bmhead.file_size);
	
	//Pixel colour setting.
	whitep.blue = 255;
	whitep.green = 255;
	whitep.red = 255;
	
	blackp.blue = 0;
	blackp.green = 0;
	blackp.red = 0;
	
	//Padding
	pad.z1 = 0;
		
	int stopl, it, j;
	
	if(m == 1)
	{	
		stopl = (i.width - 1)/2;
		
		//writing bitmap meta data to file
		fwrite(&bsign, sizeof(bsign), 1, fp);
	
		fwrite(&bmhead, sizeof(bmhead), 1, fp);
	
		fwrite(&i, sizeof(i), 1, fp);
	
		fwrite(&i2, sizeof(i2), 1, fp);
	
		fwrite(&i3, sizeof(i3), 1, fp);
	
		//Writing of Colour Table and padding here
		for(j = 0; j < ((i.height-1)/2); j++)
		{
			//First row
			//pixels (it < stopl)
			for(it = 0; it < stopl; it++)
			{
				fwrite(&whitep, sizeof(whitep), 1, fp);
				fwrite(&blackp, sizeof(blackp), 1, fp);
			}
			fwrite(&whitep, sizeof(whitep), 1, fp);
	
		//padcount (it < padcount)
		for(it = 0; it < padcount; it++)
		{
			fwrite(&pad, sizeof(pad), 1, fp);
		}
	
		//Second row
		for(it = 0; it < stopl; it++)
		{
			fwrite(&blackp, sizeof(blackp), 1, fp);
			fwrite(&whitep, sizeof(whitep), 1, fp);
		}
		fwrite(&blackp, sizeof(blackp), 1, fp);
	
		//padcount (it < padcount)
		for(it = 0; it < padcount; it++)
		{
			fwrite(&pad, sizeof(pad), 1, fp);
		}
	}
	
	for(it = 0; it < stopl; it++)
	{
		fwrite(&whitep, sizeof(whitep), 1, fp);
		fwrite(&blackp, sizeof(blackp), 1, fp);
	}
	fwrite(&whitep, sizeof(whitep), 1, fp);
	
		//padcount (i < padcount)
		for(it = 0; it < padcount; it++)
		{
			fwrite(&pad, sizeof(pad), 1, fp);
		}
	
	}
	
	if(m == 0)
	{	
		//Writing header to file.
		fwrite(&bsign, sizeof(bsign), 1, fp);
	
		fwrite(&bmhead, sizeof(bmhead), 1, fp);
	
		fwrite(&i, sizeof(i), 1, fp);
	
		fwrite(&i2, sizeof(i2), 1, fp);	
	
		fwrite(&i3, sizeof(i3), 1, fp);
	
		//Writing colour table to file.
		
		//first row
		stopl = i.width/2;
		
		for(j = 0; j < (i.height/2); j++)
		{

			for(it = 0; it < stopl; it++)
			{
				fwrite(&whitep, sizeof(whitep), 1, fp);
				fwrite(&blackp, sizeof(blackp), 1, fp);	
			}
			for(it = 0;it < padcount; it++)
			{
				fwrite(&pad, sizeof(pad), 1, fp);	
			}
		
			//second row
			for(it = 0; it < stopl; it++)
			{
				fwrite(&blackp, sizeof(blackp), 1, fp);	
				fwrite(&whitep, sizeof(whitep), 1, fp);
			}
			for(it = 0;it < padcount; it++)
			{
				fwrite(&pad, sizeof(pad), 1, fp);	
			}
		}
	
	}
	fclose(fp);			
}


int main()
{
	//The computer is being told to write a 4000px by 4000px bitmap file.
	generateSqBitmap(4000);
	return 0;
}

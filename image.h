#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
 
struct Dim{
        GLint x, y;
};
 
struct RGBA{
        GLubyte r, g, b, a;
};
 
struct Image{
        struct Dim dim;
        struct RGBA *img;
};
 
struct Image load_img(char *name){
        struct Image image;
        RGBQUAD pixels; 
        GLint cnt=0,x,y;
 
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(name,0);
        FIBITMAP *loadimagem = FreeImage_Load(format,name,0);
 
        if(loadimagem == NULL){
                printf("Falha ao carregar a imagem: %s\n",name);
                exit(0);
        }
 
        image.dim.x = FreeImage_GetWidth(loadimagem);
        image.dim.y = FreeImage_GetHeight(loadimagem);
        image.img =(RGBA*)malloc((image.dim.x*image.dim.y)*sizeof(RGBA));
 
        for(x = 0; x < image.dim.y; x++){
                for(y = 0; y < image.dim.x; y++){
                        FreeImage_GetPixelColor(loadimagem, y, x, &pixels);
                        image.img[cnt].r = pixels.rgbRed;
                        image.img[cnt].g = pixels.rgbGreen;
                        image.img[cnt].b = pixels.rgbBlue;
                        image.img[cnt++].a = pixels.rgbReserved;
                }
        } 
        FreeImage_Unload(loadimagem); 
        return image;
}

#endif

#include "libfreetype.h"

#include <iostream>
#include <QImage>
#include <stdio.h>

int main()
{
    std::string fuck = "auck";
    unsigned long aaa[4];
    for(int i = 0;i<fuck.length();i++)
    {
        aaa[i] = (unsigned long)fuck[i];
    }
    unsigned int x = 0 ,y = 0;
    unsigned int w=0,h=0;
    unsigned int size = 60;
    FreetypeHadle * hadle = initFreetype("/home/hai/tmp/freetype1/simhei.ttf",size);

    QImage img2(640,480,QImage::Format_RGBA8888);
    for(int i = 0 ; i<fuck.length();i++)
    {
        if(char2ftbitmap(fuck[i],hadle,&w,&h) == -1)
        {
            return -1;
        }
        y = size - h;
        draw_rgba(hadle,x,y,
                   (unsigned char*)img2.bits(),img2.width(),img2.height(),0xFF303099);
        x+=w+6;
    }
    img2.save("bbb.bmp");



    QImage img3(640,480,QImage::Format_RGBA8888);
    img3.fill(QColor(255, 255, 255, 255));
    str2rgba(hadle,aaa,4,
                60,0,0,
               (unsigned char*)img3.bits(),img3.width(),img3.height(),0xFF303099);
    img3.save("ccc.bmp");




    closeFreetype(hadle);
}

#include "libfreetype.h"

#include <iostream>
#include <QImage>
#include <stdio.h>

int main()
{
    wchar_t aaa[] = L"a你 好世界哈哈a";
    unsigned int x = 0 ,y = 0;
    unsigned int w=0,h=0;
    unsigned int size = 60;
    //指定合适的ttf文件即可
    FreetypeHandle * handle = initFreetype("/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",size);

    QImage img2(640,480,QImage::Format_RGBA8888);
    for(unsigned int i = 0 ; i<sizeof(aaa)/4;i++)
    {
        if(aaa[i] == L' ')
        {
            w= size/2;
        }
        else
        {
            if(char2ftbitmap(aaa[i],handle,&w,&h) == -1)
            {
                return -1;
            }
            y = size - h;
            draw_rgba(handle,x,y,
                       (unsigned char*)img2.bits(),img2.width(),img2.height(),0xFF303099);
        }
        x+=w+6;
    }
    img2.save("bbb.bmp");



    QImage img3(640,480,QImage::Format_RGBA8888);
    img3.fill(QColor(255, 255, 255, 255));
    str2rgba(handle,aaa,sizeof(aaa)/4,
                0,0,
               (unsigned char*)img3.bits(),img3.width(),img3.height(),0xFF303099);

    drawRectangle((unsigned char*)img3.bits(),img3.width(),img3.height(),
                  160,120,480,360,0xFF303099);

    img3.save("ccc.bmp");




    closeFreetype(handle);
}
using namespace std;
int main1(int argc, char *argv[])
{

    int a = 0;
    int b = 0;
    int const c = 0;
    int d = 0;
    printf("%p-%p-%p-%p\n",&a,&b,&c,&d);

    int *p = (int*)&c;
    *p = 100;
    printf("%d\n",c);

    return 0;
}


#include <stdlib.h>
#include <ft2build.h>
#include <memory.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

#include "libfreetype.h"
typedef struct FreetypeHadle_
{
    FT_Bitmap   *bitmap;
    FT_Library  ft2_library;
    FT_Face		ft2_face;
    unsigned int size;
}FreetypeHadle;

void draw_bitmap( const FreetypeHadle *hadle,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,const char byte)
{
    FT_Bitmap* bitmap= &hadle->ft2_face->glyph->bitmap;
    signed int  i, j, p, q;
    signed int  x_max = x + bitmap->width;
    signed int  y_max = y + bitmap->rows;


    for ( i = x, p = 0; i < x_max; i++, p++ )
    {
        for ( j = y, q = 0; j < y_max; j++, q++ )
        {
            if ( i < 0 || j < 0 || i >= buf_width || j >= buf_height )
                continue;
            //原算法
            //*(buf+j*buf_width+i) |= bitmap->buffer[q * bitmap->width + p];
            //改动后 对不是黑色区域（也就是字形）赋值成白色，非字形位置不动
            if(bitmap->buffer[q * bitmap->width + p] != 0x00)
            {
                *(buf+j*buf_width+i) = byte;
            }
        }
    }
}
void draw_rgba( const FreetypeHadle *hadle,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,signed int rgba)
{
    FT_Bitmap* bitmap= &hadle->ft2_face->glyph->bitmap;
    signed int  i, j, p, q;
    signed int  x_max = x + bitmap->width;
    signed int  y_max = y + bitmap->rows;
    signed int* buf_tmp =(signed int*)buf ;


    for ( i = x, p = 0; i < x_max; i++, p++ )
    {
        for ( j = y, q = 0; j < y_max; j++, q++ )
        {
            if ( i < 0 || j < 0 || i >= buf_width || j >= buf_height )
                continue;
            //原算法
            //*(buf+j*buf_width+i) |= bitmap->buffer[q * bitmap->width + p];
            //改动后 对不是黑色区域（也就是字形）赋值成rgba，非字形位置不动
            if(bitmap->buffer[q * bitmap->width + p] != 0x00)
            {
                *(buf_tmp + j*buf_width+i) = rgba;
            }
        }
    }
}

int char2ftbitmap(wchar_t ch,const FreetypeHadle *hadle,unsigned int *width,unsigned int *height)
{
    if(FT_Load_Glyph( hadle->ft2_face, FT_Get_Char_Index(hadle->ft2_face, ch), FT_LOAD_NO_BITMAP | FT_LOAD_DEFAULT ) &&
                FT_Load_Glyph( hadle->ft2_face, FT_Get_Char_Index(hadle->ft2_face, ch), FT_LOAD_DEFAULT ))
    {
        return -1;
    }
    //	FT_Load_Char(ft2_face, ucode, FT_LOAD_DEFAULT );

    if(FT_Render_Glyph( hadle->ft2_face->glyph, FT_RENDER_MODE_NORMAL))
    {
        return -1;
    }
    if(width != NULL)
    {
        *width = hadle->ft2_face->glyph->bitmap.width;
    }
    if(height != NULL)
    {
        *height = hadle->ft2_face->glyph->bitmap_top;
    }
    return 0;
}
FreetypeHadle *initFreetype(const char *ttf_path, unsigned int size)
{
    FreetypeHadle *hadle =(FreetypeHadle *)malloc(sizeof(FreetypeHadle)) ;
    FT_Error	err;
    /* Init freetype library */
    err = FT_Init_FreeType(&hadle->ft2_library);
    if (err != FT_Err_Ok)
    {
        return NULL;
    }
    err = FT_New_Face( hadle->ft2_library, ttf_path, 0, &hadle->ft2_face );
    if (err != FT_Err_Ok)
    {
        return NULL;
    }
    err = FT_Set_Pixel_Sizes( hadle->ft2_face, 0, size);
    if (err != FT_Err_Ok)
    {
        return NULL;
    }
    FT_Select_Charmap( hadle->ft2_face, FT_ENCODING_UNICODE);

    return hadle;
}
void closeFreetype(FreetypeHadle *hadle)
{
    if(hadle != NULL)
    {
        FT_Done_Face( hadle->ft2_face );
        FT_Done_FreeType( hadle->ft2_library );
        free(hadle);
    }
}
int str2rgba(const FreetypeHadle *hadle, wchar_t *str,int len,
              signed int x, signed int y,
              unsigned char* buf, signed int buf_width, signed int buf_height, signed int rgba)
{
    unsigned int w = 0 ,h = 0;
    for(int i = 0 ; i<len;i++)
    {
        if(char2ftbitmap(str[i],hadle,&w,&h) == -1)
        {
            return -1;
        }
        y = hadle->size - h;
        draw_rgba(hadle,x,y,
                   buf,buf_width,buf_height,rgba);
        x+=w+6;
    }
    return 0;
}

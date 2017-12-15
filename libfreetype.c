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
}FreetypeHadle;

void draw_bitmap( FT_Bitmap*  bitmap,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,const char byte)
{
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
void draw_rgba( FT_Bitmap*  bitmap,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,signed int rgba)
{
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
            //改动后 对不是黑色区域（也就是字形）赋值成白色，非字形位置不动
            if(bitmap->buffer[q * bitmap->width + p] != 0x00)
            {
                *(buf_tmp + j*buf_width+i) = rgba;
            }
        }
    }
}

FT_Bitmap* char2bitmap(unsigned long ch,const FreetypeHadle *hadle)
{
    if(FT_Load_Glyph( hadle->ft2_face, FT_Get_Char_Index(hadle->ft2_face, ch), FT_LOAD_NO_BITMAP | FT_LOAD_DEFAULT ) &&
                FT_Load_Glyph( hadle->ft2_face, FT_Get_Char_Index(hadle->ft2_face, ch), FT_LOAD_DEFAULT ))
    {
        return NULL;
    }
    //	FT_Load_Char(ft2_face, ucode, FT_LOAD_DEFAULT );

    if(FT_Render_Glyph( hadle->ft2_face->glyph, FT_RENDER_MODE_NORMAL))
    {
        return NULL;
    }
    return &hadle->ft2_face->glyph->bitmap;
}
FreetypeHadle *InitFreetype(char *ttf_path,unsigned int size)
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
    return hadle;
}
void CloseFreetype(FreetypeHadle *hadle)
{
    if(hadle != NULL)
    {
        FT_Done_Face( hadle->ft2_face );
        FT_Done_FreeType( hadle->ft2_library );
    }
}

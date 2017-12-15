#ifndef LIBFREETYPE_H
#define LIBFREETYPE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdio.h>
typedef struct FT_Bitmap_ FT_Bitmap;
typedef struct FreetypeHadle_ FreetypeHadle;

/**
 * @brief draw_bitmap   将freetype句柄中char2bitmap转化的字符，绘制到buf图像(8位灰度图)上
 * @param hadle         一个freetype句柄
 * @param x             将FT_Bitmap绘制在buf图像的x坐标
 * @param y             将FT_Bitmap绘制在buf图像的y坐标
 * @param buf           要绘制到的图像的buf
 * @param buf_width     要绘制到的图像的宽
 * @param buf_height    要绘制到的图像的高
 * @param byte          要绘制到图像的字的颜色
 */
void draw_bitmap(const FreetypeHadle *hadle, signed int x, signed int y,
                  unsigned char* buf, signed int buf_width, signed int buf_height, const char byte);

/**
 * @brief draw_bitmap   将freetype句柄中char2bitmap转化的字符，绘制到buf图像(rgba)上
 * @param bitmap        一个freetype句柄
 * @param x             将freetype句柄中的FT_Bitmap绘制在buf图像的x坐标
 * @param y             将freetype句柄中的FT_Bitmap绘制在buf图像的y坐标
 * @param buf           要绘制到的图像的buf
 * @param buf_width     要绘制到的图像的宽
 * @param buf_height    要绘制到的图像的高
 * @param byte          要绘制到图像的字的颜色如（0xffffffff）
 */
void draw_rgba( const FreetypeHadle *hadle,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,signed int rgba);

/**
 * @brief char2bitmap   将一个字符转化成FT_Bitmap类型
 * @param ch            要转化的字符
 * @param hadle         InitFreetype返回的hadle
 * @param width         [out] 字符的实际宽度
 * @param height        [out] 字符的实际高度
 * @return              成功0,失败-1
 */
int char2ftbitmap(wchar_t ch,const FreetypeHadle *hadle,unsigned int *width,unsigned int *height);

/**
 * @brief initFreetype  初始化一个Freetype
 * @param ttf_path      ttf文件路径
 * @param size          输出字符大小，单位-像素
 * @return              成功返回一个freetype句柄，失败返回NULL
 */
FreetypeHadle *initFreetype(const char *ttf_path, unsigned int size);

/**
 * @brief closeFreetype 关闭一个Freetype
 * @param hadle
 */
void closeFreetype(FreetypeHadle *hadle);

/**
 * @brief draw_bitmap   str转化的字符，绘制到buf图像(rgba图)上
 * @param bitmap        [out] 一个FT_Bitmap结构体，里面包含一个字形buff已经，buff所构成的图像的信息
 * @param str           要转化的字符串
 * @param len           字符串长度
 * @param size          输出字符的一个字符的大小，单位-像素
 * @param x             将FT_Bitmap绘制在buf图像的x坐标
 * @param y             将FT_Bitmap绘制在buf图像的y坐标
 * @param buf           要绘制到的图像的buf
 * @param buf_width     要绘制到的图像的宽
 * @param buf_height    要绘制到的图像的高
 * @param rgba          要绘制到图像的字的颜色如（0xffffffff）
 */
int str2rgba(const FreetypeHadle *hadle, wchar_t *str,int len,
              unsigned int size,signed int x, signed int y,
              unsigned char* buf, signed int buf_width, signed int buf_height, signed int rgba);
#ifdef __cplusplus
}
#endif
#endif // LIBFREETYPE_H

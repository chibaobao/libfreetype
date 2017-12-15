#ifndef LIBFREETYPE_H
#define LIBFREETYPE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdio.h>
typedef struct FT_Bitmap_ FT_Bitmap;
/**
 * @brief draw_bitmap   将一个FT_Bitmap(一个字)，绘制到buf图像(8位灰度图)上
 * @param bitmap        [out] 一个FT_Bitmap结构体，里面包含一个字形buff已经，buff所构成的图像的信息
 * @param x             将FT_Bitmap绘制在buf图像的x坐标
 * @param y             将FT_Bitmap绘制在buf图像的y坐标
 * @param buf           要绘制到的图像的buf
 * @param buf_width     要绘制到的图像的宽
 * @param buf_height    要绘制到的图像的高
 * @param byte          要绘制到的图像的字的颜色
 */
void draw_bitmap(FT_Bitmap*  bitmap, signed int x, signed int y,
                  unsigned char* buf, signed int buf_width, signed int buf_height, const char byte);

/**
 * @brief draw_bitmap   将一个FT_Bitmap(一个字)，绘制到buf图像(rgba)上
 * @param bitmap        [out] 一个FT_Bitmap结构体，里面包含一个字形buff已经，buff所构成的图像的信息
 * @param x             将FT_Bitmap绘制在buf图像的x坐标
 * @param y             将FT_Bitmap绘制在buf图像的y坐标
 * @param buf           要绘制到的图像的buf
 * @param buf_width     要绘制到的图像的宽
 * @param buf_height    要绘制到的图像的高
 * @param byte          要绘制到的图像的字的颜色如（0xffffffff）
 */
void draw_rgba( FT_Bitmap*  bitmap,signed int x,signed int y,
                  unsigned char* buf,signed int buf_width,signed int buf_height,signed int rgba);

/**
 * @brief char2bitmap   将一个字符转化成FT_Bitmap类型
 * @param ch            要转化的字符
 * @param ttf_path      指定一个ttf文件路径
 * @return              转化失败返回NULL
 */
FT_Bitmap *char2bitmap(const unsigned long ch,char * ttf_path);

#ifdef __cplusplus
}
#endif
#endif // LIBFREETYPE_H

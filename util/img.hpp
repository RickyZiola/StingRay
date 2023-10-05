#ifndef IMG_HPP
#define IMG_HPP

/**
 * Save an image buffer to a file.
 * This is called internally from  RenderBuffer::save()
*/
void save_png(const char *filename, int width, int height, unsigned char *pixels);

#endif
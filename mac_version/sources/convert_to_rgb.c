#include "../include/minirt.h"

int to_byte(double x)
{
    if (x <= 0.0) return 0;
    if (x >= 1.0) return 255;
    return (int)(x * 255.999);
}

int create_rgb(int r, int g, int b) 
{
    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff); 
}

int vec_to_rgb(t_vec c) // expects 0..1
{
    return create_rgb(to_byte(c.x), to_byte(c.y), to_byte(c.z));
}

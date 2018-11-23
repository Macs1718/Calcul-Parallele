#ifndef _MANDELBULB_IMAGE_HPP_
#define _MANDELBULB_IMAGE_HPP_
#include "light.hpp"
#include <vector>

class image
{
public:
    unsigned int height, width, bytes_per_pixel;
    std::vector<unsigned char> pixel_data;

    image( unsigned int w, unsigned int h, unsigned int depth ) :
        height(h), width(w), bytes_per_pixel(depth),
        pixel_data(h*w*depth+1)
    {}
    image( const image& ) = default;
    image( image&& ) = default;
    ~image() = default;

    image& operator = ( const image& ) = default;
    image& operator = ( image&& )      = default;

    unsigned char* data() { return pixel_data.data(); }
    const unsigned char* data() const { return pixel_data.data(); }
    unsigned char* operator() ( unsigned int i, unsigned int j )
    {
        return pixel_data.data()+bytes_per_pixel*(i*width + j);
    }
    const unsigned char* operator() ( unsigned int i, unsigned int j ) const
    {
        return pixel_data.data()+bytes_per_pixel*(i*width + j);
    }

    void set_color( unsigned i, unsigned j, const color_rgb& col )
    {
        unsigned char* pt_col = (*this)(i,j);
        pt_col[0] = (unsigned char)(std::max(real_t(0),std::min(col.x,real_t(1)))*255);
        pt_col[1] = (unsigned char)(std::max(real_t(0),std::min(col.y,real_t(1)))*255);
        pt_col[2] = (unsigned char)(std::max(real_t(0),std::min(col.z,real_t(1)))*255);
    }

    color_rgb get_color( unsigned i, unsigned j ) const
    {
        const unsigned char* pt_col = (*this)(i,j);
        return {pt_col[0]/real_t(255),pt_col[1]/real_t(255),pt_col[2]/real_t(255)};
    }
};

#endif

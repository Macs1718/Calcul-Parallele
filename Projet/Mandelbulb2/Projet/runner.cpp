#include "light_dir.hpp"
#include "light_point.hpp"
#include "light_spot.hpp"
#include "scene.hpp"
#include <fstream>

void save_image( const std::string &filename, const image &img )
{
    std::ofstream ofs( filename.c_str(), std::ios::out | std::ios::binary );
    ofs << "P6\n"
        << img.width << " " << img.height << "\n255\n";
    for ( unsigned i = 0; i < img.width * img.height; ++i ) {
        ofs << img.data()[ img.bytes_per_pixel * i + 0 ] << img.data()[ img.bytes_per_pixel * i + 1 ] << img.data()[ img.bytes_per_pixel * i + 2 ];
    }
    ofs.close();
}

int main( int nargs, char *argv[] )
{
    int order = 8;
    int max_iter = 10;
    std::string output_name( "mandelbulb.ppm" );
    if ( nargs > 1 ) {
        if ( ( nargs - 1 ) % 2 != 0 ) {
            std::cout << "Usage : ./runner [--order n] [--max_iter m]" << std::endl;
            return EXIT_FAILURE;
        }
        for ( int i = 1; i < nargs; i += 2 ) {
            if ( std::string( argv[ i + 0 ] ) == "-order" )
                order = std::stoi( argv[ i + 1 ] );
            if ( std::string( argv[ i + 0 ] ) == "-max_iter" )
                max_iter = std::stoi( argv[ i + 1 ] );
            if ( std::string( argv[ i + 0 ] ) == "-output" )
                output_name = std::string( argv[ i + 1 ] );
        }
    }

    camera cam{point3d{1., +3.5, -2.2}, point3d{0., 0., 0.}};
    scene sc( cam, order, max_iter );
    sc.fractal_epsilon_alpha = 1.E-4;
    sc.fractal_max_ray_steps = 100;
    sc.add_light( light_point( point3d{0., 0., +8.}, {1., 1., 1.} ) );
    //sc.add_light(light_dir(vector3d{ 0., +4.,3.}, {1.,0.95,0.95}));
    sc.add_light( light_dir( vector3d{0., +4., 3.}, {1., 0.85, 0.85} ) );
    image img{1280, 1024, 3};
    sc.render( img );
    save_image( output_name, img );
    return 0;
}

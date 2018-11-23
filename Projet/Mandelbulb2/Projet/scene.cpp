#include "scene.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
//#define INFINITY 1e8
#endif

namespace {
    color_rgb trace( const point3d& ray_orig, const vector3d& ray_dir, const mandelbulb &obj,
                real_t alpha, real_t beta, int max_step, const scene::set_of_lights& lights )
    {
        real_t t = 0;
        real_t dist = obj.distance_estimator(ray_orig);
        int marching_iter;
        for ( marching_iter = 0; (marching_iter < max_step) and ( dist > alpha * t); ++marching_iter )
        {
            t += dist;
            if ( t > 10. ) marching_iter = max_step;
            else dist = obj.distance_estimator(ray_orig + t*ray_dir);
        }
        // si marching_iter == max_step : pas d'intersection, on retourne une couleur noire
        if ( marching_iter == max_step ) return {0,0,0};
        int stepCount = marching_iter;
        // OK, on a le point d'intersection
        auto pt_intersect = ray_orig + t*ray_dir;
        // Calcul de la normale :
        auto nrm_intersect = obj.normal_at(pt_intersect);
        // En tant qu'objet uniquement diffusif, on a qu'à calculer l'ombrage :
        color_rgb surface_color{0,0,0};
        color_rgb transmission{1,1,1};
        real_t occlusion = (1-stepCount/real_t(max_step));
        for ( auto lght : lights )
        {
            auto lght_dir = lght->direction_from(pt_intersect);
            real_t t2 = 0;
            real_t dist2 = obj.distance_estimator(pt_intersect + t2*lght_dir);
            for ( marching_iter = 0; (marching_iter < max_step) and ( dist2 > beta * t2); ++marching_iter )
            {
                t2 += dist;
                if ( t2 > 10. ) marching_iter = max_step;
                else dist2 = obj.distance_estimator(pt_intersect + t2*lght_dir);
            }
            if ( marching_iter == max_step ) // Pas de collision, donc pas d'ombre
            {
                surface_color += transmission * lght->contribution_at(pt_intersect, nrm_intersect);
                
                // Rajout de la lumière spéculative :
                // Calcul direction lumière réfléchie :
                vector3d refl_lght = 2*(nrm_intersect|lght_dir)*nrm_intersect - lght_dir;
                refl_lght.normalize();
                surface_color += pow(std::abs(refl_lght|ray_dir),90.)*lght->color;
            }
        }
        // Fausse couleur d'ambiance pour l'occlusion :
        surface_color = occlusion*surface_color;
        return surface_color;
    }
}

void scene::render(image &img) const
{
    real_t invWidth = 1. / img.width, invHeight = 1. / img.height;
    real_t aspectratio = img.width / real_t( img.height );
    real_t angle = tan( M_PI * 0.5 * objectif.fov / 180. );
    matrix44 cam2world = objectif.camera2world();
    point3d ray_origin{0, 0, 0};
    point3d ray_world = cam2world * ray_origin;
    // Trace rays
    for ( unsigned y = 0; y < img.height; ++y ) {
        for ( unsigned x = 0; x < img.width; ++x ) {
            if ( (y & 7) == 0 )
            {
                std::cout << std::setfill('0')
                          << "\rRendering row " << std::setw(4) << y << " in " << std::setw(4) << img.height 
                          << " rows and " << std::setw(4) << x << " in " << std::setw(4) << img.width << " column.";
                std::flush(std::cout);
            }
            real_t xx = ( 2 * ( ( x + 0.5 ) * invWidth ) - 1 ) * angle * aspectratio;
            real_t yy = ( 1 - 2 * ( ( y + 0.5 ) * invHeight ) ) * angle;
            point3d ray_dir_o{xx, yy, -1};
            vector3d ray_dir = ( cam2world * ray_dir_o ) - ray_world;
            ray_dir.normalize();
            auto col = trace(objectif.position, ray_dir, object, fractal_epsilon_alpha, 
                             shadow_epsilon_alpha, fractal_max_ray_steps, this->lights);
            // Attention, pour une image, l'ordonnee est inversee par rapport à la géométrie :
            img.set_color(img.height-y-1, x, col);
        }
    }
}

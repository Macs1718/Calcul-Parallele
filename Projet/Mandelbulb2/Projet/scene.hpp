#ifndef _MANDELBULB_SCENE_HPP_
#define _MANDELBULB_SCENE_HPP_
#include <vector>
#include <memory>
#include "camera.hpp"
#include "light.hpp"
#include "image.hpp"
#include "mandelbulb.hpp"

/**
 * @brief Raytrace the mandelbulb
 * @details [long description]
 * 
 * @param init_pos [description]
 * @param s [description]
 * 
 * @return [description]
 */
class scene
{
public:
    using set_of_lights = std::vector<std::shared_ptr<light>>;
    camera objectif;
    set_of_lights lights;
    mandelbulb object;
    // Nombre d'itérations maximales pour l'algorithme de ray marching.
    // Si la valeur est trop petite, seuls les détails prochent de la caméra
    // seront affichés, les détails plus éloignés ne seront pas atteints par les
    // rayons, car le nombre d'itérations maximales sera atteinte. L'impact de cette
    // valeur sur la performance est notable. Valeur par défaut : 50
    int fractal_max_ray_steps;
    // Permet de calculer le pas pour une itération de l'algorithme de ray marching :
    //   stepThreshold = fractal_epsilon_alpha * ( distance à la caméra ) ( Eq. 5.4 )
    // C'est une valeur modifiant l'apparence du fractal. Si la valeur est trop basse,
    // la fréquence d'échantillon sera trop haute et on aura des moires dûes aux
    // interférences montrant à l'écran qu'un amas de pixels colorés. Si la valeur est
    // trop haute, la fréquence sera trop basse et aucun détail ne sera visible, seulement
    // une surface lisse. Cette valeur sert en quelque sorte pour un algorithme de type
    // LoD ( Level of Details ), de grandes valeurs faisant que les frontières entre les
    // différents niveaux de détails seront visibles. Cette constante a un impact fort sur
    // la performance. Sa valeur par défaut est de 0.0001
    real_t fractal_epsilon_alpha;
    // Valeur similaire à celle d'au dessus, mais utilisé pour le calcul des ombres.
    // La valeur peut-être plus grande pour un rendu correct, mais si la valeur est trop grande,
    // tout sera oculté et dans l'ombre. Valeur par défaut : 0.05
    real_t shadow_epsilon_alpha;
    /**
     * @brief Constructeur de la scene
     * @details Constructeur de la scene demandant la position initiale de la caméra,
     *          l'ordre du mandelbulb et le nombre d'itérations maximales pour le fractal.
     * 
     * @param init_pos La position initiale de la caméra
     * @param order L'ordre du mandelbulb
     * @param max_iter Nombre d'itérations max avant de déclarer que la suite de mandelbulb converge
     *                 pour un point donné ( l'impact sur la performance est raisonnable )
     */
    scene( const camera& init_pos, unsigned order, unsigned max_iter ) : 
        objectif(init_pos), lights(),
        object(order, max_iter), fractal_max_ray_steps(50), fractal_epsilon_alpha(1.E-4), shadow_epsilon_alpha(0.05)
    {
    }
    scene( const scene& ) = default;
    scene( scene&& ) = default;
    ~scene() = default;

    scene& operator = ( const scene& ) = default;
    scene& operator = ( scene&& ) = default;

    void add_light( const light& lght ) {
        lights.push_back(lght.clone());
    }

    void render( image& img ) const;
};

#endif

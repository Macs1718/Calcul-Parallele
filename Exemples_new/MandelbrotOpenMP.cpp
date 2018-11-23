# include <atomic>
# include <iostream>
# include <thread>
# include <vector>
# include <mutex>
# include <cstdlib>
# include <string>
# include <cmath>
# include "lodepng/lodepng.h"

/** Une structure complexe est définie pour la bonne raison que la classe
 * complex proposée par g++ est très lente ! Le calcul est bien plus rapide
 * avec la petite structure donnée ci--dessous
 **/
struct Complex
{
    Complex() : real(0.), imag(0.)
    {}
    Complex(double r, double i) : real(r), imag(i)
    {}
    Complex operator + ( const Complex& z )
    {
        return Complex(real + z.real, imag + z.imag );
    }
    Complex operator * ( const Complex& z )
    {
        return Complex(real*z.real-imag*z.imag, real*z.imag+imag*z.real);
    }
    double sqNorm() { return real*real + imag*imag; }
    double real,imag;
};

/** Pour un c complexe donné, calcul le nombre d'itérations de mandelbrot
 * nécessaires pour détecter une éventuelle divergence. Si la suite
 * converge, la fonction retourne la valeur maxIter
 **/
int iterMandelbrot( int maxIter, const Complex& c)
{
    Complex z{0.,0.};
    int niter = 0;
    // On vérifie dans un premier temps si le complexe
    // n'appartient pas à une zone de convergence connue :
    // Appartenance aux disques  C0{(0,0),1/4} et C1{(-1,0),1/4}
    if ( c.real*c.real+c.imag*c.imag < 0.0625 )
        return maxIter;
    if ( (c.real+1)*(c.real+1)+c.imag*c.imag < 0.0625 )
        return maxIter;
    // Appartenance à la cardioïde {(1/4,0),1/2(1-cos(theta))}    
    if ((c.real > -0.75) && (c.real < 0.5) ) {
        Complex ct{c.real-0.25,c.imag};
        double ctnrm2 = sqrt(ct.sqNorm());
        if (ctnrm2 < 0.5*(1-ct.real/ctnrm2)) return maxIter;
    }
    while ((z.sqNorm() < 4.) && (niter < maxIter))
    {
        z = z*z + c;
        ++niter;
    }
    return niter;
}

//std::mutex iomutex;

/* Calcul la ième ligne de l'image de Mandelbrot.
 */ 
void compLineMandelbrot( unsigned W, unsigned H, int maxIter, int i, std::vector<int>& pixels  ) {
    double scaleX = 3./(W-1);
    double scaleY = 2.25/(H-1);

    for ( unsigned j = 0; j < W; ++j ) {
      Complex c{-2.0+j*scaleX,-1.125+i*scaleY};
      pixels[i*W+j] = iterMandelbrot( maxIter, c );
    }

}

/* Calcul de l'ensemble de Mandelbrot en OpenMP */
std::vector<int> compMandelbrot( int W, int H, int maxIter ) {
    std::vector<int> img(W*H);
#   pragma omp parallel for schedule(dynamic)
    for ( int i  = 0; i < H; ++i )
        compLineMandelbrot( W,H, maxIter, i, img );
  return img;
}

/** Construit et sauvegarde l'image finale **/
void savePicture( const std::string& fileName, int W, int H, const std::vector<int>& nbIters, int maxIter )
{
    std::vector<unsigned char> image(4*W*H);
    double scaleCol = 1./maxIter;//16777216
    for ( int i = 0; i < H; ++i ) {
        for ( int j = 0; j < W; ++j ) {
            double iter = scaleCol*nbIters[i*W+j];
            unsigned r = unsigned (iter*256.) & 0xFF;
            unsigned b = (unsigned (iter*65536) & 0xFF);
            unsigned g = (unsigned( iter*16777216) & 0xFF);
            image[4*(i*W+j)+0] = (unsigned char)(256-r);
            image[4*(i*W+j)+1] = (unsigned char)(256-g);
            image[4*(i*W+j)+2] = (unsigned char)(256-b);
            image[4*(i*W+j)+3] = 255;
        }
    }
    unsigned error = lodepng::encode(fileName.c_str(), image, W, H);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main()
{
    const int W = 1280;
    const int H = 1024;
    const int maxIter = 8*65536;

    auto iters = compMandelbrot( W, H, maxIter );
    savePicture("mandelbrot.png", W, H, iters, maxIter);
    return EXIT_SUCCESS;
}

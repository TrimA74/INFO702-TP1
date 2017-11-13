//
// Created by trima on 11/11/17.
//
#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"
#include <cstdlib>
#include <algorithm>

using namespace std;

int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    if ( argc < 2 )
    {
        std::cerr << "Usage: double-brightness <input.pgm> <export.pgm> <k>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();



    int k = (argc > 3) ? std::atoi( argv[ 3 ] ) : 3; // récupère le k
    int taille = (2*k+1)* (2*k+1);
    int tab[taille];
    std::cout << "taille " << taille/2;
    int w = img.w();
    int h = img.h();
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            /***
             * pour chaque pixel
             * On récup les pixels voisins qu'on met dans tab
             */
            int cpt=0;
            //if(i==20 && j==20){
            for (int x = i-k; x <= i+k; ++x) {
                for (int y = j-k; y <= j+k; ++y) {
                    if(x > 0 && y > 0 && x < h && y < w ) {
                        tab[cpt] = (int) img.at(x, y);
                        //std::cout << "val" << cpt << " " << tab[cpt] << std::endl;
                        cpt++;
                    }
                }

            }
            std::sort(tab,tab + cpt);
            /*std::cout << (int) img.at(i,j) << std::endl;
            std::cout <<"moyenne " <<  tab[5] << std::endl;*/
            img.at(i,j) = (GrayLevel) tab[taille/2];
        }
    }






    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}


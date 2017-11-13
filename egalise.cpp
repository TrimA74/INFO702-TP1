//
// Created by trima on 11/11/17.
//
#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"
#include "Histogramme.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: egalise <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    Histogramme h;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    h.init(img);
    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
        *it = h.egalisation((int)(*it));
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


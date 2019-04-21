#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
using namespace std;
// Formats d'image SVG : PovRay, SVG, PPM, x Pixmap...
// PPM possible : couleurs. ICI.
// PGM possible : gris.
const int maxHz = 17; // pixels.
const int maxVt = 12; // pixels.
const int maxRGB = 256; // each. //  65 536 max.
const int nbComposantRGB = 3;

int imageTableauRGB_int[maxHz][maxVt][nbComposantRGB];
int rgb = 1;

int pixelInit ( int x, int y, int rgb = 1 )
{
    return (maxRGB / 2); // Medium gray.
}

int pixelModif ( int x, int y, int rgb = 1 )
{

   int result = (imageTableauRGB_int[x][y][rgb] + ( rand() % maxRGB ) - ( maxRGB / 2 )); // ints tous inclus.;
result = max(result, 0);
result = min(result, maxRGB);

return result ;
}

int main()
{
    srand ( time ( NULL ) ); // No need for better init.
    if ( maxRGB >= 65536 )
        {
        cerr << "Err: maxRGB => 65 536." << endl;
        }
    else
        {

        cout << "Pseudo-random PPM image, for tests." << endl;
        cout << "Later: pseudo-random texture." << endl;
        cout << "maxHz = " << maxHz << " pixels." << endl;
        cout << "maxVt = " << maxVt << " pixels." << endl;
        cout << "maxRGB = " << maxRGB << " < 65 536 : ok." << endl;
        cout << "nbComposantRGB = " << nbComposantRGB << "." << endl;



// Create random table, (init):

        for ( int h = 0; h < maxVt; h++ )
            {
            for ( int v = 0; v < maxHz; v++ )
                {

                for ( int rgb = 1; rgb <= nbComposantRGB; rgb++ )
                    {
                    imageTableauRGB_int[h][v][rgb] = pixelInit ( h, v, rgb );
                    }
                }

            }

// Modif random table, (upgrade):

        for ( int h = 0; h < maxVt; h++ )
            {
            for ( int v = 0; v < maxHz; v++ )
                {

                for ( int rgb = 1; rgb <= nbComposantRGB; rgb++ )
                    {
                    imageTableauRGB_int[h][v][rgb] = pixelModif ( h, v, rgb );
                    }
                }

            }


        clog << "Table ok." << endl;

// Convert to file:
        string name_noext = "file";
        string name_ext = name_noext + ".ppm";
//fileappend

        // string ligne = "ok";

//  string file =  "file.txt";
        ofstream ajouteFile ( name_ext.c_str(), ios::app );
        if ( !ajouteFile )
            {
            cerr << "Impossible to open the file!" << endl;
            }
        else
            {

            ajouteFile << "P3" << endl;
            ajouteFile << maxHz << " " << maxVt << endl;
            ajouteFile << maxRGB << endl << endl;

            for ( int h = 0; h < maxVt; h++ )
                {
                for ( int v = 0; v < maxHz; v++ )
                    {
                    for ( int rgb = 1; rgb <= nbComposantRGB; rgb++ ) // iMax inclus.
                        {
                        ajouteFile << imageTableauRGB_int[h][v][rgb] << " " ;
                        }




                    ajouteFile  << endl;
                    }
                ajouteFile << endl; // Saut de ligne pour nouvelle ligne.
                }
            }
        ajouteFile.close();

        clog << "File ok." << endl;
        }
    return 0;
}

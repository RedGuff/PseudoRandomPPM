// From scratch: initial https://github.com/RedGuff/PseudoRandomPPM can NOT ask the size of the image.

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> // ?
#include <math.h>
using namespace std;
int errorfile = 0; // no error now.
bool errBadVAlue ( string texteBadValue, auto min, auto max )
{
    cerr << "Min = "  << min << endl;
    cerr << "Max = "  << max << endl;
    cerr << texteBadValue << endl;
    return false;
}

auto inputNb ( auto max = 42, auto min = 0, string texteDemande = "How many?", string texteBadValue = "A good number!" )
{
    if ( max < min ) { // Usually, the minimum is before the maximum, and sometimes it is not the default value.
        auto temp = max;
        max = min;
        min = temp;
    }
// Default texts by lgg files?

    auto a = max; // Good value.
    string tentativeString = "";
    bool inputOk  = true;
    do {
        cout << texteDemande; // << endl; // "<< endl" not obvious.
        inputOk = true; // For another time, if needed.
        try {
            getline ( cin, tentativeString ); // To avoid NaN bugs.
        } catch ( const std::invalid_argument& e ) {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
        try {
            a = stoi ( tentativeString ); // cin is bad, it's the reason of that function.
        } catch ( exception& e ) { // Over number, like: 99999999999999999999999999999999 for exemple.
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
        if ( ( a < min ) || ( a > max ) ) {
            a = max; // Good value.
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
    } while ( inputOk == false );
    return a;
}

int appendFunctionFileString(string file, string data = "")  // And create new file if does not exist. SLOW!
{
    ofstream outfile(file.c_str(), ios_base::app);
    if (!outfile) {
        cerr << "Error Opening File " << file << "!" << endl;
        return -1;
    } else {
        outfile << data; // No endl!
        outfile.close();
    }
return 0; // Ok.
}


// Possible ASCII images : SVG, PovRay, SVG, PPM, x Pixmap...
// PPM is possible : colors. here.
// PGM is possible : gray.
int displayVector3D(vector<vector<vector<int> > > &v){ // & to avoid copy.

return 0; // Ok.
}

string name() {
string file = "";
do
{
    string nameFile = "Le nom de votre fichier, avec son chemin facultatif, mais sans l'extention ? ";
    cout << nameFile ;
    getline ( cin, file );

} while (file == "");

file = file + ".ppm";
return file;
}

int main()
{
    srand ( time ( NULL ) ); // No need for better init.
    cout << "Pseudo-random PPM image, for tests." << endl;
    cout << "Later: pseudo-random texture." << endl;
    string Hz = "Horizontal size? ";
    int maxHz = inputNb(32758, 1, Hz); // PPM can do more.
    string Vz = "Vertical size? ";
    int maxVt = inputNb(32758, 1, Vz); // PPM can do more.
    int maxRGB = inputNb(65536, 1, "Nombre de valeurs par composantes ? (256 est bien !) "); // 65536 bcause of PPM.
    const int nbComposantRGB = 3; // 3 in PPM.
    int rgb = 0; // 0 = R, 1 = G, 2 = B. // Tableau en 0.
    string file = "";
    file = name();
// Init3D:
int gray = maxRGB / 2;
// https://stackoverflow.com/questions/9812411/trying-to-create-a-3-dimensional-vector-in-c
vector<vector<vector<int> > > v = vector<vector<vector<int> > >( maxHz, vector<vector<int> >(maxVt, vector<int>(3, gray)));
// Calc vector.
    for (int a=0; a<maxHz; a++)
    {
        for (int b=0; b<maxVt; b++) {
            for (rgb=0; rgb<nbComposantRGB; rgb++) { // 1 = R, 2 = G, 3 = B. // Tableau en 0.
                v[a][b][rgb] = rand() % maxRGB + 0; // ints tous inclus.;
            }

        }

    }




cout << "Image ok, now writing file." << endl;
// displayVector3D: // Chiant à faire fonctionner en fonction.
/*
    for (int a=0;a<maxHz;a++)
{
    for (int b=0;b<maxVt;b++)
    {
        for (int c=1;c<nbComposantRGB+1;c++) // 1 = R, 2 = G, 3 = B.
        {
            cout << v[a][b][c] << endl;
        }

    }
}

*/

int errorFile = 0;
recVector3DFile:
ofstream outfile(file.c_str(), ios_base::app);
    if (!outfile) {
        cerr << "Error Opening File " << file << "!" << endl;
        cout << "Try again!" << endl;
         file = name();
goto recVector3DFile;
    } else {


//errorFile +=   appendFunctionFileString(file, "P3\n");
outfile << "P3\n";

//errorFile +=   appendFunctionFileString(file, to_string(maxHz) + " " + to_string(maxVt)+ " " + to_string(maxRGB) + "\n");
outfile << to_string(maxHz) + " " + to_string(maxVt)+ " " + to_string(maxRGB) + "\n";
    for (int a=0; a<maxHz; a++)
    {
        for (int b=0; b<maxVt; b++) {
            for (int c=0; c<nbComposantRGB; c++) { // 1 = R, 2 = G, 3 = B. // Tableau en 0.
               // errorFile +=            appendFunctionFileString(file, to_string(v[a][b][c]) + " "); // Slow! Environ 100 octets par seconde !

        outfile << to_string(v[a][b][c]) + " "; // No endl!

            }
           // errorFile +=            appendFunctionFileString(file, "\n"); // Slow!

        outfile << "\n"; // No endl!

        }
      //  errorFile +=            appendFunctionFileString(file, "\n"); // Slow!
        outfile << "\n"; // No endl!
    }

if (errorFile==0)
{
    clog << "file Ok: " << file << endl;
}

        outfile.close();
    }

clog << "End!"<< endl;


//system("open picture.ppm"); // https://www.youtube.com/watch?v=fbH005SzEMc
    return 0;
}

#include "art.h"
#include "trees.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {

    Binarytree<string, TPolinom> tree;
    tree.Insert("B", TPolinom("2x2y0z0"));
    tree.Insert("A", TPolinom("3x0y1z0"));
    tree.Insert("C", TPolinom("1x1y1z0"));
    TPolinom* p = tree.Find("A");  
    tree["D"] = TPolinom(5.0);
    tree.Print();
    vector<string> keys = tree.keys();


        string vurazhenie = "x*y+z+z";
        Binarytree<string, TPolinom> peremen;

        peremen.Insert("x", TPolinom("1x1y1z0"));
        peremen.Insert("y", TPolinom("3x0y0z0"));
        peremen.Insert("z", TPolinom("9x2y1z0+2x1y1z0"));
        TPolinom resul = execute(vurazhenie, peremen);
        cout << "vurazhenieession: " << vurazhenie << endl;
        cout << "Res" << resul << endl;
        cout << "V tochke x=1, y=2, z=3: " << resul.Calculate_At(1, 2, 3) << endl;
    

    return 0;
}
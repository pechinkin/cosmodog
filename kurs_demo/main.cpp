#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "character.hpp"

int main() {
    
    Dog Barsik;
    Barsik.Dump();
    
    Barsik.AddPart();
    Barsik.Dump();
    
    Barsik.Move();
    Barsik.Dump();
    
    Barsik.Rotate(90);
    Barsik.Move();
    Barsik.Dump();

    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "character.hpp"

int main() {
    
    Dog Barsik;
    Barsik.Dump();
    
    Barsik.Move();
    Barsik.Dump();
    
    
    Barsik.MoveRotated(90);
    Barsik.Dump();
    
    Barsik.Move();
    Barsik.Dump();
    
    Barsik.MoveRotated(-90);
    Barsik.Dump();
    
    Barsik.Move();
    Barsik.Dump();
    
    Barsik.AddPart();
    Barsik.Dump();

    return 0;
}

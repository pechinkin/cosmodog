#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;
#define HEIGHT 60
#define WIDTH 60
#define DISTANCE 2
#define DELTA 0.3
#include "character.hpp"
#include "scene.hpp"

int main() {
    srand((unsigned)time(0));
    Scene MyScene;
    MyScene.Start();
    return 0;
};

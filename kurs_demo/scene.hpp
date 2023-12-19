

struct Scene {
    Dog MyDog;
    vector <Element> Asteroids, Food;
    Scene(): MyDog() {
        Food.push_back(Element(90, 50));
        Food.push_back(Element(30, 10));
        Asteroids.push_back(Element(10, 50));
    };
    void Start() {
        char c;
        MyDog.Dump();
        while (cin >> c && c != 'q')
        {
            if (c == 's') {
                MyDog.MoveRotated(90);
            } else if (c == 'd') {
                MyDog.MoveRotated(-90);
            } else {
                MyDog.Move();
            }
            
            MyDog.Dump(); //will be updated to drawing later
            
            if (MyDog.IsCollided(Food)) {
                MyDog.AddPart();
                cout << "food detected" << endl;
            } else if (MyDog.IsCollided(Asteroids)) {
                cout << "asteroid detected" << endl;
                break;
            } else if (MyDog.IsOut()) {
                cout << "out of borders" << endl;
                break;
            }
        }
    }
    
};

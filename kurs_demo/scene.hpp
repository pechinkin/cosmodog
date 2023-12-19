struct Scene {
    Dog MyDog;
    vector <Element> Asteroids, Food;
    Scene(): MyDog() {
        Food.push_back(Element(-80, 0));
        Food.push_back(Element(-120, 0));
        Asteroids.push_back(Element(-160, 0));
    };
    void Start() {
        char c;
        while (cin >> c && c != 'q')
        {
            if (c == 's') {
                MyDog.MoveRotated(90);
            } else if (c == ' ') {
                MyDog.MoveRotated(-90);
            } else {
                MyDog.Move();
            }
            MyDog.Dump();
            if (MyDog.IsCollided(Food))
            {
                MyDog.AddPart();
                cout << "food detected" << endl;
//                break;
            }
            if (MyDog.IsCollided(Asteroids))
            {
                cout << "asteroid detected" << endl;
                break;
            }
        }
    }
    
};

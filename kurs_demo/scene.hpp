struct Scene {
    Dog MyDog;
    vector <Element> Asteroids, Food;
    void AddElemTo(vector<Element> &arr) {
        int new_x = rand()%WIDTH;
        int new_y = rand()%HEIGHT;
        if (new_x % 2 != 0) --new_x;
        if (new_y % 2 != 0) --new_y;
        arr.push_back(Element(new_x, new_y));
    };
    Scene(): MyDog() {
        AddElemTo(Food);
        for (int i = 0; i < WIDTH/5; ++i) {
            AddElemTo(Asteroids);
        }
        AddElemTo(Food);
        
    };
    int arr[HEIGHT][WIDTH];
    
    void makenull() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int n = 0; n < WIDTH; ++n) {
                if (n == WIDTH - 1 || i == HEIGHT - 1) {
                    arr[i][n] = 4;
                } else {
                    arr[i][n] = 0;
                }
            }
        }
    };
    
    void print() {
        cout << "\033c";
        for (int i=0; i<HEIGHT; i++) {
            for (int n=0; n<WIDTH; n++) {
                switch (arr[i][n]) {
                    case 0:
                        cout << "  ";
                        break;
                    case 1: //for dog
                        cout << "\033[47m" << "  " << "\033[0m";
                        break;
                    case 2: //for asteroids
                        cout << "\033[41m" << "  " << "\033[0m";
                        break;
                    case 3: //for food
                        cout << "\033[42m" << "  " << "\033[0m";
                        break;
                    case 4: //for boundaries
                        cout << "\033[46m" << "  " << "\033[0m";
                        break;
                    case 5: //for head
                        cout << "\033[45m" << "  " << "\033[0m";
                        break;
                    default:
                        break;
                }
            }
            cout << endl;
        }
    };
    
    void Draw() {
        makenull();
        for (size_t i = 0; i < Asteroids.size(); ++i) {
            arr[(int)Asteroids[i].y][(int)Asteroids[i].x] = 2;
        }
        for (size_t i = 0; i < Food.size(); ++i) {
            arr[(int)Food[i].y][(int)Food[i].x] = 3;
        }
        MyDog.Dump(arr);
        print();
    };
    
//    void Start() {
//        char c;
//        Draw();
//        while (1)
//        {
//            if (cin >> c) {
//                if (c == 's') {
//                    MyDog.MoveRotated(90);
//                } else if (c == 'd') {
//                    MyDog.MoveRotated(-90);
//                } else if (c == 'q') {
//                    break;
//                } else {
//                    MyDog.Move();
//                }
//            }
//            Draw(); //will be updated to drawing later
//            
//            if (MyDog.IsCollided(Food)) {
//                MyDog.AddPart();
//                cout << "food detected" << endl;
//                AddElemTo(Food);
//            } else if (MyDog.IsCollided(Asteroids)) {
//                cout << "asteroid detected" << endl;
//                break;
//            } else if (MyDog.IsCollidedToItself()) {
//                cout << "eated itself" << endl;
//                break;
//            } else if (MyDog.IsOut()) {
//                cout << "touched border" << endl;
//                break;
//            }
//        }
//    }
    void Start() {
        char c;
        Draw();

        std::atomic<bool> running{ true };
        std::mutex mtx;

        std::thread movementThread([&]() {
            while (running) {
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    MyDog.Move(); // Move the dog every second
                    Draw(); // Redraw after movement
                    if (MyDog.IsCollided(Food)) {
                        MyDog.AddPart();
                        cout << "food detected" << endl;
                        AddElemTo(Food);
                    } else if (MyDog.IsCollided(Asteroids)) {
                        cout << "asteroid detected" << endl;
                        break;
                    } else if (MyDog.IsCollidedToItself()) {
                        cout << "eated itself" << endl;
                        break;
                    } else if (MyDog.IsOut()) {
                        cout << "touched border" << endl;
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
            }
        });

        while (running) {
            if (cin >> c) {
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (c == 'q') {
                        running = false;
                    }
//                    else if (c == 'd') {
//                        MyDog.MoveRotated(-90);
//                    } else if (c == 'q') {
//                        running = false;
//                    } 
                        MyDog.processInput(c);
                }
            }
        }

        movementThread.join(); // Wait for the movement thread to finish
    }
};

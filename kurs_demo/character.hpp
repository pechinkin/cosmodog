struct Element
{
    float x, y;
    Element(float _x, float _y): x{_x}, y{_y} {};
    void SetPos(float _x, float _y) {x = _x; y = _y;};
    void SetPos(Element another) {x = another.x; y = another.y;};
    bool operator==(const Element& other) const {
        return abs(x - other.x) < DELTA && abs(y - other.y) < DELTA;
    };
};

class Dog {
    int head_direction;
    vector <Element> parts;
    Element ProcessPointPos(Element first, Element second);
    Element RotatePoint(Element pointToRotate, Element centerPoint, float angleDegrees);
public:
    Dog();                          //+
    void MoveRotated(int degree);   //+
    void Move();                    //+
    void AddPart();                 //+
    void Draw();                //?is needed?
    void Update();              //?is needed?
    void Dump(int (&arr)[HEIGHT][WIDTH]);                    //+
    bool IsCollided(vector<Element> &arr);
    bool IsOut();
    bool IsCollidedToItself();
};

Dog::Dog() {
    head_direction = 0;
    for (int i = 0; i < 3; ++i) {
        parts.push_back(Element(WIDTH/2 + i * DISTANCE, HEIGHT/2));
    }
};

void Dog::MoveRotated(int degree) {
    head_direction += degree;
    for (size_t i = parts.size() - 1; i > 0; --i) {
        parts[i].SetPos(parts[i - 1]);
    }
    parts[0].SetPos(RotatePoint(ProcessPointPos(parts[2], parts[1]), parts[1], degree));

};

void Dog::Move() {
    for (size_t i = parts.size() - 1; i > 0; --i) {
        parts[i].SetPos(parts[i - 1]);
    }
    parts[0].SetPos(ProcessPointPos(parts[2], parts[1]));
};

void Dog::AddPart() {
    size_t last = parts.size() - 1;
    parts.push_back(ProcessPointPos(parts[last - 1], parts[last]));
};

void Dog::Dump(int (&arr)[HEIGHT][WIDTH])
{
    cout << endl;
    for (size_t i = 1; i < parts.size(); ++i) {
        arr[(int)parts[i].y][(int)parts[i].x] = 1;
    }
    arr[(int)parts[0].y][(int)parts[0].x] = 5;
};

Element Dog::ProcessPointPos(Element first, Element second) {
    float x2 = first.x, y2 = first.y;
    float x1 = second.x, y1 = second.y;
    float dx = x1 - x2;
    float dy = y1 - y2;

    // Находим длину этого вектора
    float length = sqrt(dx * dx + dy * dy);

    // Нормализуем вектор
    float normalized_dx = dx / length;
    float normalized_dy = dy / length;

    // Умножаем нормализованный вектор на DISTANCE
    float new_x = x1 + normalized_dx * DISTANCE;
    float new_y = y1 + normalized_dy * DISTANCE;
    return Element(new_x, new_y);
};

Element Dog::RotatePoint(Element pointToRotate, Element centerPoint, float angleDegrees) {
    // Настройте угол в радианах
    float angleRadians = angleDegrees * M_PI / 180.0;

    // Найдите разницу между точкой и центральной точкой
    float dx = pointToRotate.x - centerPoint.x;
    float dy = pointToRotate.y - centerPoint.y;

    // Поверните точку относительно центральной точки
    float rotatedX = centerPoint.x + dx * cos(angleRadians) - dy * sin(angleRadians);
    float rotatedY = centerPoint.y + dx * sin(angleRadians) + dy * cos(angleRadians);

    Element rotatedPoint(rotatedX, rotatedY);
    return rotatedPoint;
}

bool Dog::IsCollided(vector<Element> &arr) {
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        if (parts[0] == *it) {
            arr.erase(it); // Erase the collided element from the vector
            return true;
        }
    }
    return false;
};

bool Dog::IsOut() {
    if ((parts[0].x < 0 || parts[0].x > HEIGHT - DISTANCE - 2) || (parts[0].y < 0 || parts[0].y > WIDTH - DISTANCE - 2)) {
        return true;
    } else {
        return false;
    }
};

bool Dog::IsCollidedToItself() {
    for (size_t i = 4; i < parts.size(); ++i) {
        if (parts[0] == parts[i]) {
            return true;
        }
    }
    return false;
};

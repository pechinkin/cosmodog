#define DISTANCE 20


struct Element
{
    float x, y;
    Element(float _x, float _y): x{_x}, y{_y} {};
    void SetPos(float _x, float _y) {x = _x; y = _y;};
    void SetPos(Element another) {x = another.GetX(); y = another.GetY();};
    float GetX() {return x;};
    float GetY() {return y;};
};

class Dog {
    vector <Element> parts;
    Element ProcessPointPos(Element first, Element second);
    Element RotatePoint(Element pointToRotate, Element centerPoint, float angleDegrees);
public:
    Dog();                      //+
    void MoveRotated(int degree);    //+
    void Move();                //+
    void AddPart();             //+
    void Draw();                //-
    void Update();              //-
    void Dump();                
};

Dog::Dog() {
    for (int i = 0; i < 3; ++i) {
        parts.push_back(Element(i * DISTANCE, 0));
    }
};

void Dog::MoveRotated(int degree) {
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

void Dog::Dump()
{
    cout << endl;
    for (size_t i = 0; i < parts.size(); ++i) {
        cout << '[' << parts[i].GetX() << ';' << parts[i].GetY() << ']' << endl;
    }
};

Element Dog::ProcessPointPos(Element first, Element second) {
    float x2 = first.GetX(), y2 = first.GetY();
    float x1 = second.GetX(), y1 = second.GetY();
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
    float dx = pointToRotate.GetX() - centerPoint.GetX();
    float dy = pointToRotate.GetY() - centerPoint.GetY();

    // Поверните точку относительно центральной точки
    float rotatedX = centerPoint.GetX() + dx * cos(angleRadians) - dy * sin(angleRadians);
    float rotatedY = centerPoint.GetY() + dx * sin(angleRadians) + dy * cos(angleRadians);

    Element rotatedPoint(rotatedX, rotatedY);
    return rotatedPoint;
}

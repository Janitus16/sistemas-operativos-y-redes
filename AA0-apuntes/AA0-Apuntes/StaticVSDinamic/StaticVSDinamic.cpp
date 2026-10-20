#include <iostream>

class Fruta {
public:
    Fruta();
    ~Fruta();

    virtual void Draw() {
        std::cout << "F" << std::endl;
    }
private:

};

class Manzana : public Fruta {
public:
    Manzana();
    ~Manzana();


};

int main()
{
    
}

Manzana::Manzana()
{

}

// OOP Project.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// 1.Builder pattern (done)
// 2. Container (done)
// 3. Iterator (done)
// 4.вычисление Price(done)
#include "Builder.h"
#include "Windows.h"



; using namespace std;


int main()
{
    Director dir;
    SnowboardOrderBuilder ord_builder;
    ManualOrderBuilder builder;
    builder.createOrder();
    builder.buildSki();
    builder.buildSkiBoots();
    builder.buildSkiSticks();
    auto ord = builder.getOrder();
    container<Order> cont;
    cont.emplace_back(*builder.getOrder());
    container<ski> conts;
    cont[0].info();
    cont.emplace_back(*builder.getOrder());
    cont[1].info();
    auto it = container<Order>::Iterator(cont.begin());
    it++;
    cont[1].starttime.tm_hour -= 1;
    cout << cont[1].price();
}
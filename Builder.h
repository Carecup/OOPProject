#ifndef Builder

#define Builder
#include <iostream>
#include <vector>
#include "container.h"
#include <ctime>



class Data {
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a) {
        m_data_ = a;
    }

    int data() {
        return m_data_;
    }

private:
    int m_data_;
};


class ski {
public:
    void static info() {
        std::cout << "ski" << std::endl;
    }
    int static price() {
        return 700;
    }
};
class snowboard {
public:
    static void info() {
        std::cout << "snowboard" << std::endl;
    }

    static int price() {
        return 700;
    }
};
class snowboardBoots {
public:
    static void info() {
        std::cout << "snowboardBoots" << std::endl;
    }

    static int price() {
        return 400;
    }
};
class skiBoots {
public:
    static void info() {
        std::cout << "skiBoots" << std::endl;
    }

    static int price() {
        return 400;
    }

};
class helmet {
public:
    static void info() {
        std::cout << "helmet" << std::endl;
    }

    static int price() {
        return 400;
    }

};
class skiSticks {
public:
    static void info() {
        std::cout << "skiSticks" << std::endl;
    }

    static int price() {
        return 100;
    }

};
class Mask {
public:
    static void info() {
        std::cout << "Mask" << std::endl;
    }

    constexpr int price() {
        return 100;
    }

};
class Order {
public:
    container<ski> vsk;
    container<skiBoots> vskb;
    container<snowboard> vsn;
    container<snowboardBoots> vsnb;
    container<skiSticks> vsks;
    container<Mask> vm;
    tm starttime;
    void info() {
        int i;
        for (i = 0; i < vsk.size(); ++i)  vsk[i].info();
        for (i = 0; i < vskb.size(); ++i)  vskb[i].info();
        for (i = 0; i < vsn.size(); ++i)  vsn[i].info();
        for (i = 0; i < vsnb.size(); ++i)  vsnb[i].info();
        for (i = 0; i < vsks.size(); ++i)  vsks[i].info();
        for (i = 0; i < vm.size(); ++i)  vm[i].info();
    }
	tm getTime() {
        struct tm newtime;
        __time64_t long_time;
        char timebuf[26];
        errno_t err;
        // Get time as 64-bit integer.
        _time64(&long_time);
        // Convert to local time.
        err = _localtime64_s(&newtime, &long_time);
        return newtime;
	}
    Order()
    {
        starttime = this->getTime();
    }
    int time_passed()
    {
        int diff = (this->getTime().tm_hour * 3600 + this->getTime().tm_min * 60 + this->getTime().tm_sec) - (this->starttime.tm_hour * 3600 + this->starttime.tm_min * 60 + this->starttime.tm_sec);
        if (diff<0)
        {
            diff += 24 * 3600;
        }
        int c = diff / 3600;
        if (diff%3600 ==0)
        {
            return c;
        }
        if (diff%3600 !=0)
        {
            return (c+1);
        }
    }
    int price()
    {
        int i;
        int buf=0;
        for (i = 0; i < vsk.size(); ++i)  buf+=vsk[i].price();
        for (i = 0; i < vskb.size(); ++i)  buf+=vskb[i].price();
        for (i = 0; i < vsn.size(); ++i)  buf+=vsn[i].price();
        for (i = 0; i < vsnb.size(); ++i)  buf+=vsnb[i].price();
        for (i = 0; i < vsks.size(); ++i)  buf+=vsks[i].price();
        for (i = 0; i < vm.size(); ++i)  buf+=vm[i].price();
        return buf*this->time_passed();
    }
};

class OrderBuilder {
protected:
    Order* p;
public:
    OrderBuilder() :p(0) {}
    virtual ~OrderBuilder() {}
    virtual void createOrder() {}
    virtual void buildSki() {}
    virtual void buildSnowboard() {}
    virtual void buildSkiBoots() {}
    virtual void buildSnowboardBoots() {}
    virtual void buildSkiSticks() {}
    virtual void buildMask() {}
    virtual Order* getOrder() { return p; }
};

class ManualOrderBuilder final : public OrderBuilder {
protected:
    Order* p;
public:
    ManualOrderBuilder() :p(0) {}
    ~ManualOrderBuilder() override = default;
    void createOrder() override { p = new Order; }
    void buildSki() override { p->vsk.emplace_back(); }
    void buildSnowboard() override { p->vsn.emplace_back(); }
    void buildSkiBoots() override { p->vskb.emplace_back(); }
    void buildSnowboardBoots() override { p->vsnb.emplace_back(); }
    void buildSkiSticks() override { p->vsks.emplace_back(); }
    void buildMask() override { p->vm.emplace_back(); }
    Order* getOrder() override { return p; }
};

class SkiOrderBuilder final : public OrderBuilder {
public:
    void createOrder() override { p = new Order; }
    void buildSki() override { p->vsk.emplace_back(); }
    void buildSkiBoots() override { p->vskb.emplace_back(); }
    void buildSkiSticks() override { p->vsks.emplace_back(); }
    void buildMask() override { p->vm.emplace_back(); }
};

class SnowboardOrderBuilder final : public OrderBuilder {
public:
    void createOrder() override { p = new Order; }
    void buildSnowboard() override { p->vsn.emplace_back(); }
    void buildSnowboardBoots() override { p->vsnb.emplace_back(); }
    void buildMask() override { p->vm.emplace_back(); }
};

class Director
{
public:
    static Order* createOrder(OrderBuilder& builder)
    {
        builder.createOrder();
        builder.buildSki();
        builder.buildSkiBoots();
        builder.buildSnowboard();
        builder.buildSnowboardBoots();
        builder.buildMask();
        builder.buildSkiSticks();
        return(builder.getOrder());
    }

};


#endif
#include <iostream>
#include <memory>  // 用于智能指针
#include <string>
#include "my_print.cpp"

using namespace std;

// Computer类，包含各个部件属性
class Computer {
protected:
    string CPU;
    string GPU;
    string memory;
    string storage;
    string powerSupply;
    string type;

public:
    // 构造函数初始化所有部件
    Computer(string CPU, string GPU, string memory, string storage, string powerSupply, string type)
        : CPU(CPU), GPU(GPU), memory(memory), storage(storage), powerSupply(powerSupply), type(type) {}

    // 获取方法
    string getCPU() { return CPU; }
    string getGPU() { return GPU; }
    string getMemory() { return memory; }
    string getStorage() { return storage; }
    string getPowerSupply() { return powerSupply; }
    string getType() { return type; }
};

// ComputerBuilder基类，提供构建接口
class ComputerBuilder {
protected:
    string CPU = "Default CPU";  // 默认值
    string GPU = "Default GPU";
    string memory = "Default Memory";
    string storage = "Default Storage";
    string powerSupply = "Default Power Supply";
    string type = "Default Type";

public:
    // 创建计算机实例
    Computer createComputer() {
        return Computer(CPU, GPU, memory, storage, powerSupply, type);
    }

    // 设置各个部件的方法
    virtual ComputerBuilder& setCPU(const string& CPU) {
        this->CPU = CPU;
        return *this;
    }

    virtual ComputerBuilder& setGPU(const string& GPU) {
        this->GPU = GPU;
        return *this;
    }

    virtual ComputerBuilder& setMemory(const string& memory) {
        this->memory = memory;
        return *this;
    }

    virtual ComputerBuilder& setStorage(const string& storage) {
        this->storage = storage;
        return *this;
    }

    virtual ComputerBuilder& setPowerSupply(const string& powerSupply) {
        this->powerSupply = powerSupply;
        return *this;
    }

    // 设置计算机类型，由子类实现
    virtual ComputerBuilder& setType() {
        this->type = "Generic Computer";
        return *this;
    }
};

// GamingComputerBuilder，构建游戏型电脑
class GamingComputerBuilder : public ComputerBuilder {
public:
    ComputerBuilder& setType() override {
        this->type = "Gaming Computer";
        return *this;
    }
};

// OfficeComputerBuilder，构建办公型电脑
class OfficeComputerBuilder : public ComputerBuilder {
public:
    ComputerBuilder& setType() override {
        this->type = "Office Computer";
        return *this;
    }
};

// GraphicDesignComputerBuilder，构建图形设计型电脑
class GraphicDesignComputerBuilder : public ComputerBuilder {
public:
    ComputerBuilder& setType() override {
        this->type = "Graphic Design Computer";
        return *this;
    }
};

// ComputerDirector，负责根据不同需求生成电脑
class ComputerDirector {
public:
    // 根据类型生成电脑，使用智能指针管理对象
    Computer generateComputer(const string& type) {
        unique_ptr<ComputerBuilder> builder;

        if (type == "GamingComputer") {
            builder = make_unique<GamingComputerBuilder>();
            builder->setCPU("Intel i9")
                   .setGPU("NVIDIA RTX 3080")
                   .setMemory("32GB DDR4")
                   .setStorage("1TB SSD")
                   .setPowerSupply("750W PSU")
                   .setType();
        } else if (type == "OfficeComputer") {
            builder = make_unique<OfficeComputerBuilder>();
            builder->setCPU("Intel i5")
                   .setGPU("Integrated Graphics")
                   .setMemory("16GB DDR4")
                   .setStorage("512GB SSD")
                   .setPowerSupply("500W PSU")
                   .setType();
        } else if (type == "GraphicDesignComputer") {
            builder = make_unique<GraphicDesignComputerBuilder>();
            builder->setCPU("AMD Ryzen 7")
                   .setGPU("NVIDIA RTX 3070")
                   .setMemory("64GB DDR4")
                   .setStorage("2TB SSD")
                   .setPowerSupply("850W PSU")
                   .setType();
        } else {
            throw std::invalid_argument("Invalid computer type");
        }

        return builder->createComputer();
    }
};

// 主函数
int main() {
    ComputerDirector director;

    // 生成办公型电脑
    Computer officeComputer = director.generateComputer("OfficeComputer");
    print(officeComputer.getCPU());
    print(officeComputer.getGPU());
    print(officeComputer.getMemory());
    print(officeComputer.getStorage());
    print(officeComputer.getPowerSupply());
    print(officeComputer.getType());

    // 生成游戏型电脑
    Computer gamingComputer = director.generateComputer("GamingComputer");
    print(gamingComputer.getCPU());
    print(gamingComputer.getGPU());
    print(gamingComputer.getMemory());
    print(gamingComputer.getStorage());
    print(gamingComputer.getPowerSupply());
    print(gamingComputer.getType());
}

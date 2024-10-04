
#include <iostream>
#include <memory>
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

// ComputerBuilder类，提供构建接口
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
    ComputerBuilder& setCPU(const string& CPU) {
        this->CPU = CPU;
        return *this;
    }

    ComputerBuilder& setGPU(const string& GPU) {
        this->GPU = GPU;
        return *this;
    }

    ComputerBuilder& setMemory(const string& memory) {
        this->memory = memory;
        return *this;
    }

    ComputerBuilder& setStorage(const string& storage) {
        this->storage = storage;
        return *this;
    }

    ComputerBuilder& setPowerSupply(const string& powerSupply) {
        this->powerSupply = powerSupply;
        return *this;
    }

    // 设置计算机类型
    ComputerBuilder& setType(const string& type) {
        this->type = type;
        return *this;
    }
};

// 抽象的ComputerDirector类，定义指挥器的接口
class ComputerDirector {
public:
    virtual Computer buildComputer(ComputerBuilder& builder) = 0;
};

// GamingComputerDirector，用于构建游戏型电脑
class GamingComputerDirector : public ComputerDirector {
public:
    Computer buildComputer(ComputerBuilder& builder) override {
        return builder.setCPU("Intel i9")
                      .setGPU("NVIDIA RTX 3080")
                      .setMemory("32GB DDR4")
                      .setStorage("1TB SSD")
                      .setPowerSupply("750W PSU")
                      .setType("Gaming Computer")
                      .createComputer();
    }
};

// OfficeComputerDirector，用于构建办公型电脑
class OfficeComputerDirector : public ComputerDirector {
public:
    Computer buildComputer(ComputerBuilder& builder) override {
        return builder.setCPU("Intel i5")
                      .setGPU("Integrated Graphics")
                      .setMemory("16GB DDR4")
                      .setStorage("512GB SSD")
                      .setPowerSupply("500W PSU")
                      .setType("Office Computer")
                      .createComputer();
    }
};

// GraphicDesignComputerDirector，用于构建图形设计型电脑
class GraphicDesignComputerDirector : public ComputerDirector {
public:
    Computer buildComputer(ComputerBuilder& builder) override {
        return builder.setCPU("AMD Ryzen 7")
                      .setGPU("NVIDIA RTX 3070")
                      .setMemory("64GB DDR4")
                      .setStorage("2TB SSD")
                      .setPowerSupply("850W PSU")
                      .setType("Graphic Design Computer")
                      .createComputer();
    }
};

// 主函数
int main() {
    ComputerBuilder builder;

    // 使用GamingComputerDirector生成游戏型电脑
    GamingComputerDirector gamingDirector;
    Computer gamingComputer = gamingDirector.buildComputer(builder);
    print(gamingComputer.getCPU());
    print(gamingComputer.getGPU());
    print(gamingComputer.getMemory());
    print(gamingComputer.getStorage());
    print(gamingComputer.getPowerSupply());
    print(gamingComputer.getType());

    // 使用OfficeComputerDirector生成办公型电脑
    OfficeComputerDirector officeDirector;
    Computer officeComputer = officeDirector.buildComputer(builder);
    print(officeComputer.getCPU());
    print(officeComputer.getGPU());
    print(officeComputer.getMemory());
    print(officeComputer.getStorage());
    print(officeComputer.getPowerSupply());
    print(officeComputer.getType());
}

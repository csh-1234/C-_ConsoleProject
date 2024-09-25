#pragma once
#include "InputManager.h"
class Manager {

private:
    static InputManager inputManager; // 정적할당으로 구현
    //InputManager* inputManager; // 동적할당으로 싱글톤 구현
    Manager() 
    {
        //inputManager = new InputManager();
    }
    ~Manager() {}

    //복사생성자와 대입연산자 처리
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
public:
    static Manager& getInstance() 
    {
        static Manager instance;
        return instance;
    }

    static InputManager& getInputManager() 
    {
        return inputManager;
    }
    //InputManager* getInputManager() const 
    // {
    //     return inputManager; 
    // }
};

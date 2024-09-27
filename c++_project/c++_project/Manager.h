#pragma once
#include "InputManager.h"
#include "GameManager.h"
#include <iostream>
class Manager {
public:
    Manager() {}
    ~Manager() {}

    InputManager& input = InputManager::getInstance();
    GameManager& game = GameManager::getInstance();

    static Manager& getInstance() 
    {
        static Manager instance;
        return instance;
    }
    /*static InputManager& getInputManager() 
    {
        return inputManager;
    }*/
    //InputManager* getInputManager() const 
    //{
    //    return inputManager; 
    //}

private:
    //복사생성자와 대입연산자 처리
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
};

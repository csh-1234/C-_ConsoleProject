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
    //��������ڿ� ���Կ����� ó��
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
};

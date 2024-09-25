#pragma once
#include "InputManager.h"
class Manager {

private:
    static InputManager inputManager; // �����Ҵ����� ����
    //InputManager* inputManager; // �����Ҵ����� �̱��� ����
    Manager() 
    {
        //inputManager = new InputManager();
    }
    ~Manager() {}

    //��������ڿ� ���Կ����� ó��
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

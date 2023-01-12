#pragma once

class Scene
{
public:
    int state;
public:
    Scene() { state = 0; }
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};
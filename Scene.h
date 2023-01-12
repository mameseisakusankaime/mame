#pragma once
class Scene
{
public:
    int state;

public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};
#ifndef BULLET_H
#define BULLER_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Node2D.hpp>
#include <Area2D.hpp>
#include <Input.hpp>


namespace godot {

class Bullet : public Area2D
{
private:
    GODOT_CLASS(Bullet, Area2D)
    float speed;
    float time;
    Vector2 motion;

public:

    static void _register_methods();

    Bullet();
    ~Bullet();

    void _init();
    void _process(float delta);

    void set_speed(float p_speed);
    float get_speed();


};


}

#endif
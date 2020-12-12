#include "Bullet.h"

using namespace godot;


void Bullet::_register_methods() {
    register_method((char*)"_process", &Bullet::_process);
    register_property<Bullet, float>("speed", &Bullet::set_speed, &Bullet::get_speed, 200.0);
}

Bullet::Bullet(){

}

Bullet::~Bullet(){

}

void Bullet::_init(){
    speed = 200;
    
}

void Bullet::_process(float delta){
    

    motion = get_position();
    motion += Vector2(cos(get_rotation()), sin(get_rotation())) * speed * delta;
    set_position(motion);


   // queue_free();
    
}


void Bullet::set_speed(float p_speed){
    speed = p_speed;
}

float Bullet::get_speed(){
    return speed;
}
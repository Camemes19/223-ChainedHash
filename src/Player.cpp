#include "Player.h"

using namespace godot;

void Player::_register_methods() {
    register_method((char*)"_process", &Player::_process);
    register_method("UpdateMotionFromInput", &Player::UpdateMotionFromInput);
    register_property<Player, float>("Speed", &Player::set_speed, &Player::get_speed, 200.0);
    register_property<Player, float>("rate of fire", &Player::set_fireRate, &Player::get_fireRate, 0.1);

}

Player::Player() {
}

Player::~Player() {
    // add your cleanup here
}

void Player::_init() {

    speed = 200.0;
    reload = 0;

    MyHash.emplace("Single Shot", std::pair<int, int>(1, 0));
    MyHash.emplace("Double Shot", std::pair<int, int>(2, 5));
    MyHash.emplace("Triple Shot", std::pair<int, int>(3, 10));
    MyHash.emplace("5 Shot", std::pair<int, int>(5, 10));


    ResourceLoader* loader  = ResourceLoader::get_singleton();

    bullet_scene = loader->load("res://Bullet.tscn");
}

void Player::UpdateMotionFromInput()
{
    motion = Vector2(0, 0);
    
    Input* i = Input::get_singleton();

    if (i->is_action_pressed("Up")) 
		motion += Vector2(0, -1);
	if (i->is_action_pressed("Down")) 
		motion += Vector2(0, 1);
	if (i->is_action_pressed("Left")) 
		motion += Vector2(-1, 0);
	if (i->is_action_pressed("Right")) 
		motion += Vector2(1, 0);
    if (i->is_action_pressed("shoot"))
        shoot();
   /* if (i->is_action_pressed("pause_menu")){

        get_tree()->set_pause(true);
        get_tree("Pause_Menu")->show();
    }*/
        

}

void Player::_process(float delta) {

    look_at(get_global_mouse_position());
    UpdateMotionFromInput();
    move_and_slide(motion * speed);
    reload -= delta; 
}

void Player::shoot(){

    look_at(get_global_mouse_position());

    if(reload <= 0)
    {

        int spread = 0, alter = 0;
        int range = MyHash.at("Single Shot").second;
        
        for (int i = 0; i < MyHash.at("Single Shot").first; i++)
        {
        
            Area2D* bull = (Area2D*)bullet_scene->instance();
            get_parent()->add_child(bull);
            bull->set_transform(get_transform());
            bull->set_position(get_global_position() + Vector2(spread, 0));
            
            if(alter % 2 == 0)
                spread += range;  
            else
                spread -= range;
                
            range += range;
            ++alter;
            
        }
       

        reload = fire_rate;
    }

}

void Player::set_speed(float p_speed){
    speed = p_speed;
}

float Player::get_speed(){
    return speed;
}

void Player::set_fireRate(float rate){
    fire_rate = rate;
}

float Player::get_fireRate(){
    return fire_rate;
}




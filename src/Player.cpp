


//included header file
#include "Player.h"

//using namespace godot
using namespace godot;

//registered functions to godot
void Player::_register_methods() {
    //run process while game is running 
    register_method((char*)"_process", &Player::_process);
    //run update motion from input while game is running 
    register_method("UpdateMotionFromInput", &Player::UpdateMotionFromInput);
    //send godot the speed of the player and be able to change it in godot engine 
    register_property<Player, float>("Speed", &Player::set_speed, &Player::get_speed, 200.0);
    //send godot the rate of fire and be able to change it in the godot game engine 
    register_property<Player, float>("rate of fire", &Player::set_fireRate, &Player::get_fireRate, 0.3);
}

//constructor 
Player::Player() {
}

//destructor 
Player::~Player() {
}

//set initial values for variables in class player 
void Player::_init() {

    //set player speed to 200
    speed = 200.0;
    //reload is set to 0
    reload = 0;

    //create 4 different bullet types
    MyHash.emplace("Single Shot", std::pair<int, int>(1, 0));
    MyHash.emplace("Double Shot", std::pair<int, int>(2, 5));
    MyHash.emplace("Triple Shot", std::pair<int, int>(3, 10));
    MyHash.emplace("5 Shot", std::pair<int, int>(5, 10));

    //create a resource loader for loading in scenes from godot
    ResourceLoader* loader  = ResourceLoader::get_singleton();

    //set bullet scene to loaded in scene from godot scene files 
    bullet_scene = loader->load("res://Bullet.tscn");
}

//function to allow input to control player movement 
void Player::UpdateMotionFromInput()
{
    //motion is set to 0 initially
    motion = Vector2(0, 0);
    
    //get input from the keyboard
    Input* i = Input::get_singleton();

    //change player movement to move up if up is pressed
    if (i->is_action_pressed("Up")) 
		motion += Vector2(0, -1);
    //change player movement to move down if down is pressed
	if (i->is_action_pressed("Down")) 
		motion += Vector2(0, 1);
    //change player movement to move up if left is pressed
	if (i->is_action_pressed("Left")) 
		motion += Vector2(-1, 0);
    //change player movement to move up if right is pressed
	if (i->is_action_pressed("Right")) 
		motion += Vector2(1, 0);
    //when the shoot key is pressed(space/ left mouse) shoot function played
    if (i->is_action_pressed("shoot"))
        shoot();


}

//processes that will run while the game is running 
void Player::_process(float delta) {

    //set player to look at where the mouse is
    look_at(get_global_mouse_position());
    //update player motion according to keys being pressed
    UpdateMotionFromInput();
    //move said player on screen
    move_and_slide(motion * speed);
    //subtact delta from reload
    reload -= delta; 
}

//shoot a spawned bullet from the player
void Player::shoot(){
    
    //set player to be looking at mouse
    look_at(get_global_mouse_position());
    //TextEdit temp = get_node("TextEdit");
   
    //if reload is less than or equal to 0
    if(reload <= 0)
    {
        //set spread and chang in bullet distibution to 0
        int spread = 0, alter = 0;
        //set range of bullets to range preset of used hash key
        int range = MyHash.at("Single Shot").second;
        
        //create number of bullets specified by used hash key
        for (int i = 0; i < MyHash.at("Single Shot").first; i++)
        {
            //create an instance of a bullet at the player
            Area2D* bull = (Area2D*)bullet_scene->instance();
            //make the spawned bullet a child of player
            get_parent()->add_child(bull);
            //set transform/rotation of bullet to same as player
            bull->set_transform(get_transform());
            //set postion of bullet to player and modified if more than one bullet
            bull->set_position(get_global_position() + Vector2(spread, 0));
            
            //alter where the bullet will be placed in relation to player 
            //based on how many bullets are spawned
            if(alter % 2 == 0)
                spread += range;  
            else
                spread -= range;
            
            //increase range by range
            range += range;
            //increment alter
            ++alter;
            
        }
       
        //set reload to fire rate 
        reload = fire_rate;
    }

}

//set speed of player to input
void Player::set_speed(float p_speed){
    speed = p_speed;
}

//get speed of player and return it
float Player::get_speed(){
    return speed;
}

//set fire rate of player to input 
void Player::set_fireRate(float rate){
    fire_rate = rate;
}

//get fire rate of player and return it
float Player::get_fireRate(){
    return fire_rate;
}




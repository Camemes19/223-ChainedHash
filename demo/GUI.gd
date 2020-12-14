extends CanvasLayer


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
func _input(event):
	if event.is_action_pressed("pause_menu"):
		get_tree().paused = true
		get_node("Pause_Menu").show()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Resume_pressed():
	get_node("Pause_Menu").hide()
	get_tree().paused = false




func _on_Quite_Game_pressed():
	get_tree().quit()


func _on_Bullet_Change_pressed():
	get_node("Bullet_Menu").show()


func _on_Exit_pressed():
	get_node("Bullet_Menu").hide()
	

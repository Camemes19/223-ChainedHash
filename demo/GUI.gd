extends CanvasLayer


#open pause menu if pause_menu (esc) is pressed
func _input(event):
	if event.is_action_pressed("pause_menu"):
		#pause game
		get_tree().paused = true
		#show pause menu to user
		get_node("Pause_Menu").show()

#close pause menu when resume button is pressed 
func _on_Resume_pressed():
	#hide pause menu
	get_node("Pause_Menu").hide()
	#unpause game 
	get_tree().paused = false

#quit game if quit game is pressed
func _on_Quite_Game_pressed():
	#quit game
	get_tree().quit()

#open bullet menu when bullet button is pressed
func _on_Bullet_Change_pressed():
	#hide pause menu from user
	get_node("Pause_Menu").hide()
	#show bullet menu to user
	get_node("Bullet_Menu").show()

#exit bullet menu when exit button is pressed
func _on_Button_pressed():
	#hide bullet menu from user
	get_node("Bullet_Menu").hide()
	#show pause menu to user
	get_node("Pause_Menu").show()

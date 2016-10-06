BackgroundSprite = 0
Button1 = 10.1
Button2 = 2.2

--function next_menu()
	---- Second parameter = transition?
	--change_scene('MainGame')
--end

function push_me()
	print("push_me")
end

function init()
	Button1 = Button.new('img/mario_btn.png')
	Button2 = Button.new('img/mario_btn.png')

	Button1:set_position(10.1,100)
	Button2:set_position(100,100)

	Button1:set_action(push_me)
	Button2:set_action(push_me)
	----BackgroundSprite = sprite("test.png")
	--Button1 = button("button.png")
	----Button2 = button("button.png")

	----Button1.setPos(0, 120, 'center', 'center')
	----Button2.setPos(0, 320, 'center', 'center')

	----Button1.setAction(next_menu)
	--Button1:render()
end

function update(dt)
	Button1:update(dt)
	Button2:update(dt)
end

function render()
	--BackgroundSprite.render()
	Button1:render()
	Button2:render()
end

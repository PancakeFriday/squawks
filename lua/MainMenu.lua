BackgroundSprite = 0
Button1 = 10.1
Button2 = 2.2
Goomba = 0
questionblock = 0
questionblockT = {}
GoombaDir = -1

StartGameB = 0
SettingsB = 0
ExitB = 0

time = 0
time2 = 0
wait = false

trans = nil

function push_me()
	print("blubb")
end

function exit_action()
	trans = Transition.new("fadeOut")
	trans:set_speed(0.3)
end

function init()
	StartGameB = Button.new('img/MainMenu/StartGame.png')
	StartGameB:set_position(200,100)
	StartGameB:set_action(push_me)

	SettingsB = Button.new('img/MainMenu/Settings.png')
	SettingsB:set_position(200,200)
	SettingsB:set_action(push_me)

	ExitB = Button.new('img/MainMenu/Exit.png')
	ExitB:set_position(200,300)
	ExitB:set_action(exit_action)

	BackgroundSprite = Sprite.new('img/MainMenu/background.png')
	BackgroundSprite:scale_to(1024, 640)

	Goomba = Animator.new('img/MainMenu/Goomba.png')
	Goomba:scale_to(96,48)
	Goomba:set_position(700, 524)

	table.insert(questionblockT, Animator.new('img/MainMenu/questionblock.png'))
	table.insert(questionblockT, Animator.new('img/MainMenu/questionblock.png'))
	table.insert(questionblockT, Animator.new('img/MainMenu/questionblock.png'))
	table.insert(questionblockT, Animator.new('img/MainMenu/questionblock.png'))

	questionblockT[1]:set_position(309, 388)
	questionblockT[2]:set_position(539, 388)
	questionblockT[3]:set_position(631, 388)
	questionblockT[4]:set_position(585, 204)

	for i,v in pairs(questionblockT) do
		v:scale_to(135,45)
		v:create_animation("blinking", IntRect.new(0,0,16,16), 0, 0, 2, 0, 100, 4)
		v:set_single_delay("blinking", 400, 0, 0);
	end

	Goomba:create_animation("walking", IntRect.new(0,0,16,16), 0,0,1,0,100,4)
end

function update(dt)
	if trans then
		trans:update(dt)

		if trans:finished() then
			exit()
		end

		return
	end

	time = time + dt
	time2 = time2 + dt

	StartGameB:update(dt)
	SettingsB:update(dt)
	ExitB:update(dt)

	if Goomba:get_position().x < 0 or Goomba:get_position().x > 816 then
		GoombaDir = GoombaDir * -1
	end

	if isKeyDown("Right") then
		Goomba:move(1*0.19*dt,0)
	elseif isKeyDown("Left") then
		Goomba:move(-1*0.19*dt,0)
	end
	Goomba:animate("walking")

	for i,v in pairs(questionblockT) do
		v:animate("blinking")
	end
end

function render()
	if trans then
		trans:render()

		return
	end

	BackgroundSprite:render()
	Goomba:render()

	for i,v in pairs(questionblockT) do
		v:render()
	end

	StartGameB:render()
	SettingsB:render()
	ExitB:render()
end

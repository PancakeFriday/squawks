BackgroundSprite = 0
Button1 = 10.1
Button2 = 2.2
Goomba = 0
questionblock = 0
questionblockT = {}
GoombaDir = -1

SomeButton = 0

time = 0
time2 = 0
wait = false

function push_me()
	print("push_me")
end

function init()
	SomeButton = Button.new('img/SomeButton.png')
	SomeButton:set_position(200,100)
	SomeButton:set_action(push_me)

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
	time = time + dt
	time2 = time2 + dt

	SomeButton:update(dt)

	if Goomba:get_position().x < 0 or Goomba:get_position().x > 816 then
		GoombaDir = GoombaDir * -1
	end
	Goomba:move(GoombaDir*0.09*dt,0)
	Goomba:animate("walking")

	for i,v in pairs(questionblockT) do
		v:animate("blinking")
	end
end

function render()
	BackgroundSprite:render()
	Goomba:render()

	for i,v in pairs(questionblockT) do
		v:render()
	end

	SomeButton:render()
end

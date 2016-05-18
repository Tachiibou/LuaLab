playerTex = "./res/player.png"
local character = player.create(playerTex);
points = 0
playerSizeX = 0
playerSizeY = 0

function testing2()
	print("In Lua");
end

function setPlayerSize(x, y)
	playerSizeX = x
	playerSizeY = y

	character:setSize(x,y)
end

function getPlayerSizeX()
	return playerSizeX
end

function getPlayerSizeY()
	return playerSizeY
end

function updateMovement(x, y, type)
	if type == "dirt" then 	character:walk(x,y)
	elseif type == "grass" then  character:walk(x,y)
	elseif type == "wall" then 
	elseif type == "goal" then  win = 1
	elseif type == "spawn" then  character:walk(x,y)
	elseif type == "point" then  character:walk(x,y) points = points +1
	else
		print("WRONG TYPE BISH")end
end

function getWin()
	return win
end

function getPoints()
	return points
end

function reset()
	win = 0
	points = 0
end

function setPosition(x, y)
	character:setPos(x,y)
end


--player.testing()
--[[

--x,y
--type

--setPos(x,y)
--setType(type)

--Walk()
--if type = dirt
--player.walk(x,y)

--if type == point
--player.walk(x,y)
--player.point()

--if type = goal
--player.win()






--end


--]]


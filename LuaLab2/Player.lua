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
	character:setPos(2,2)
end

function getPlayerSizeX()
	return playerSizeX
end

function getPlayerSizeY()
	return playerSizeY
end

function updateMovement(x, y, type)
	if type == "dirt" then print ("dirt")	character:walk(x,y)
	elseif type == "grass" then print ("grass") character:walk(x,y)
	elseif type == "wall" then print ("wall") 
	elseif type == "goal" then print ("goal") win = 1
	elseif type == "spawn" then print ("spawn") character:walk(x,y)
	elseif type == "point" then print ("point") character:walk(x,y)
	else
		print("WRONG TYPE BISH")end
end

function getWin()
	return win
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


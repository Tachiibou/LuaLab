
Map = {}
width = 0
height = 0

Block = {type = "dirt",
		texture = "dirt.png",
		x = 0,
		y = 0}

Block.New = function()
	local b = {}
	setmetatable(b, Block)
	for k, v in pairs(Block) do
		b[k] = v
	end

	return b
end

Block.isGrass = function(self)
	self.type = "grass"
	self.texture = "grass.png"

end

Block.isSpawn = function(self)
	self.type = "spawn"
	self.texture = "spawn.png"

end

Block.isWall = function(self)
	self.type = "wall"
	self.texture = "wall.png"

end

Block.isPoint = function(self)
	self.type = "point"
	self.texture = "point.png"
end

Block.isGoal = function(self)
	self.type = "goal"
	self.texture = "goal.png"
end

function CreateBlockArr(x,y)
	local blockArr = {}
	local index
	for xf = 1, x,1 do
		for yf = 1, y, 1 do
			index = y*(xf - 1) + (yf - 1)
			blockArr[index] = Block.New()
			blockArr[index].x = xf
			blockArr[index].y = yf
			blockArr[index].setPos(blockArr[index],xf,yf)

			--print(index)
			--print(blockArr[index].y)
		end
	end
	return blockArr
end

Block.setPos = function (self, x , y)
	self.x = x
	self.y = y
end

function CreateMap(x,y)
	height = y
	width = x
	Map = CreateBlockArr(height,width)
end

function GetTile(x,y)
	return Map[height*x + y]
end

CreateMap(5,5)

derp = GetTile(1,4);

Block.isGrass(derp)

print(derp.x)
print(derp.y)
print (derp.type)

Map = {}
width = 100
height = 200

textureExtension = "./res/"

print("Herruuu, elsa bajs")

Block = {type = "dirt",
		texture = textureExtension.."Dirt.png",
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
-- BLOCK FUNCTIONS START
Block.isGrass = function(self)
	self.type = "grass"
	self.texture =textureExtension.. "Grass.png"

end

Block.isDirt = function(self)
	self.type = "dirt"
	self.texture =textureExtension.. "Dirt.png"

end

Block.isSpawn = function(self)
	self.type = "spawn"
	self.texture =textureExtension.. "Spawn.png"

end

Block.isWall = function(self)
	self.type = "wall"
	self.texture =textureExtension.. "Wall.png"

end

Block.isPoint = function(self)
	self.type = "point"
	self.texture = textureExtension.."Point.png"
end

Block.isGoal = function(self)
	self.type = "goal"
	self.texture =textureExtension.. "Goal.png"
end

Block.setPos = function (self, x , y)
	self.x = x
	self.y = y
end
-- CREATE MAP FUNCTIONS
function CreateBlockArr(x,y)
	local blockArr = {}
	local index
	for xf = 0, x-1,1 do
		for yf = 0, y-1, 1 do
			index = y*(xf) + (yf)
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

function CreateMap(x,y)
	height = y
	width = x
	Map = CreateBlockArr(height,width)
end

-- GET FUNCTIONS TO BE CALLED FROM c++ START
function GetTile(x,y)
	if x >= width or y >= height then print("x or y is bigger than width or height Error 1337 - Tile Error")

	else return Map[height*x + y] end
end

function GetType(x,y)
	if x >= width or y >= height then print("x or y is bigger than width or height Error 1338 - Type Error")

	else return Map[height*x + y].type end
end

function GetTexture(x,y)
	if x >= width or y >= height then print("x or y is bigger than width or height Error 1339 - Texture Error")

	else return Map[height*x + y].texture end
end

function GetWidth()
	return width
end

function GetHeight()
	return height
end

-- SET FUNCTIONS TO BE CALLED FROM c++ START
function SetGrass(x,y)
	Block.isGrass(GetTile(x,y))
end

function SetDirt(x,y)
	Block.isDirt(GetTile(x,y))
end

function SetSpawn(x,y)
	Block.isSpawn(GetTile(x,y))
end

function SetWall(x,y)
	Block.isWall(GetTile(x,y))
end

function SetPoint(x,y)
	Block.isPoint(GetTile(x,y))
end

function SetGoal(x,y)
	Block.isGoal(GetTile(x,y))
end

function SaveFile(name)
	local file = io.open(name,"w")
	file:write(width .. "\n" .. height .. "\n")
	for xf = 0, width-1,1 do
		for yf = 0, height-1, 1 do
			index = height*(xf) + (yf)

			file:write(GetType(xf,yf) .. "\n")
			--file:write(xf .. ":" .. yf .. "  " .. GetType(xf,yf) .. "\n")
			--print(blockArr[index].y)
		end
	end
	
	file:close()
end

function LoadMap(name)
	local file = io.open(name,"rb")
	local x = 0
	local y = 0
	local walls = 0
	local a = file:read("*number") -- width
	local b = file:read("*number") -- height
	local c = file:read("*line") -- need to read this to change line for some reason, this is NIL dont know why

	CreateMap(a,b) -- create an empty map
	print(a,b,c)

	while true do
		line = file:read("*line")
		if line == nil then break end -- end loop

		if (line.find(line,"dirt")) then SetDirt(x,y) end
		if (line.find(line,"wall")) then SetWall(x,y) end
		if (line.find(line,"grass")) then SetGrass(x,y) end
		if (line.find(line,"goal")) then SetGoal(x,y) end
		if (line.find(line,"point")) then SetPoint(x,y) end
		if (line.find(line,"spawn")) then SetSpawn(x,y) end

		y = y + 1

		if y >= height then x = x + 1; y = 0 end
	end
	print ("we found " .. walls .. " walls.")
	file:close()

	
end

--CreateMap(5,5)

--CreateMap(5,5)

--SaveFile("test1.txt")

--LoadMap("test1.txt")

--SetGoal(0,2)
--SetPoint(0,0)
--SetGrass(1,1)
--SetSpawn(4,4)
--SaveFile("test2.txt")


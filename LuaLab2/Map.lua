
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

b = CreateBlockArr(10,10)

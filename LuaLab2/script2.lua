print(os.date ("%A, %m %B %Y"))

Vector3 = {x = 10, y = 0, z = 0}
Vector3.prototype = {x = 0, y = 20, z = 0}
Vector3.mt = {}

Vector3.New = function()
	local vec = {}
	setmetatable(vec, Vector3)
	for k, v in pairs(Vector3) do
		vec[k] = v
	end

	return vec
end

v1 = Vector3.New()

print (v1.x, v1.prototype.y, v1.z)
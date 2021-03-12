local obj = Helpers.vec3:new(5,7,2)

local obj2 = Helpers.vec3:new(1,1,1)

obj = obj + obj2

obj3 = obj - obj2 - obj2

obj = obj3 * obj2

local matrix = Helpers.mat3:new(1)
local matrix1 = Helpers.mat3:new(2)
local matrix2 = matrix * matrix1

print(obj.x, ":", obj.y, ":", obj.z)
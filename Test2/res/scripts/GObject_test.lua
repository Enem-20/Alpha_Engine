local Gobj = Helpers.GObject:new()

local newPosition = Helpers.vec3:new(5,5,5)

print(newPosition.x)

Gobj:Translate(newPosition)

print(Gobj.position.x)
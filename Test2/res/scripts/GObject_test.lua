--require('Components')

-- Collider = Component:new(BoxCollider)

-- b = Collider:new()
-- b:SetActive(true)

-- print(b.active)

local Gobj = Helpers.GObject:new("object5")

local newPosition = Helpers.vec3:new(5,5,5)

print(newPosition.x)

Gobj:Translate(newPosition)

print(Gobj.position.x)
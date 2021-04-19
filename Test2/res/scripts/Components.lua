Transform = {}
Transform.position = Helpers.vec3

BoxCollider = {}
BoxCollider.position = Helpers.vec3

Component = {}
Component["active"] = false

function Component:new(component)
    component = component or {}
    setmetatable(component, self)
    self.__index = self
    return component
end

function Component.SetActive(switcher)
        self.active = switcher
end
function createFoo(name) --对象工厂模式
    local obj = {name = name}
    function obj:SetName(name) --等价于 function obj.SetName(self, name)
        self.name = name
    end
    function obj:GetName(name) --等价于 function obj.GetName = function(self, name)
        return self.name
    end
    return obj
end

o = createFoo("Sam")
print("name:", o:GetName()) --等价于o.GetName(o)


o:SetName("Lucy")
print("name:", o:GetName())


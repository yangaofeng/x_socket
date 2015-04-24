t = {}
t2 = {a="and", b="LiLei", c="Han Meimei"}
m={ __index = t2 }
setmetatable(t, m) --设表m为表t的元素

for k, v in pairs(t) do
    print("table t:", k, v)
end
print("------------")
print(t.b, t.a, t.c)


print("------------")
for k, v in pairs(m) do
    print(k, v)
end

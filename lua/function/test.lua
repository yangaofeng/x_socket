function foo(a, b, c) --foo是全局变量
    local sum = a + b --sum 是局部变量
    return sum, c
end

r1, r2 = foo(1, '123', 'hello') --r1, r2是全局变量
print(r1, r2)


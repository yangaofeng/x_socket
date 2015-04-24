a={} -- 定义一张空表
b={n = 1, str='abc', 100, 'hello'} --定义一张有初始内容的表

--访问表的成员
a.n = 1
a.str='abc'
a[1] = 100
a[2] = 'hello'
a['a table'] = b

--任何类型的值都可以做表项的key，除了nil
function func1() end
function func2() end
a[func1] = func2 --func1作为key， func2作为value

--穷举表a
for k, v in pairs(a) do
    print(k, "=>", v)
end

--穷举表b
for k, v in pairs(a['a table']) do
    print(k, "=>", v)
end

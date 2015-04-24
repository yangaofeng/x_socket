// test.cc (2015-04-22)
// Yan Gaofeng (yangaofeng@360.cn)

#include <iostream>
#include <string.h>

using namespace std;

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    if (L == NULL) {
        return -1;
    }

    //加载lua文件
    int bRet = luaL_loadfile(L, "hello.lua");
    if (bRet) {
        cout << "load file error" << endl;
        return -1;
    }

    bRet = lua_pcall(L, 0, 0, 0);
    if (bRet) {
        cout << "pcall error" << endl;
        return -1;
    }

    lua_getglobal(L, "str");

    string str = lua_tostring(L, -1);
    cout << "str = " << str << endl;

    lua_getglobal(L, "tbl");
    lua_getfield(L, -1, "name");
    str = lua_tostring(L, -1);
    cout << "table:name = " << str << endl;

    lua_getglobal(L, "add");
    lua_pushnumber(L, 10);
    lua_pushnumber(L, 20);
    int iRet = lua_pcall(L, 2, 1, 0);
    if (iRet) {
        cout << "call lua_pcall failed" << endl;
        return -1;
    } 

    if (lua_isnumber(L, -1)) {
        double fVal = lua_tonumber(L, -1);
        cout << "Result is " << fVal << endl;
    }

    return 0;
}


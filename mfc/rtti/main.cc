// main.cc (2017-12-17)
// Yan Gaofeng (yan_gaofeng@hotmail.com)

#include <iostream>
#include <stdio.h>
#include <string.h>

#define  LPCSTR char *
#define  UINT unsigned int

class CObject;

struct CRuntimeClass
{
    // Attributes
    LPCSTR m_lpszClassName;

    int m_nObjectSize;

    // schema number of the loaded class
    UINT m_wSchema; 

    // 由IMPLEMENT_DYNCREATE宏指定
    CObject* (* m_pfnCreateObject)(); // NULL => abstract class

    CRuntimeClass* m_pBaseClass;

    // 会使用 m_pfnCreateObject 创建具体的对象
    CObject* CreateObject();

    // CRuntimeClass 有, 其它类没有
    static CRuntimeClass* Load();

    // CRuntimeClass objects linked together in simple list
    static CRuntimeClass* pFirstClass; // start of class list

    CRuntimeClass* m_pNextClass; // linked list of registered classes
};

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

// 不是宏, 是结构体
struct AFX_CLASSINIT
{ AFX_CLASSINIT(CRuntimeClass *pNewClass); };

// 构造函数, 不是宏
AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass *pNewClass)
{
    pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
    CRuntimeClass::pFirstClass = pNewClass;
}

#define RUNTIME_CLASS(class_name) \
    (&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
    public: \
    static CRuntimeClass class##class_name; \
    virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
    static char _lpsz##class_name[] = #class_name; \
    CRuntimeClass class_name::class##class_name = { \
        _lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
        RUNTIME_CLASS(base_class_name), NULL }; \
        static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
        CRuntimeClass* class_name::GetRuntimeClass() const \
{ return &class_name::class##class_name; } \

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
    _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)


// 动态创建
#define DECLARE_DYNCREATE(class_name) \
    DECLARE_DYNAMIC(class_name) \
    static CObject* CreateObject();
#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
    CObject* class_name::CreateObject() \
    { return new class_name; } \
    _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
        class_name::CreateObject)



// CObject, 表头, 需要特殊构造, 不能直接套用宏
class CObject {
    public:
        // 定义成虚函数是因为派生类会改写
        virtual CRuntimeClass *GetRuntimeClass() const;

        bool IsKindOf(const CRuntimeClass *pClass) const;

        virtual void SayHello() { std::cout << "Hello Object\n"; }

    public:
        static CRuntimeClass classCObject;
};

// 判断派生类是否是pClass
bool CObject::IsKindOf(const CRuntimeClass *pClass) const
{
    // 获取自身的CRuntimeClass, 如 classWinThread
    // GetRuntimeClass是虚函数, 派生类会改写
    CRuntimeClass *pClassThis = GetRuntimeClass();
    while (pClassThis != NULL) {
        if (pClassThis == pClass) {
            return true;
        }
        // 找基类
        pClassThis = pClassThis->m_pBaseClass;
    }

    return false;
}

// 以全局变量的方式定义RTTI
static char szCObject[] = "CObject"; 
struct CRuntimeClass CObject::classCObject = 
{ szCObject, sizeof(CObject), 0xFFFF, NULL, NULL };
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

// CObject成员函数
CRuntimeClass *CObject::GetRuntimeClass() const 
{
    return &CObject::classCObject;
}
// CObject 表头构造结束


CObject* CRuntimeClass::CreateObject()
{
    if (m_pfnCreateObject == NULL) {
        printf("Error: Trying to create object which is not "
                "DECLARE_DYNCREATE \nor DECLARE_SERIAL: %hs.\n",
                m_lpszClassName);
        return NULL;
    }

    CObject* pObject = NULL;
    // 调用具体类的创建函数
    pObject = (*m_pfnCreateObject)();
    return pObject;
}

// 模拟用的, 从命令行创建类
CRuntimeClass* CRuntimeClass::Load()
{
    char szClassName[64];
    CRuntimeClass* pClass;
    // JJHOU : instead of Load from file, we Load from cin.
    std::cout << "enter a class name... ";
    std::cin >> szClassName;
    for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass) {
        if (strcmp(szClassName, pClass->m_lpszClassName) == 0)
            return pClass;
    }
    printf("Error: Class not found: %s \n", szClassName);
    return NULL; // not found
}


// CCmdTarget
class CCmdTarget : public CObject {
    DECLARE_DYNAMIC(CCmdTarget)
};

// CWinThread
class CWinThread: public CCmdTarget {
    DECLARE_DYNAMIC(CWinThread)
};

// CWind
class CWnd: public CCmdTarget {
    DECLARE_DYNCREATE(CWnd)

public:
    void SayHello() { std::cout << "Hello CWnd \n"; }
};

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread, CCmdTarget)
IMPLEMENT_DYNCREATE(CWnd, CCmdTarget)


void PrintAllClasses()
{
    CRuntimeClass *pClass;

    for (pClass = CRuntimeClass::pFirstClass; pClass != NULL;
            pClass = pClass->m_pNextClass)
    {
        std::cout << pClass->m_lpszClassName << "\n";
        std::cout << pClass->m_nObjectSize << "\n";
        std::cout << pClass->m_wSchema << "\n";
    }
}

int main() {
    PrintAllClasses();

    // 演示运行时类型识别
    CWinThread o;
    bool ok = o.IsKindOf(RUNTIME_CLASS(CCmdTarget));
    if (ok) {
        std::cout << "CWinThread is s CCmdTarget" << "\n";
    }

    // 演示动态创建, 请在命令行输入"CWnd"
    CRuntimeClass *pClassRef;
    CObject *pOb;
    while(1) {
        if ((pClassRef = CRuntimeClass::Load()) == NULL) {
            break;
        }

        pOb = pClassRef->CreateObject();
        if (pOb != NULL) {
            pOb->SayHello();
        }
    }

    return 0;
}


// main.go (2017-11-20)
// yangaofeng (yangaofeng@360.net)

package main

import (
	"fmt"
	"reflect"
	// "unsafe"
)

type Reader interface {
	Read() string
}

type Log struct {
	name string
}

func (l *Log) Read() string {
	return "Hello"
}

func main() {

	// 测试类型比较
	var a interface{} = Log{}
	var b interface{} = Log{}

	fmt.Printf("a: %#v\n", a)
	fmt.Printf("b: %#v\n", b)

	if a == b {
		fmt.Println("a == b")
	} else {
		fmt.Println("a != b")
	}

	// 反射
	k := reflect.TypeOf(a).Kind()
	fmt.Println("kind of interface: ", k)

	var l Log
	k = reflect.TypeOf(l).Kind()
	fmt.Println("kind of struct: ", k)

	// 测试指针值
	s1 := Log{}
	s2 := Log{}

	if s1 == s2 {
		fmt.Printf("compare struct, s1 == s2\n")
	} else {
		fmt.Printf("compare struct, s1 != s2\n")
	}

	// 测试指针值
	p1 := &Log{}
	p2 := &Log{}

	if p1 == p2 {
		fmt.Printf("compare struct pointer, p1 == p2\n")
	} else {
		fmt.Printf("compare struct pointer, p1 != p2\n")
	}

	//fmt.Printf("log point 1 %d\n", uintptr(unsafe.Pointer(l1)))
	//fmt.Printf("log point 2 %d\n", uintptr(unsafe.Pointer(l2)))

}

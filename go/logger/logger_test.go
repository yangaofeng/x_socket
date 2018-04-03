// mlogger_test.go (2018-03-26)
// Yan Gaofeng (yan_gaofeng@hotmail.com)

package mwlogger

import (
	"golang.org/x/net/context"
	"log"
	"testing"

	"middleware/log"
)

func creator(method string) grpc_log.Logger {
	return NewLogger(method, MW_DEBUG)
}

func A(ctx context.Context, t *testing.T) {
	l := grpc_log.GetLogger(ctx)
	if l == nil {
		t.Error("get logger failed")
	}

	l.Debugf("hello A")
	l.Infof("hello A")
	l.Warnf("hello A")
	l.Errorf("hello A")
	// l.Fatalf("hello A")
	// ctx2 := WithLogger(ctx, l)
	// B(ctx2)
}

// func B(ctx context.Context, t *testing.T) {
// 	l := GetLogger(ctx)
// 	l.Infof("hello B")
// }

func TestInfo(t *testing.T) {

	log.SetFlags(log.Ldate | log.Ltime | log.Lmicroseconds | log.Lshortfile)

	grpc_log.SetCreator(creator)

	A(context.Background(), t)
}

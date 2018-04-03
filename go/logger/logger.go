// mwlogger.go (2018-03-26)
// Yan Gaofeng (yan_gaofeng@hotmail.com)

package mwlogger

import (
	"fmt"
	"log"
	"middleware/log"
	"strings"
)

const (
	MW_DEBUG = iota + 10000
	MW_INFO
	MW_WARN
	MW_ERROR
	MW_FATAL
)

var (
	dlStrCode = map[int]string{
		MW_DEBUG: "[DEBUG]",
		MW_INFO:  "[INFO]",
		MW_WARN:  "[WARN]",
		MW_ERROR: "[ERROR]",
		MW_FATAL: "[FATAL]",
	}
)

type DefaultLogger struct {
	logName string
	level   int
}

func NewLogger(logName string, level int) grpc_log.Logger {
	return &DefaultLogger{
		logName: logName,
		level:   level,
	}
}

func (dl *DefaultLogger) Fatalf(format string, args ...interface{}) {
	// TODO: logName, level, levelString
	s := fmt.Sprintf(format, args...)
	dl.output(MW_FATAL, s)
}

func (dl *DefaultLogger) Errorf(format string, args ...interface{}) {
	s := fmt.Sprintf(format, args...)
	dl.output(MW_ERROR, s)
}

func (dl *DefaultLogger) Warnf(format string, args ...interface{}) {
	s := fmt.Sprintf(format, args...)
	dl.output(MW_WARN, s)
}

func (dl *DefaultLogger) Infof(format string, args ...interface{}) {
	s := fmt.Sprintf(format, args...)
	dl.output(MW_INFO, s)
}

func (dl *DefaultLogger) Debugf(format string, args ...interface{}) {
	s := fmt.Sprintf(format, args...)
	dl.output(MW_DEBUG, s)
}

func (dl *DefaultLogger) output(level int, s string) {
	if level < dl.level {
		return
	}

	b := strings.Builder{}
	b.WriteString(dlStrCode[level])
	b.WriteString("\t")
	b.WriteString(dl.logName)
	b.WriteString("\t")
	b.WriteString(s)
	log.Output(3, b.String())

	if level == MW_FATAL {
		panic("")
	}
}

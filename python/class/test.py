class Test:
    desc = "this is a test class"

    def __init__(self, name):
        self.name = name

    def show(self):
        print self.name

if (__name__ == "__main__"):
    t = Test("test name")
    print t
    print t.desc
    t.show()

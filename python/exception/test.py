try:
    raise Exception("hello", "world")
except Exception as e:
    print e

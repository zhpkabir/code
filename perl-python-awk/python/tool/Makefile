CFLAGS+= $(shell pkg-config --cflags  python)
LDFLAGS+= $(shell pkg-config --libs python)

api.so:
	g++ -fPIC -shared $(CFLAGS) $(LDFLAGS) py.cpp -o $@

%:%.c
	gcc $(CFLAGS) $(LDFLAGS) $< -o $@

ssd TestModule:
	gcc -shared -fpic $(CFLAGS) $(LDFLAGS) TestModule.c -o $@.so

%:%.cpp
	g++ $(CFLAGS) $(LDFLAGS) -lboost_python-py27 $< -o $@

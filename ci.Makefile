
all:
	$(MAKE) -C global/modules/cli/ -f ci.Makefile
	$(MAKE) -C global/modules/tcpServer/ -f ci.Makefile
	$(MAKE) -C global/modules/textproto/ -f ci.Makefile
	$(MAKE) -C examples/hello_world/ -f ci.Makefile



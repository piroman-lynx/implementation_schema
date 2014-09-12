

all:
	is-cc tcpServer.cpp
	is-cc tcpConnection_private.cpp
	is-cc tcpServer_private.cpp
	is-cc makemodule tcpServer.cpp tcpConnection_private.cpp tcpServer_private.cpp

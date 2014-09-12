
all:
	is-cc textproto.cpp
	is-cc textproto_private.cpp
	is-cc makemodule textproto.cpp textproto_private.cpp

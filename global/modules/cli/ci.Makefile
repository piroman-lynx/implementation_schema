

all:
	is-cc cli.cpp
	is-cc cli_private.cpp
	is-cc makemodule cli.cpp cli_private.cpp

Задача:
  Написасть binary выводящую в консоль Hello World

Реализация на Implementation Schema:

    #provide binary hello_world
    #require cli as c

    hello_world {
      c< "Hello world"
    }

Сборка:
$ is hello_world.is hello_world.out

Задача:
  Написать библиотеку выводящую в консоль Hello World, доступную по имени lib_hello_world

Реализация на Implementation Schema:

    #provide library lib_hello_world
    #require cli as c

    hello_world_call {
      c< "Hello world"
    }

Сборка:
$ is hello_world.is hello_world.out hello_world.so hello_world.la hello_world.la hello_world.c

Задача:
  Написать бинарик использующий библиотеку lib_hello_world
  
Реализация на Implementation Schema:

    #provide binary hello_world
    #require lib_hello_world
    
    hello_world {
      hello_world_call
    }
    
Сборка:
$ is clean
$ is add_library hello_world.c
$ is hello_world.is hello_world.out

Задача:
  Написать бинарик использующий библиотеку lib_hello_world с подменой cli на tcp<cli
  
Реализация на Implementation Schema:

    #provide binary hello_world
    #require lib_hello_world \
      #with_replace cli<tcp_server tcp_init as cli
    
    tcp_init {
      tcp<tcp_host<"127.0.0.1"
      tcp<tcp_port<10000
    }
    
    hello_world {
      hello_world_call
    }


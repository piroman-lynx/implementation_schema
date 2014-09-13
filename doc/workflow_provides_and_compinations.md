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

    $ is hello_world.is hello_world.out hello_world.so hello_world.la hello_world.la hello_world.cpp

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
    $ is add_library hello_world
    $ is hello_world.is hello_world.out

Задача:
  Написать бинарик использующий библиотеку lib_hello_world с подменой cli на вывод в файл
  
Реализация на Implementation Schema:

    #provide binary hello_world
    #require fileIO
    #make <>Stream \
      #with init file_init as file
    #require lib_hello_world \
      #with_replace cli to file
    
    file_init with (streamConfig) {
      streamConfig.preConfigure("<").forStream(fileIO).configure({ "filename":"/tmp/out" })
      streamConfig.preConfigure(">").forStream(fileIO).configure({ "filename":"/tmp/in" })
      return streamConfig;
    }
    
    hello_world {
      hello_world_call
    }


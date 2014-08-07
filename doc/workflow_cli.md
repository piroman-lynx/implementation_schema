Задача: 
 Вывод строки "Hello world" в cli

Реализация Implementation Schema:

    #provide binary hello_world
    #require cli as c
    
    hello_world {
      c< "Hello world"
    }
    

Задача:
 Реализация простого конечного автомата в cli
 
Реализация Implementation Schema:

    #provide binary fsm_hello_world
    #require cli as c
    #require fsm as fsm
    
    fsm_hello_world {
      c< "Enter 0 or 1"
      c> fsm {
       "0": fsm_hello
       "1": fsm_world
       *: fail
      }
    }
    
    fail {
      c< "Not 0 or 1"
    }
    
    fsm_hello {
      c< "Hello"
    }
    
    fsm_world {
      c< "World"
    }

Задача:
  Реализация простого конечного автомата с io в tcp
  
Реализация Implementation Schema:
  
    #provide binary fsm_tcp_hw
    #require cli<tcp_server tcp_init as tcp
    #require cli as c
    #require fsm as fsm
    
    tcp_init {
      tcp<tcp_host<"127.0.0.1"
      tcp<tcp_port<10000
    }
    
    fsm_tcp_hw {
      tcp< "Send 0 or 1"
      tcp> fsm {
       "0\n": fsm_hello
       "1\n": fsm_world
       *: fail
      }
    }
    
    ....

Задача:
  Реализация многопоточного конечного автомата с io в tcp
  
Реализация Implementation Schema:
    
    #provide binary fsm_tcp_hw
    #require cli<tcp_server<threads tcp_init as tcp
    #require cli as c
    #require fsm as fsm
    
    tcp_init {
      tcp<tcp_host<"127.0.0.1"
      tcp<tcp_port<10000
      tcp<threads_max<20
      tcp<threads_cache<0
    }
    
    fsm_tcp_hw {
      tcp< "Send 0 or 1"
      tcp> fsm {
       "0\n": fsm_hello
       "1\n": fsm_world
       *: fail
      }
    }
    
    ....

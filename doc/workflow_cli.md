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
       "0": fsm_hello(c)
       "1": fsm_world(c)
       *: fail(c)
      }
    }
    
    fail with (c) {
      c< "Not 0 or 1"
    }
    
    fsm_hello with (c) {
      c< "Hello"
    }
    
    fsm_world with (c) {
      c< "World"
    }

Задача:
  Реализация простого конечного автомата с io в tcp
  
Реализация Implementation Schema:
  
    #provide binary fsm_tcp_hw
    #require textproto
    #require tcpServer(forChild<textproto)
    #require fsm as fsm
    
    fsm_tcp_hw {
      tcpServer.configure({ "host":"localhost", "port":1001 }).forPool(tcp_conn)
    }
    
    tcp_conn with (stream) {
      stream< "Send 0 or 1"
      stream> fsm {
       "0\n": fsm_hello(stream)
       "1\n": fsm_world(stream)
       *: fail
      }
    }
    
    ....

Задача:
  Реализация многопоточного конечного автомата с io в tcp
  
Реализация Implementation Schema:
    
    #provide binary fsm_tcp_hw
    #require textproto
    #require fsm as fsm
    #require threadPool(forChild<textproto)
    #require tcpServer(forChild<threadPool) as tcp
    
    fsm_tcp_hw {
      pool = threadPool.configure({ "max":20, "prestart":0 }).forOne(tcp_thread)
      tcp.configure({ "host":"localhost", "port":1001 }).forPool(pool)
    }
    
    tcp_thread with (tcp) {
      tcp< "Send 0 or 1"
      tcp> fsm {
       "0\n": fsm_hello(tcp)
       "1\n": fsm_world(tcp)
       *: fail(tcp)
      }
    }
    
    ....

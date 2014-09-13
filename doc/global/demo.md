
    #provide binary webecho
    #require webMVCServer
    #require logger_syslog
    #require date
    #require threadPool
    
    webecho {
      thread_pool = threadPool.configure({ "max":20, "start":0 }).forOne(web)
      httpServer.configure({ "host":"0.0.0.0", "port":80 }).forPool(thread_pool)
    }
    
    web with (socket) {
      webMVCServer.urlMap("/([.]*)", request)
      webMVCServer.preFilter(dolog)
      webMVCServer.forSocket(socket)
    }
    
    dolog with (request){
      $logger = logger_syslog.configure({ "ident": "httpd", "facility": "local7" })
      $logger<"[ %d ] %T %U" | with ({"%d": date.now.format("Y-m-d H:i:s"), "%T": request.method.string, "%U": request.url})
      //do write [ 2014-09-13 23:21 ] GET /test
    }
    
    request with (request, response, firstParam) {
      html = HTML.makeDoc().toBody('<h1>Request to Echo server</h1> Uri: %U' | with ({"%U": request.url})).toString();
      response<html
    }
    

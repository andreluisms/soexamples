from threading import *         
import time        
  
obj = Semaphore(1)        
  
#Using output
def show(name):    
    obj.acquire()                
    for i in range(5):
        print('Hello, ', name)
        time.sleep(1)
    obj.release()    
          
# creating six threads 
t1 = Thread(target = show , args = ('Thread-1',))
t2 = Thread(target = show , args = ('Thread-2',))
t3 = Thread(target = show , args = ('Thread-3',))
t4 = Thread(target = show , args = ('Thread-4',))
t5 = Thread(target = show , args = ('Thread-5',))
t6 = Thread(target = show , args = ('Thread-6',))
  
# calling the threads 
t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t6.start()
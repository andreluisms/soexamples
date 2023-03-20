from threading import *         
import time        
  
S0 = Semaphore(1)   
S1 = Semaphore(1)   
S2 = Semaphore(1)   
lock =  Lock()
  

def printsync(*str):
    lock.acquire()
    print(str)
    lock.release()


#Using output
def task(name, times, funcs, sems):
    itime = 0
    for f in range(len(times)):
        time.sleep(times[f]/10.0)
        itime += times[f]
        if funcs[f:] != []:
            printsync ('[time: ' + str(itime) + ']', name, "calls ", sems[f] + '.' + funcs[f].__name__ + '()')
            funcs[f]()
    printsync ('[time: ' + str(itime) + ']', name, "END")
                  
# creating six threads 
t1 = Thread(target = task , args = ('Task A', [3, 4, 1, 1, 2], [S0.acquire, S2.acquire, S2.release, S0.release], ['S0', 'S2', 'S2', 'S0']))
t2 = Thread(target = task , args = ('Task B',[1, 2, 1, 3, 1, 2], [S1.acquire, S2.release, S2.acquire, S2.release, S0.release], ['S1', 'S2', 'S2', 'S2', 'S0']))
t3 = Thread(target = task , args = ('Task C',[4, 1, 2, 3], [S2.acquire, S1.release, S0.acquire], ['S2', 'S1', 'S0']))
  
# calling the threads 
t1.start()
t2.start()
t3.start()
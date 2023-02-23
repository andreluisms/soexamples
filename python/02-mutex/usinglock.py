import threading
import time
import random

n_threads = 10000
lock = threading.Lock()

def job():
    r = random.random()
    time.sleep(r)
    lock.acquire()
    print('lock acquire() ------>',threading.current_thread().getName())
    lock.release()

if __name__ == '__main__':
    for i in range(n_threads):
        t = threading.Thread(target=job, args=())
        t.start()
    main_thread = threading.current_thread()
    for t in threading.enumerate():
        if t is not main_thread:
            t.join()
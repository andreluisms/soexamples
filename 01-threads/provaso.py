import threading, time

lst = [3,1,2,5]

def thr(name):
    time.sleep(2)
    if name == lst[name]:
        print(name * 3)


for i in range(4):
    x = threading.Thread(target=thr, args=(i,))
    x.start()
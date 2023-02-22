#Adaptado de realpython.com/intro-to-python-threading/#what-is-a-thread

import logging, threading, time

def thread_function(name):
    logging.info("Thread %s: iniciando", name)
    time.sleep(2)
    logging.info("Thread %s: finalizando", name)

if __name__ == "__main__":
    format = "[%(asctime)s: %(threadName)s] -  %(message)s: " #Cria formato para log. Formato hora/nome da thread/ mensagem
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

    logging.info("Antes de criar a thread")
    x = threading.Thread(target=thread_function, args=(1,), daemon=True)
    x.start()

    logging.info("aguardando final da thread")
    # x.join()
    logging.info("Finalizado")
#Adaptado de realpython.com/intro-to-python-threading/#what-is-a-thread

import concurrent.futures, logging, time

def thread_function(name):
    logging.info("Thread %s: iniciando", name)
    time.sleep(2)
    logging.info("Thread %s: finalizando", name)

if __name__ == "__main__":
    format = "[%(asctime)s: %(threadName)s] -  %(message)s: " #Cria formato para log. Formato hora/nome da thread/ mensagem
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

    logging.info("Antes de criar a thread")
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
        executor.map(thread_function, range(5))

    logging.info("aguardando final das threads")
    logging.info("Finalizado")
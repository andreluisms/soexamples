#Adaptado de realpython.com/intro-to-python-threading/#what-is-a-thread

import time, logging, concurrent.futures

class SimpleDatabase:
    def __init__(self):
        self.value = 0

    def update(self, name):
        logging.info("Thread %s: Iniciando atualizacao", name)
        copy = self.value
        copy += 1
        time.sleep(0.1)
        self.value = copy
        logging.info("Thread %s: Finalizando atualizacao", name)

if __name__ == "__main__":
    format = "[%(asctime)s: %(threadName)s] -  %(message)s: "
    logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

    database = SimpleDatabase()
    logging.info("Testando atualizacao. Iniciando com valor %d.", database.value)
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as executor:
        # executor.map(database.update, range(2))
        for index in range(2):
            executor.submit(database.update, index)
    logging.info("Testando atualizacao. Valor final e %d.", database.value)
# -*- coding: utf-8 -*-

from .server import server as agent

class iot:

    def run(self):
        agent.init_network(agent)
        agent.run_server(agent)

if __name__ == '__main__':
    agent.init_network(agent)
    agent.run_server(agent)